
#include "../../proj/tl_common.h"

#if __PROJECT_PHY_TEST__

/**********************************************************************
 * INCLUDES
 */
#include "../../proj_lib/rf_drv.h"

#include "../../rf/rf.h"
#include "phy_test.h"




/**********************************************************************
 * CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */
typedef struct {
    priQueue_t rxQ;

    ev_time_event_t sendDataTimer;
    u32 txTimerInterval;
    u32 txNum;
    u8* txBuf;
    u8  txLen;
    u32 txCnt;

    u8  *rxTgtBuf;
    u8  rxTgtLen;

    u32 rxSuccCnt;
    u32 rxFailCnt;
} phyTest_ctrl_t;


/**********************************************************************
 * LOCAL FUNCTIONS
 */
phyTest_ctrl_t phyTest_vs;
phyTest_ctrl_t *phyTest_v = &phyTest_vs;

extern unsigned char rf_tx_mode;

extern void rfTest_init(void);
extern void rfTest_reset(void);
extern void rfTest_set(u8 id, u8 *pValue, u8 len);
extern void rfTest_resetStatistic(void);
extern u32  rfTest_getTxFinishCnt(void);
extern u32  rfTest_getRxCnt(void);
extern u32  rfTest_getRxGarbageCnt(void);

rf_specificFunc_t rfTest_funcs =
{
	rfTest_init,
	rfTest_reset,
	rfTest_set,
};

u8 defPayload[27] = {
    0x41, 0x88, 0x11, 0xAA, 0x1A, 0xFF, 0xFF, 0x44, 0x33, // mac compatible header
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, // test payloads 
    0xFE, 0xFE}; // fcf


u8 rxTargetPayload[160];
u8 txPayload[128] = {
    0x41, 0x88, 0x11, 0xAA, 0x1A, 0xFF, 0xFF, 0x44, 0x33, // mac compatible header
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, // test payloads 
    0xFE, 0xFE, 0x41, 0x88, 0x11, 0xAA, 0x1A, 0xFF, 0xFF, 0x44, 0x33, // mac compatible header
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, // test payloads 
    0xFE, 0xFE,
    0x41, 0x88, 0x11, 0xAA, 0x1A, 0xFF, 0xFF, 0x44, 0x33, // mac compatible header
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, // test payloads 
    0xFE, 0xFE,
    0x41, 0x88, 0x11, 0xAA, 0x1A, 0xFF, 0xFF, 0x44, 0x33, // mac compatible header
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10, // test payloads 
    0xFE, 0xFE,};

ev_time_event_t rssiTimer;



/**********************************************************************
 * GLOBAL VARIABLES
 */
extern u8 rf_lastRssi;


/**********************************************************************
 * LOCAL VARIABLES
 */

/////////////////////////////////////////////////////////////////////////////
//		EMI
/////////////////////////////////////////////////////////////////////////////
static int	state, feed;
void emi_pn (void) {
	feed = (state&BIT(14)) >> 1;
	state ^= feed;
	state <<= 1;
	state = (state&0xfffe) + ((state&BIT(15))>>15);
}

static inline void emi_test_tx_restore (void) {
	write_reg16 (0x800400,0x0b);
}

static inline void emi_test_tx_init(void){
	int k = 0;
	write_reg8 (0x800400,0x02);//0a for 2Mbps, 02 for Zigbee
	write_reg8 (0x800401,0x80);//kick tx controller to wait data
	//transmit data
	write_reg32(0x80041c,0xa008030a);
	write_reg32(0x80041c,0xffffffff);

	//Init PN generator [15 14 0] and run some empty loops
	state = BIT(14);
	for (k=0; k<100; k++){
		emi_pn ();
	}
}

#ifndef EMI_CD_MODE_RE_CHECK
#define EMI_CD_MODE_RE_CHECK	0
#endif
void emi_test_tx_status_check(void){
	/*if(read_reg8(0x80041c) & 0x1){
		return;
	}*/

	u32 t = 0;
	while((read_reg8(0x80041c) & 0x1) && (t++<100))
	{
		//advance PN generator
		emi_pn ();
	}
#if EMI_CD_MODE_RE_CHECK	
	if ( t >= 100 ){
		write_reg8(0x800060, 2);	
		write_reg8(0x800060, 0);
		
		SetTxMode (g_rf_chn, 0);
		emi_test_tx_init();
		}
#endif	
	write_reg8(0x80041c, state);
    

	//advance PN generator
	emi_pn ();
}


