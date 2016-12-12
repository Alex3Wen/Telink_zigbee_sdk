#include "../../proj/tl_common.h"

#if __PROJECT_PHY_TEST__

/**********************************************************************
 * INCLUDES
 */
#include "../../rf/rf.h"
#include "../../proj_lib/rf_drv.h"


/**********************************************************************
 * LOCAL CONSTANTS
 */




/**********************************************************************
 * LOCAL TYPES
 */


#if RF_STATISTIC_ENABLE
typedef struct {
    u32 rxCnt;
    u32 rxGarbageCnt;

    u32 txFinishCnt;
} rf_statistic_t;
#endif  /* RF_STATISTIC_ENABLE */


/**********************************************************************
 * LOCAL VARIABLES
 */
extern u8 rf_rx_buf1[];
extern u8 rf_rx_buf2[];
extern u8 rx_tx_buf_index;   

/* Variables defined in the rf driver */
extern u8*       rf_rxBuf;
extern u8*       rf_rxBackupBuf;
extern rf_txCB_t rf_txCbFunc;
extern rf_rxCB_t rf_rxCbFunc;
extern u8        rf_txPower;
extern u8        rf_lastRssi;
u8 _attribute_aligned_(4) rf_ack_buf[12];


/* Used in the upper layer stack */
volatile u8 soft_rssi;

rx_buf_t rf_rxEvt;

#if RF_STATISTIC_ENABLE
rf_statistic_t rf_statistic;
#endif


/**********************************************************************
 * LOCAL FUNCTIONS
 */
void rfTest_reset(void)
{
    /* Reset ack buf */
    memset(rf_ack_buf, 0, 12);
    rf_ack_buf[0] = 4;
    rf_ack_buf[4] = 5;
    rf_ack_buf[0+5] = 0x02;
    rf_ack_buf[1+5] = 0x00;

#if RF_STATISTIC_ENABLE
    memset(&rf_statistic, 0, sizeof(rf_statistic_t));
#endif

}

void rfTest_init(void)
{
	u8 *pBackupBuf;
    rfTest_reset();

    /* Initialize RX buffer */
	rx_tx_buf_index = 0;
	rf_setRxBuf(rf_rx_buf1);

#ifndef WIN32
	/* Initialize RX backup buffer */
	rx_tx_buf_index ^= 1;
	pBackupBuf = rf_rx_buf2;
	rf_setRxBackupBuf(pBackupBuf);
#endif
}


void rfTest_set(u8 id, u8 *pValue, u8 len)
{
    switch(id) {
        
    }
}





/*********************************************************************
 * @fn      rf_rx_irq_handler
 *
 * @brief   RX irq handler
 *
 * @param   none
 *
 * @return  none
 */
void rf_rx_irq_handler(void)
{
    u8 len;

    /* Received data is already the rx buffer */
    u8 *p = rf_rxBuf;
    
    /* Set 1 to clear the interrupt flag */
    reg_rf_rx_status = FLD_RF_RX_INTR;

    /* Disable the dma during RX isr, because the memory 
       may be changed  by DMA*/
    dma_channel_disable_all();
	
	if (RF_IS_CRC_CORRECT(p)) {
        
    #if (RF_STATISTIC_ENABLE)
	    rf_statistic.rxCnt++;
    #endif
    
		rf_lastRssi = p[4];
		len = RF_ACTUAL_PAYLOAD_LEN(p);

#if (MCU_CORE_TYPE != MCU_CORE_5320)
        /* Use the backup buffer to receive next packet */		
		rf_rxBuf = rf_rxBackupBuf;

        *((u32*)rf_rxBuf) = 0;
		rf_rxBuf[12] = 1;
        
		reg_dma_rf_rx_addr = (u16)(u32)(rf_rxBuf);
		dma_channel_enable_all();

        rf_rxBackupBuf = bufm_getHeadPtr(bufm_allocate(DFLT_LARGE_BUF_SIZE));
        if (!rf_rxBackupBuf) {
            while(1);
        }

        /* Make a new rx event and let upper layer to handle it */
        rf_rxEvt.rxBuf = ((bufferItem_t*)p)->data;
        rf_rxEvt.len = len;
        rf_rxEvt.timestamp = RF_GET_TIMESTAMP(p);
        if (rf_rxCbFunc) {
            POST_TASK(rf_rxCbFunc, (void*)&rf_rxEvt);
        }
#else
        rx_tx_buf_index ^= 1;
        if ( rx_tx_buf_index == 0 ) {
            rf_rxBuf = rf_rx_buf1;
            rf_rxBackupBuf = rf_rx_buf2;
        } else {
            rf_rxBuf = rf_rx_buf2;
            rf_rxBackupBuf = rf_rx_buf1;
        }

        reg_dma_rf_rx_addr = (u16)(u32)(rf_rxBuf);
        *((u32*)(rf_rxBuf)) = 0;
		dma_channel_enable_all();

        /* Make a new rx event and let upper layer to handle it */
        rf_rxEvt.rxBuf = p;
        rf_rxEvt.len = len;
        rf_rxEvt.timestamp = RF_GET_TIMESTAMP(p);
        if (rf_rxCbFunc) {
            POST_TASK(rf_rxCbFunc, (void*)&rf_rxEvt);
        }
#endif
	
	} else {
	
	#if (RF_STATISTIC_ENABLE)
	    /* Not ZigBee packet, drop the frame, continue receive */
		rf_statistic.rxGarbageCnt++;
    #endif
		*((u32*)(rf_rxBuf)) = 0;
		dma_channel_enable_all();
		
	}



}



/*********************************************************************
 * @fn      rf_tx_irq_handler
 *
 * @brief   Tx Interrupt handler for RF module.
 *
 * @param   none
 *
 * @return  none
 */
void rf_tx_irq_handler(void)
{
    /* Set to clear the interrupt flag */
    reg_rf_rx_status = FLD_RF_TX_INTR;

#if (RF_STATISTIC_ENABLE)
    /* Not ZigBee packet, drop the frame, continue receive */
	rf_statistic.txFinishCnt++;
#endif

    /* Tx Packet Success */
    rf_txCbFunc((void*)SUCCESS);
}



u32 rfTest_getTxFinishCnt(void)
{
#if (RF_STATISTIC_ENABLE)
	return rf_statistic.txFinishCnt;
#endif
	return 0;
}

u32 rfTest_getRxCnt(void)
{
#if (RF_STATISTIC_ENABLE)
	return rf_statistic.rxCnt;
#endif
	return 0;
}

u32 rfTest_getRxGarbageCnt(void)
{
#if (RF_STATISTIC_ENABLE)
	return rf_statistic.rxGarbageCnt;
#endif
	return 0;
}

void rfTest_resetStatistic(void)
{
#if (RF_STATISTIC_ENABLE)
	memset((u8*)&rf_statistic, 0, sizeof(rf_statistic));
#endif
}

#endif





