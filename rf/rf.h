#ifndef  __RF_H__ 
#define  __RF_H__

/*********************************************************************
 * CONSTANTS
 */

/**
 * Default RF Channel when power up
 */
#define DFLT_LOGIC_CHANNEL  11

/*
 * Definition for RF TX power
 */
#if(MCU_CORE_TYPE == MCU_CORE_5320)
	#define MAX_RF_TX_POWER        0x07
	#define MIN_RF_TX_POWER        0x00
#elif(MCU_CORE_TYPE == MCU_CORE_5328)
	#define MAX_RF_TX_POWER        0x44
	#define MIN_RF_TX_POWER        0x45
#elif(MCU_CORE_TYPE == MCU_CORE_5332)
    #define MAX_RF_TX_POWER        0x10
    #define MIN_RF_TX_POWER        0x11
#endif



#define CCA_THRESHOLD       -69


/*********************************************************************
 * MACRO
 */
/**
 *  @brief  Macro for flag show ZigBee packet CRC correct
 */
#define ZIGBEE_CRC_CORRECT   0x10

/**
 *  @brief Timestamp is stored on the before of CRC value
 */
#define RF_GET_TIMESTAMP(p)    ( p[p[0]] | (p[p[0]+1]<<8) | (p[p[0]+2]<<16) )

/**
 *  @brief CRC correct flag is stored on the behind of Timestamp
 */
#define RF_IS_CRC_CORRECT(p) (ZIGBEE_CRC_CORRECT == p[p[0]+3])

/**
 *  @brief Over the air packet length
 */
#define RF_ACTUAL_PAYLOAD_LEN(p) (p[12])

/*********************************************************************
 * ENUMS
 */
enum {
    RF_SUCC,
    RF_CSMA_FAILURE,
};

enum {
    RF_RX_OFF,
    RF_RX_ON,
};


enum {
    CCA_ED_ONLY,
    CCA_CS_ONLY,
    CCA_ED_AND_CS,
    CCA_ED_OR_CS,
};


enum {
    RF_STATE_TX,
    RF_STATE_RX,
    RF_STATE_ED,
    RF_STATE_OFF,
};


/*
 * Definition for RF Setting identifier.
 */
enum {
    /* General ID */
    RF_ID_CHANNEL               = 0x00,
    RF_ID_TX_POWER,
    RF_ID_RX_ONOFF,
    RF_ID_GENERAL_END           = 0x9F,
    

    /* Protocol Specific ID*/
    RF_ID_ZIGBEE                = 0xA0,
    RF_ID_MAC_SHORT_ADDR,
    RF_ID_MAC_EXT_ADDR,
    RF_ID_MAC_PANID,
    RF_ID_MAC_FRAME_PENDING,
    RF_ID_MAC_PAN_COORD,
    RF_ID_MAC_RECV_START,

    RF_ID_BLE                   = 0xB0,
};

/*********************************************************************
 * TYPES
 */

/*
 * Definition for RF callback function type
 */
typedef void ( *rf_txCB_t )( void* arg );
typedef void ( *rf_rxCB_t )( void* arg ); 

typedef void ( *rf_protocolSpecificInit_t) (void);
typedef void ( *rf_protocolSpecificReset_t) (void);
typedef void ( *rf_protocolSpecificSet_t) (u8 id, u8 *pValue, u8 len);


/**
 *  @brief  Definition for Telink RX packet format
 */
typedef struct {
    u32 dmaLen;
    u8  rssi;
    u8  rseverd[7];
    u8  payloadLen;
    u8  payload[1];
} rf_recvPkt_t;


/**
 *  @brief  Definition for Telink TX packet format
 */
typedef struct {
    u32 dmaLen;
    u8  rfLen;
    u8  payload[1];
} rf_sendPkt_t;


/*
 * Definition for RF Rx buffer format
 */
typedef struct {
    u8* rxBuf;
    u8  len;
    u8  fPending;
    u8  rssi;
    u8  reserved;
    u32 timestamp;
} rx_buf_t;


/*
 * Definition for Protocol Specific RF functions
 */
typedef struct {
    rf_protocolSpecificInit_t initFunc;
    rf_protocolSpecificReset_t resetFunc;
    rf_protocolSpecificSet_t setFunc;
} rf_specificFunc_t;


/*********************************************************************
 * Public Variables
 */
extern u8 *rf_tx_buf;
extern u8 rf_paEnable;

/*********************************************************************
 * Public Functions
 */


/*********************************************************************
 * @fn      rf_init
 *
 * @brief   Initialize RF module and do the RF power up.
 *
 * @param   none
 *
 * @return  none
 */