void emi_task(void)
{
    emi_test_tx_status_check();
}
////////////////////////////// end of EMI ///////////////////////////////



u8 phy_getEdFromRssi(s8 rssi)
{
	u8 ed;
	u32 temp;

	/* Transfer the RSSI value to ED value */
	if (rssi <= -75) {
		ed = 0;
	} else if (rssi >= -15) {
		ed = 0xff;
	} else{
		temp = (rssi + 75) * 255;
		ed = temp/65;
	}

	return ed;
}


void phyTest_setRxTargetPayload(u8* buf, u8 len)
{
    phyTest_v->rxTgtLen = len;
    memcpy(rxTargetPayload, buf, len);
    phyTest_v->rxTgtBuf = rxTargetPayload;
}


void phyTest_setTxPayload(u8* buf, u8 len)
{
    //memcpy(txPayload, buf, len);
    
    phyTest_v->txBuf = txPayload;
    phyTest_v->txLen = len;
}

void phyTest_txStatistic(void)
{
	u8 *buf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	u32 txFinishCnt = 0;
    u8 *p = buf;

    *p++ = 9;
    *p++ = CMD_ID_GET_TX_STATISTIC;

	memcpy(p, (u8*)&phyTest_v->txCnt, 4);
    p+=4;
	txFinishCnt = rfTest_getTxFinishCnt();
	memcpy(p, (u8*)&txFinishCnt, 4);
    p+=4;

	sendCmdToTH(buf, p-buf);
}


void phyTest_rxStatistic(void)
{
	u8 *buf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	u32 rxCnt = 0;
	u32 rxGarbageCnt = 0;
    u8 *p = buf;

	rxCnt = rfTest_getRxCnt();
	rxGarbageCnt = rfTest_getRxGarbageCnt();

    *p++ = 17;
    *p++ = CMD_ID_GET_RX_STATISTIC;

	memcpy(p, (u8*)&rxCnt, 4);
    p+=4;
	memcpy(p, (u8*)&rxGarbageCnt, 4);
    p+=4;
	memcpy(p, (u8*)&phyTest_v->rxSuccCnt, 4);
    p+=4;
	memcpy(p, (u8*)&phyTest_v->rxFailCnt, 4);
    p+=4;

	sendCmdToTH(buf, p-buf);
}


int phy_edTimerCb(void* arg)
{
	u8 *rsp = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	rsp[0] = 2;
	rsp[1] = CMD_ID_GET_ED;
	rsp[2] = rf_stopED();
    sendCmdToTH(rsp, 3);
    return -1;
}


int phy_rssiTimerCb(void* arg)
{
    u8 *rsp = bufm_allocate(DFLT_LARGE_BUF_SIZE);
    rsp[0] = 3;
    rsp[1] = CMD_ID_GET_RSSI;
    rsp[2] = rf_getRssi() + 110;
    rsp[3] = phy_getEdFromRssi(rsp[2] - 110);
    sendCmdToTH(rsp, 4);
    return 0;
}

void phy_startRssiTimer(void)
{
    rssiTimer.cb = phy_rssiTimerCb;
    ev_on_timer(&rssiTimer, 1000);
}


/*********************************************************************
 * @fn      phyTest_cmd_handler
 *
 * @brief   Main task to handle the test command from Host
 *
 * @param  none
 *
 * @return  none
 */
