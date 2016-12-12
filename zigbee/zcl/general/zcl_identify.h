#pragma once


/*********************************************************************
 * CONSTANTS
 */

/* Command ID */
// Client generated command
#define ZCL_CMD_IDENTIFY                                  0x00
#define ZCL_CMD_IDENTIFY_QUERY                            0x01

// Server generated command
#define ZCL_CMD_IDENTIFY_QUERY_RSP                        0x00

/* Attribute ID */
#define ZCL_ATTRID_IDENTIFY_TIME                          0x0000

/*********************************************************************
 * ENUMS
 */


/*********************************************************************
 * TYPES
 */

/* Command Callback Function Type */
typedef void (*zcl_identifyCb_t)( u16 identifyTime ); // number of seconds the device will continue to identify itself

typedef struct {
	zcl_identifyCb_t    identifyCbFunc;
} zcl_identify_AppCallbacks_t;



/*********************************************************************
 * GLOBAL VARIABLES
 */
#ifdef ZCL_IDENTIFY
extern u16 zcl_attr_identifyTime;
extern zclAttrInfo_t identify_attrTbl[];
#endif


/*********************************************************************
 * Public Functions
 */
#ifdef ZCL_IDENTIFY
rst_t zcl_identify_register(u8 attrNum, zclAttrInfo_t* pAttrTbl, zcl_identify_AppCallbacks_t* cb);
#endif

void zcl_identify_sendIdentify(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 identifyTime);
void zcl_identify_identifyQuery(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);


