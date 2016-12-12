/**************************************************************************************************
  Filename:       mac_trx_api.h
  Revised:        $Date: 2013-05-30 $

  Description:    This file here is for the compatible with some internal structure 
**************************************************************************************************/

#pragma once

#if (USE_ZBOSS_MAC)

typedef enum {
	MAC_SUCCESS                 = 0x00,                /**< Operation successful */
    MAC_PAN_AT_CAPACITY         = 0x1,
    MAC_PAN_ACCESS_DENIED       = 0x2,
	MAC_AUTOACK_PENDING_ALL_ON  = 0xFE,                /**< The AUTOPEND pending all is turned on */
    MAC_AUTOACK_PENDING_ALL_OFF = 0xFF,                /**< The AUTOPEND pending all is turned off */
    MAC_BEACON_LOSS             = 0xE0,                /**< The beacon was lost following a synchronization request */
    MAC_CHANNEL_ACCESS_FAILURE  = 0xE1,                /**< The operation or data request failed because of
                                                            activity on the channel */
    MAC_COUNTER_ERROR           = 0xDB,                /**< The frame counter purportedly applied by the originator of
                                                            the received frame is invalid */
    MAC_DENIED                  = 0xE2,                /**< The MAC was not able to enter low power mode. */
    MAC_DISABLE_TRX_FAILURE     = 0xE3,                /**< Unused */
    MAC_FRAME_TOO_LONG          = 0xE5,                /**< The received frame or frame resulting from an operation
                                                            or data request is too long to be processed by the MAC */
    MAC_IMPROPER_KEY_TYPE       = 0xDC,                /**< The key purportedly applied by the originator of the
                                                            received frame is not allowed */
    MAC_IMPROPER_SECURITY_LEVEL = 0xDD,                /**< The security level purportedly applied by the originator of
                                                            the received frame does not meet the minimum security level */
    MAC_INVALID_ADDRESS         = 0xF5,                /**< The data request failed because neither the source address nor
                                                            destination address parameters were present */
    MAC_INVALID_GTS             = 0xE6,                /**< Unused */
    MAC_INVALID_HANDLE          = 0xE7,                /**< The purge request contained an invalid handle */
    MAC_INVALID_INDEX           = 0xF9,                /**< Unused */
    MAC_INVALID_PARAMETER       = 0xE8,                /**< The API function parameter is out of range */
    MAC_LIMIT_REACHED           = 0xFA,                /**< The scan terminated because the PAN descriptor storage limit
                                                            was reached */
    MAC_NO_ACK                  = 0xE9,                /**< The operation or data request failed because no
                                                            acknowledgement was received */
    MAC_NO_BEACON               = 0xEA,                /**< The scan request failed because no beacons were received or the
                                                            orphan scan failed because no coordinator realignment was received */
    MAC_NO_DATA                 = 0xEB,                /**< The associate request failed because no associate response was received
                                                            or the poll request did not return any data */
    MAC_NO_SHORT_ADDRESS        = 0xEC,                /**< The short address parameter of the start request was invalid */
    MAC_ON_TIME_TOO_LONG        = 0xF6,                /**< Unused */
    MAC_OUT_OF_CAP              = 0xED,                /**< Unused */
    MAC_PAN_ID_CONFLICT         = 0xEE,                /**< A PAN identifier conflict has been detected and
                                                            communicated to the PAN coordinator */
    MAC_PAST_TIME               = 0xF7,                /**< Unused */
    MAC_READ_ONLY               = 0xFB,                /**< A set request was issued with a read-only identifier */
    MAC_REALIGNMENT             = 0xEF,                /**< A coordinator realignment command has been received */
    MAC_SCAN_IN_PROGRESS        = 0xFC,                /**< The scan request failed because a scan is already in progress */
    MAC_SECURITY_ERROR          = 0xE4,                /**< Cryptographic processing of the received secure frame failed */
    MAC_SUPERFRAME_OVERLAP      = 0xFD,                /**< The beacon start time overlapped the coordinator transmission time */
    MAC_TRACKING_OFF            = 0xF8,                /**< The start request failed because the device is not tracking
                                                            the beacon of its coordinator */
    MAC_TRANSACTION_EXPIRED     = 0xF0,                /**< The associate response, disassociate request, or indirect
                                                            data transmission failed because the peer device did not respond
                                                            before the transaction expired or was purged */
    MAC_TRANSACTION_OVERFLOW    = 0xF1,                /**< The request failed because MAC data buffers are full */
    MAC_TX_ACTIVE               = 0xF2,                /**< Unused */
    MAC_UNAVAILABLE_KEY         = 0xF3,                /**< The operation or data request failed because the
                                                            security key is not available */
    MAC_UNSUPPORTED_ATTRIBUTE   = 0xF4,                /**< The set or get request failed because the attribute is not supported */
    MAC_UNSUPPORTED_LEGACY      = 0xDE,                /**< The received frame was secured with legacy security which is
                                                            not supported */
    MAC_UNSUPPORTED_SECURITY    = 0xDF,                /**< The security of the received frame is not supported */
    MAC_UNSUPPORTED             = 0x18,                /**< The operation is not supported in the current configuration */
    MAC_BAD_STATE               = 0x19,                /**< The operation could not be performed in the current state */
    MAC_NO_RESOURCES            = 0x1A,                /**< The operation could not be completed because no
                                                            memory resources were available */
    MAC_ACK_PENDING             = 0x1B,                /**< For internal use only */
    MAC_NO_TIME                 = 0x1C,                /**< For internal use only */
    MAC_TX_ABORTED              = 0x1D,                /**< For internal use only */
    MAC_DUPLICATED_ENTRY        = 0x1E,                /**< For internal use only - A duplicated entry is added to the source matching table */
	MAC_INVALID_REQ             = 0x1F,                /**< For internal use only - the primitive and current state is not match */
} mac_sts_t;