u8 T_BUF[50];
volatile u8 T_FLAG = 0;
static u8 stop_tx = 0;
void phyTest_cmd_handler(void* arg)
{
    u8 *rsp = bufm_allocate(DFLT_LARGE_BUF_SIZE);
    
    phyTest_cmd_t* cmdPayload = (phyTest_cmd_t*)arg;

    memcpy(T_BUF, (u8*)cmdPayload, 20);


    switch(cmdPayload->cmdId) {
    case CMD_ID_TX:
    {   u32 timerInterval, txNum;
        
        memcpy(&txNum, &(cmdPayload->payload[0]), 4);
        memcpy(&timerInterval, &(cmdPayload->payload[4]), 4);
        phyTest_v->txTimerInterval = timerInterval;
        phyTest_v->txNum = txNum;
        if (phyTest_v->txNum == 0) {
            phyTest_v->txNum = 0xFFFFFFFF;
        }
        phyTest_tx(NULL);
    }
        break;
        
    case CMD_ID_RX:
    {
    	rf_setTrxState(RF_STATE_RX);
    }
        break;
        
    case CMD_ID_SET_TX_PAYLOAD:
    {
        phyTest_setTxPayload(cmdPayload->payload, cmdPayload->length - 1);;
    }
        break;
        
    case CMD_ID_SET_RX_TARGET_PAYLOAD:
    {
        phyTest_setRxTargetPayload(cmdPayload->payload, cmdPayload->length - 1);
    }
        break;
        
    case CMD_ID_SET_TX_POWER:
    {
        rf_set(RF_ID_TX_POWER, &cmdPayload->payload[0], 1);
    }
        break;

    case CMD_ID_SET_CHANNEL:
    {
        rf_set(RF_ID_CHANNEL, &cmdPayload->payload[0], 1);
    }
        break;
        
    case CMD_ID_GET_CCA:
        rsp[0] = 2;
        rsp[1] = CMD_ID_GET_CCA;
        rsp[2] = rf_performCCA();
        bufm_free(arg);
        sendCmdToTH(rsp, 3);
        return;
        
    case CMD_ID_GET_ED:
        rf_startED();
        rssiTimer.cb = phy_edTimerCb;
        ev_on_timer(&rssiTimer, 500);
        bufm_free(arg);
        return;
        
    case CMD_ID_GET_LQI:
        rsp[0] = 2;
        rsp[1] = CMD_ID_GET_LQI;
        rsp[2] = rf_getLqi(rf_lastRssi);
        bufm_free(arg);
        sendCmdToTH(rsp, 3);
        return;

    case CMD_ID_GET_RSSI:
        rsp[0] = 3;
        rsp[1] = CMD_ID_GET_RSSI;
        rsp[2] = rf_getRssi()+110;
        rsp[3] = phy_getEdFromRssi(rsp[2]-110);
        bufm_free(arg);
        sendCmdToTH(rsp, 4);
        return;

    case CMD_ID_START_DETECT_RSSI:
        rssiTimer.cb = phy_rssiTimerCb;
        ev_on_timer(&rssiTimer, 500000);
        break;

    case CMD_ID_STOP_RSSI:
        ev_unon_timer(&rssiTimer);
        break;

    case CMD_ID_GET_TX_STATISTIC:
    	phyTest_txStatistic();
    	break;

    case CMD_ID_GET_RX_STATISTIC:
    	phyTest_rxStatistic();
    	break;

    case CMD_ID_RESET_STATISTIC:
        phyTest_v->txCnt = 0;
        phyTest_v->rxSuccCnt = 0;
        phyTest_v->rxFailCnt = 0;
        rfTest_resetStatistic();
        break;

    case CMD_ID_TX_CARRIER:
        rf_tx_mode = RF_TX_MODE_CARRIER;
      #if(MODULE_RF_PA_ENABLE)
        gpio_write(GPIO_RF_PA_TXEN, 1); // PA TX_EN
      #endif
        SetTxMode();
        break;

    case CMD_ID_TX_CONTINUED_ZB:
        
        /* Setting EMI parameter */
        rf_tx_mode = RF_TX_MODE_CONTINUE;
        write_reg32(0x800060,0xff000000);
        write_reg16(0x800064,0x07ff);
        //change system clk to 240/5=48
        write_reg8 (0x800066,0x25);
        write_reg8 (0x800067,0x81);
        emi_test_tx_init ();

        write_reg32 (0x8004e8, 0x1c7930cd); //auto mode, txcyc0 = 0
        WriteAnalogReg(0x9a,0xff);

        /* Start EMI testing */
        ev_enable_poll(EV_POLL_EMI_TEST);
        break;

    case CMD_ID_STOP_TX_EMI:
        rf_tx_mode = RF_TX_MODE_NORMAL;
        ev_disable_poll(EV_POLL_EMI_TEST);
        rf_setTrxState(RF_STATE_RX);
        break;

    default:
        bufm_free(arg);
        return;
    }

    

    /* send response to host */
    rsp[0] = 2;
    rsp[1] = cmdPayload->cmdId;
    rsp[2] = 0; // success;

    bufm_free(arg);
    sendCmdToTH(rsp, 3);
}


/*********************************************************************
 * @fn      phyTest_host2testReq
 *
 * @brief   Initialize the PHY test harness
 *
 * @param  none
 *
 * @return  none
 */
