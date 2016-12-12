#pragma once


/*********************************************************************
 * CONSTANTS
 */

/* Command ID */
// Client generated command
#define ZCL_CMD_ENROLL_RSP                                0x00

// Server generated command
#define ZCL_CMD_STATUS_CHANGE_NOTIFY                      0x00
#define ZCL_CMD_ENROLL_REQ                                0x01


/* Attribute ID */
#define ZCL_ATTRID_ZONE_STATE                             0x0000
#define ZCL_ATTRID_ZONE_TYPE                              0x0001
#define ZCL_ATTRID_ZONE_STATUS                            0x0002
#define ZCL_ATTRID_IAS_CIE_ADDR                           0x0010

/* Zone States Definition */
#define ZONE_STATE_NOT_ENROLLED                           0x00
#define ZONE_STATE_ENROLLED                               0x01


/* Zone Types Definition */
#define ZONE_TYPE_STANDARD_CIE                            0x0000
#define ZONE_TYPE_MOTION_SENSOR                           0x000D
#define ZONE_TYPE_CONTACT_SWITCH                          0x0015
#define ZONE_TYPE_FIRE_SENSOR                             0x0028
#define ZONE_TYPE_WATER_SENSOR                            0x002A
#define ZONE_TYPE_GAS_SENSOR                              0x002B
#define ZONE_TYPE_PERSONAL_EMERGENCY_DEV                  0x002C
#define ZONE_TYPE_MOVEMENT_SENSOR                         0x002D
#define ZONE_TYPE_REMOTE_CONTROL                          0x010F
#define ZONE_TYPE_KEY_FOB                                 0x0115
#define ZONE_TYPE_KEY_PAD                                 0x021D
#define ZONE_TYPE_STANDARD_WARNING_DEV                    0x0225
#define ZONE_TYPE_INVALID_TYPE                            0xFFFF

/* Zone Status Bitmap */
#define ZONE_STATUS_BIT_ALARM1                            0x0001
#define ZONE_STATUS_BIT_ALARM2                            0x0002
#define ZONE_STATUS_BIT_TAMPER                            0x0004
#define ZONE_STATUS_BIT_BATTERY                           0x0008
#define ZONE_STATUS_BIT_SUPERVISION_REPORTS               0x0010
#define ZONE_STATUS_BIT_RESTORE_REPORTS                   0x0020
#define ZONE_STATUS_BIT_TROUBLE                           0x0040
#define ZONE_STATUS_BIT_AC_MAINS                          0x0080

/* Enroll Response Code */
#define ZONE_ENROLL_SUCC                                  0x00
#define ZONE_ENROLL_NOT_SUPPORTED                         0x01
#define ZONE_ENROLL_NOT_ENROLL_PERMIT                     0x02
#define ZONE_ENROLL_TOO_MANY_ZONE                         0x03

/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */

/* Command Callback Function Type */
typedef void (*zcl_enrollRspCb_t)( u16 identifyTime ); // number of seconds the device will continue to identify itself

typedef struct {
	zcl_enrollRspCb_t    identifyCbFunc;
} zcl_iasZone_AppCallbacks_t;

/*********************************************************************
 * Public Functions
 */
#ifdef ZCL_IAS_ZONE
void zcl_iasZone_regCbFunc(zcl_iasZone_AppCallbacks_t* cb);
#endif

void zcl_iasZone_enrollReq(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 zoneType, u16 manuCode);
void zcl_iasZone_enrollRsp(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 enrollRspCode, u8 zoneID);
void zcl_iasZone_statusChangeNotify(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 zoneStatus, u8 extStatus);

#ifdef ZCL_IAS_ZONE
// internal use
rst_t zcl_iasZone_registerCluster(void);
#endif  /* USE_ZCL_ONOFF_ATTR */