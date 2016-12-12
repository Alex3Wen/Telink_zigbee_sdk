#ifndef _RF_DRV_H_
#define _RF_DRV_H_

#define DEBUG_COARSETUNE 0
#define DEBUG_DCOC 0
#define DEBUG_TP 0
#define DEBUG_TBL 0

#define RF_CHN_AUTO_CAP     0xff
#define RF_CHN_TABLE         0x80

#define RF_CHANNEL_MAX            16
#define RF_CHANNEL_MASK            (RF_CHANNEL_MAX - 1)

//STATIC_ASSERT_POW2(RF_CHANNEL_MAX);        //  if not, may fail in rf_get_msk_chn and rf_get_sub_chn


extern unsigned char    rfhw_tx_power;
extern const unsigned char    rf_chn[RF_CHANNEL_MAX];
extern unsigned char    cap_tp[RF_CHANNEL_MAX];

typedef struct DCIQ {
        signed char i;
        signed char q;
        int a;
        int th;
} DCIQ;


enum{
    RF_TX_MODE_NORMAL = 0,
    RF_TX_MODE_CARRIER,
    RF_TX_MODE_CONTINUE,
};

#define        RF_SETTING_FROM_SUSPEND            1

void CalibTOS32M (void);

int rf_drv_init (int wakeup_from_suspend);
void RF_resume(void);
void SetRxMode (void);
void SetTxMode (void);
unsigned char TpCal(signed char chn);
unsigned char TxCoarseTunning ();
unsigned char RxCoarseTunning ();
void TxPkt (void* addr);
//#define TxSendPkt    write_reg8 (0x800524, 0x08)
#define TxSendPkt    TxPkt ()


#define        RM_DCI                0x8004cb
#define        RM_DCQ                 0x8004cf

#define        RF_DCOC_DCI_SET(v)    write_reg32 (RM_DCI-3, ((v)<<24) | ((v)<<16) | ((v)<<8) | (v))
#define        RF_DCOC_DCQ_SET(v)    write_reg32 (RM_DCQ-3, ((v)<<24) | ((v)<<16) | ((v)<<8) | (v))
#define        RF_RM_DCI_VALUE        read_reg8(RM_DCI)
#define        RF_RM_DCQ_VALUE        read_reg8(RM_DCQ)


extern u8 rf_tx_mode;
#define RF_TX_MODE_CARRIER_ENABLE            do {rf_tx_mode = RF_TX_MODE_CARRIER;} while(0)
#define RF_TX_MODE_CONTINUE_ENABLE            do {rf_tx_mode = RF_TX_MODE_CONTINUE;} while(0)
#define RF_TX_MODE_NORMAL_ENABLE            do {rf_tx_mode = RF_TX_MODE_NORMAL;} while(0)

extern unsigned char reset_flag;

extern  unsigned long  pll_offset;
extern    void    (*g_rf_func_wait)(void);


#define        SET_RF_TX_DMA_ADR(a)    write_reg16 (0x80050c, a)

void rf_channel_debug_set_tp (void);

extern u8 rf_channel;


typedef struct {
	unsigned int	N;
	int		F;	
	unsigned char	m;
    unsigned char   cap;
} rf_chInfo_t;


void calcRxChInfo(signed char chn, unsigned char set);
void calcTxChInfo(signed char chn, unsigned char set);


#endif
