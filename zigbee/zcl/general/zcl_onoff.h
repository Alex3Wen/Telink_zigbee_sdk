#pragma once


/*********************************************************************
 * CONSTANTS
 */

/* Command ID */
#define ZCL_CMD_ONOFF_OFF                                 0x00
#define ZCL_CMD_ONOFF_ON                                  0x01
#define ZCL_CMD_ONOFF_TOGGLE                              0x02

/* Attribute ID */
#define ZCL_ATTRID_ONOFF                                  0x0000

/*********************************************************************
 * ENUMS
 */
enum zcl_onoff_state {
	ZCL_ONOFF_STATUS_OFF        = 0x00,
	ZCL_ONOFF_STATUS_ON         = 0x01,
};


/*********************************************************************
 * TYPES
 */

/* Command Callback Function Type */
typedef void (*zcl_OnOffCb_t)( u8 cmd );

typedef struct {
	zcl_OnOffCb_t    onOffCbFunc;
} zcl_onOff_AppCallbacks_t;



/*********************************************************************
 * GLOBAL VARIABLES
 */

#ifdef ZCL_ON_OFF
extern u8 zcl_attr_onoff;
extern zclAttrInfo_t onoff_attrTbl[];
#endif


/*********************************************************************
 * Public Functions
 */
#ifdef ZCL_ON_OFF
rst_t zcl_onOff_register(u8 attrNum, zclAttrInfo_t* pAttrTbl, zcl_onOff_AppCallbacks_t* cb);
#endif
void zcl_onOff_on(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);
void zcl_onOff_off(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);
void zcl_onOff_toggle(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);
void zcl_onOff_sendCmd(u8 cmd, u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);