void phyTest_host2testReq(u8* pData)
{
    phyTest_cmd_handler(pData);
}


int phyTest_tx(void* arg)
{
	phyTest_v->txCnt++;
    rf_tx((u8*)phyTest_v->txBuf, phyTest_v->txLen);
    return -1;
}


void phyTest_txPrint (void* arg)
{
    u8 status = (u8)arg;
    u8 *buf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
    u8 *p = buf;

    *p++ = 2;
    *p++ = CMD_ID_TX;
    *p++ = status;

    sendCmdToTH(buf, p-buf);
}


void phyTest_rxPrint (u8 status, u8 rssi)
{
    u8 *buf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
    u8 *p = buf;

    *p++ = 4;
    *p++ = CMD_ID_RX;
    *p++ = status;
    *p++ = rssi;
    *p++ = rf_getLqi(rssi);

    sendCmdToTH(buf, p-buf);
}

void phyTest_txCb(void* status)
{
    if(phyTest_v->txNum > 1) {
        ev_on_timer(&phyTest_v->sendDataTimer, phyTest_v->txTimerInterval);
    } else if (phyTest_v->txNum == 1) {
        POST_TASK(phyTest_txPrint, (void*)2);
        phyTest_v->txNum--;
        return;
    }

    if(phyTest_v->txNum != 0xFFFFFFFF) {
        phyTest_v->txNum--;
    }

    POST_TASK(phyTest_txPrint, (void*)status);
}



void phyTest_rxCb(void* arg)
{
    u8 status;
    u8 *p;
    u8 rssi;
    rx_buf_t* rxEvt = (rx_buf_t*)arg;

#if (MCU_CORE_TYPE != MCU_CORE_5320)
    p = bufm_getHeadPtr(rxEvt->rxBuf);
#else
    p = rxEvt->rxBuf;
#endif
    
    if(NULL == phyTest_v->rxTgtBuf) {
        phyTest_v->rxTgtBuf = &(defPayload[5]);
    }

    rssi = *(p+4);
    status = memcmp(p+13, phyTest_v->rxTgtBuf, rxEvt->len - 2);

#if (MCU_CORE_TYPE != MCU_CORE_5320)    
    bufm_free(rxEvt->rxBuf);
#endif

    if (status) {
        phyTest_v->rxFailCnt++;
    } else {
        phyTest_v->rxSuccCnt++;
    }
    
	phyTest_rxPrint(status, rssi);
    rf_setTrxState(RF_STATE_RX);
 
}





/*******************Initialization Functions Implementation******************************/


/*********************************************************************
 * @fn      phyTest_init
 *
 * @brief   Initialize the PHY test harness
 *
 * @param   none
 *
 * @return  none
 */
void phyTest_init(void)
{
    u8 *pBackupBuf;

    /* Init RF parameters */
    rf_regProtocolSpecific(&rfTest_funcs);
    rf_init();
    rf_setCBFunc(phyTest_txCb, phyTest_rxCb);

    /* Set RX buffer */
    #if 0
    pBackupBuf = bufm_getHeadPtr(bufm_allocate(DFLT_LARGE_BUF_SIZE));
    if ( NULL == pBackupBuf ) {
	    while(1);
    }
    rf_setRxBuf(pBackupBuf);
    pBackupBuf = bufm_getHeadPtr(bufm_allocate(DFLT_LARGE_BUF_SIZE));
    if ( NULL == pBackupBuf ) {
	    while(1);
    }
    rf_setRxBackupBuf(pBackupBuf);
    #endif



    phyTest_v->sendDataTimer.cb = phyTest_tx;
    phyTest_v->txBuf = defPayload;
    phyTest_v->txLen = 27;
    phyTest_v->rxTgtBuf = defPayload;


    /* Register EMI test poll task. */
    ev_on_poll(EV_POLL_EMI_TEST, emi_task);
    ev_disable_poll(EV_POLL_EMI_TEST);
}

/*********************************************************************
 * @fn      user_init
 *
 * @brief   user application level initialization
 *
 * @param   none
 *
 * @return  none
 */
void user_init(void)
{
    phyTest_init();
	TH_trxInit(phyTest_host2testReq);
}


/*********************************************************************
 * @fn      app_idle_handler
 *
 * @brief   Add to make it compatible with other need PMU projects
 *
 * @param   none
 *
 * @return  none
 */
void app_idle_handler(void)
{
}



#endif  /* __PROJECT_PHY_TEST__ */