void rf_init(void);

/*********************************************************************
 * @fn      rf_setCBFunc
 *
 * @brief   Set TX finish callback function and RX callback function
 *
 * @param   rxCbFunc - The specified RX callback function
 *          txCbFunc - The specified TX callback function
 *
 * @return  none
 */
void rf_setCBFunc(rf_txCB_t rxCbFunc, rf_rxCB_t txCbFunc);

/*********************************************************************
 * @fn      rf_regProtocolSpecific
 *
 * @brief   Register protocol specific RF functions.
 *            Note: This function must be called before rf_init() and rf_reset()
 *
 * @param   txCbFunc - tx done callback function
 * @param   rxCbFunc - rx done callback function
 *
 * @return  none
 */
void rf_regProtocolSpecific(rf_specificFunc_t* funcs);

/*********************************************************************
 * @fn      rf_reset
 *
 * @brief   Reset RF module.
 *
 * @param   none
 *
 * @return  none
 */
void rf_reset(void);


/*********************************************************************
 * @fn      rf_setTrxState
 *
 * @brief   Go to specified state and set related register.
 *
 * @param   state - Specified state
 *
 * @return  none
 */
void rf_setTrxState(u8 state);


/*********************************************************************
 * @fn      rf_setChannel
 *
 * @brief   Set specified channel to RF module.
 *
 * @param   ch - 11~26
 *
 * @return  none
 */
void rf_setChannel(u8 ch);

/*********************************************************************
 * @fn      rf_setTxPower
 *
 * @brief   Set specified transmitted power.
 *
 * @param   txPower - Specified power
 *
 * @return  none
 */
void rf_setTxPower(u8 txPower);


/*********************************************************************
 * @fn      rf_setCCAMode
 *
 * @brief   Set specified mode to CCA.
 *
 * @param   mode - CCA mode
 *
 * @return  none
 */
void rf_setCCAMode(u8 mode);


/*********************************************************************
 * @fn      rf_setCCALevel
 *
 * @brief   Set CCA detect threshold.
 *
 * @param   threshold - the threshold value
 *
 * @return  none
 */
void rf_setCCALevel(u8 threshold);

/*********************************************************************
 * @fn      rf_getRssi
 *
 * @brief   Get RSSI value from last received frame.
 *
 * @param   none
 *
 * @return  rssi value
 */
s8 rf_getRssi(void);

/*********************************************************************
 * @fn      rf_getLqi
 *
 * @brief   Get calculated Link Quality value from specified rssi
 *
 * @param   rssi
 *
 * @return  lqi result
 */
u8 rf_getLqi(u8 rssi);

/*********************************************************************
 * @fn      rf_getED
 *
 * @brief   Get calculated ED value
 *
 * @param   none
 *
 * @return  ed value
 */
u8 rf_getED(void);
void rf_startED(void);
u8 rf_stopED(void);




/*********************************************************************
 * @fn      rf_getCCAState
 *
 * @brief   Set CCA detect threshold.
 *
 * @param   threshold - the threshold value
 *
 * @return  none
 */
u8 rf_getCCAState(void);

/*********************************************************************
 * @fn      rf_enableRx
 *
 * @brief   Turn on/off the receiver if it's not already on/off.
 *
 * @param   fEnable - 1 means on and 0 means off
 *
 * @return  none
 */
void rf_enableRx(u8 fEnable);

/*********************************************************************
 * @fn      rf_tx
 *
 * @brief   Transmit the data through CSMA/CA mechnism.
 *
 * @param   buf - The buffer to be transmitted
 * @param   len - The length of byte to be transmitted
 *
 * @return  none
 */
void rf_tx(u8* buf, u8 len);

/*********************************************************************
 * @fn      rf_ISR
 *
 * @brief   Interrupt handler for RF module. Including TX interrupt and RX interrupt
 *
 * @param   none
 *
 * @return  none
 */
void rf_ISR(void);


u8 rf_performCCA(void);
void rf_setRxBuf(u8* pBuf);
void rf_setRxBackupBuf(u8* pBuf);
u8 *rf_get_recvBuf(void);
void rf_setRxState(u8 fEnable);
/*********************************************************************
 * @fn      rf_set
 *
 * @brief   Set rf parameter according to specified RF ID   
 *
 * @param   id     - The specified RF ID
 *          pValue - The detailed rf parameter
 *          len    - The length will be set to
 *
 * @return  none
 */
void rf_set(u8 id, u8 *pValue, u8 len);




#endif  /* __RF_H__ */
