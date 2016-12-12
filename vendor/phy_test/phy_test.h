
#pragma  once
#pragma pack(1)


#define DEFAULT_TX_LEN 27


/**
 *  @brief Definition for Phy Test command ID
 */
enum {
    CMD_ID_TX = 1,
    CMD_ID_RX,
    CMD_ID_SET_TX_PAYLOAD,
    CMD_ID_SET_RX_TARGET_PAYLOAD,
    CMD_ID_SET_TX_POWER,
    CMD_ID_SET_CHANNEL,
    CMD_ID_GET_CCA,
    CMD_ID_GET_ED,
    CMD_ID_GET_LQI,
    CMD_ID_GET_RSSI,
    CMD_ID_START_DETECT_RSSI,
    CMD_ID_STOP_RSSI,
    CMD_ID_GET_TX_STATISTIC,
    CMD_ID_GET_RX_STATISTIC,
    CMD_ID_RESET_STATISTIC,
    CMD_ID_TX_CARRIER,
    CMD_ID_TX_CONTINUED_ZB,
    CMD_ID_STOP_TX_EMI,
};


typedef struct phyTest_cmd_tag {
    u8 length; /*not include itself*/
    u8 cmdId;
    u8 payload[1];
} phyTest_cmd_t;