/**        
 *  @brief The number of slots contained in any superframe
 */
#define MAC_A_NUM_SUPERFRAME_SLOTS      16

/**        
 *  @brief Number of backoffs forming a superframe slot when the superframe order is equal to 0
 */
#define MAC_A_BASE_SLOT_DURATION        3


#ifdef WIN32
#define MAC_A_BASE_SUPERFRAME_DURATION  (MAC_A_BASE_SLOT_DURATION * MAC_A_NUM_SUPERFRAME_SLOTS)
#else
#define MAC_A_BASE_SUPERFRAME_DURATION  (MAC_A_BASE_SLOT_DURATION * MAC_A_NUM_SUPERFRAME_SLOTS)
#endif


#define MAC_MIN_HDR_LEN                 3
#define MAC_MAX_HDR_LEN                 23
#define TELINK_RF_TX_HDR_LEN            5
#define TELINK_RF_RX_HDR_LEN            13


/**        
 *  @brief Frame control field bit masks
 */
#define MAC_FCF_FRAME_TYPE_MASK         0x0007
#define MAC_FCF_SEC_ENABLED_MASK        0x0008
#define MAC_FCF_FRAME_PENDING_MASK      0x0010
#define MAC_FCF_ACK_REQUEST_MASK        0x0020
#define MAC_FCF_INTRA_PAN_MASK          0x0040
#define MAC_FCF_DST_ADDR_MODE_MASK      0x0C00
#define MAC_FCF_FRAME_VERSION_MASK      0x3000
#define MAC_FCF_SRC_ADDR_MODE_MASK      0xC000

/**        
 *  @brief MAC frame field lengths in bytes
 */
#define MAC_FCF_FIELD_LEN               2       /* frame control field */
#define MAC_SEQ_NUM_FIELD_LEN           1       /* sequence number  */
#define MAC_PAN_ID_FIELD_LEN            2       /* PAN ID  */
#define MAC_EXT_ADDR_FIELD_LEN          8       /* Extended address */
#define MAC_SHORT_ADDR_FIELD_LEN        2       /* Short address */
#define MAC_FCS_FIELD_LEN               2       /* FCS field */


/**        
 *  @brief Frame type
 */
#define MAC_FRAME_TYPE_BEACON           0
#define MAC_FRAME_TYPE_DATA             1
#define MAC_FRAME_TYPE_ACK              2
#define MAC_FRAME_TYPE_COMMAND          3
#define MAC_FRAME_TYPE_MAX_VALID        MAC_FRAME_TYPE_COMMAND

/**        
 *  @brief Frame control field bit positions
 */
#define MAC_FCF_FRAME_TYPE_POS          0
#define MAC_FCF_SEC_ENABLED_POS         3
#define MAC_FCF_FRAME_PENDING_POS       4
#define MAC_FCF_ACK_REQUEST_POS         5
#define MAC_FCF_INTRA_PAN_POS           6
#define MAC_FCF_DST_ADDR_MODE_POS       10
#define MAC_FCF_FRAME_VERSION_POS       12
#define MAC_FCF_SRC_ADDR_MODE_POS       14

/**        
 *  @brief Broadcast PAN ID
 */
#define MAC_PAN_ID_BROADCAST            0xFFFF

#define MAC_ADDR_USE_EXT            0xFFFE  //!< Short address value indicating extended address is used
#define MAC_SHORT_ADDR_BROADCAST    0xFFFF  //!< Broadcast short address
#define MAC_SHORT_ADDR_NONE         0xFFFF  //!< Short address when there is no short address



/**        
 *  @brief Definition of MAC generic frame type, used in both TX and RX
 */
typedef struct {
    u8    primitive;
    union {
        struct {
            u8 cmdID:4;
            u8 fAck:1;                 /*!< Used in TX  */
            u8 fFramePending:1;        /*!< Used in Poll  */
            u8 reserved:2;
        }bf;
        u8 byteVal;
    } flags;
    addr_t srcAddr;
    u16   dstPanId;                    /*!< Destination PAN ID  */

    union {
        /* Used for TX */
        struct {
            u8     psduLen;
            //u8     *psdu;
            u32    psduOffset;
            u8     cnfStatus;
            u8     msduHandle;
            u8     reserved[12];
        } tx;

        /* Used for RX */
        struct {
            u8     msduLen;
            u16    srcPanId;
            addr_t dstAddr;           
            u8     lqi;      
            u32    timestamp;
            u8     frameType;
            u8     dsn;
        } rx;
    } data;

    u8    reserved[15];
    u8    msdu[1];
} mac_genericFrame_t;


typedef void ( *mac_evHandler_t )( u8* pData );


void mac_trxInit(void);
u8 mac_txData(u8 *dataPtr, u8 len);

#endif


