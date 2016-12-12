#pragma once

#include "../include/zb_types.h"
#include "../zbapi/zb_api.h"


/*********************************************************************
 * CONSTANTS
 */

/*** Foundation Command IDs ***/
#define ZCL_CMD_READ                                    0x00
#define ZCL_CMD_READ_RSP                                0x01
#define ZCL_CMD_WRITE                                   0x02
#define ZCL_CMD_WRITE_UNDIVIDED                         0x03
#define ZCL_CMD_WRITE_RSP                               0x04
#define ZCL_CMD_WRITE_NO_RSP                            0x05
#define ZCL_CMD_CONFIG_REPORT                           0x06
#define ZCL_CMD_CONFIG_REPORT_RSP                       0x07
#define ZCL_CMD_READ_REPORT_CFG                         0x08
#define ZCL_CMD_READ_REPORT_CFG_RSP                     0x09
#define ZCL_CMD_REPORT                                  0x0a
#define ZCL_CMD_DEFAULT_RSP                             0x0b
#define ZCL_CMD_DISCOVER                                0x0c
#define ZCL_CMD_DISCOVER_RSP                            0x0d
#define ZCL_CMD_MAX                                     ZCL_CMD_DISCOVER_RSP


/*** Frame Control bit mask ***/
#define ZCL_FRAME_CONTROL_TYPE                          0x03
#define ZCL_FRAME_CONTROL_MANU_SPECIFIC                 0x04
#define ZCL_FRAME_CONTROL_DIRECTION                     0x08
#define ZCL_FRAME_CONTROL_DISABLE_DEFAULT_RSP           0x10

/*** Frame Types ***/
#define ZCL_FRAME_TYPE_PROFILE_CMD                      0x00
#define ZCL_FRAME_TYPE_SPECIFIC_CMD                     0x01

/*** Frame Client/Server Directions ***/
#define ZCL_FRAME_CLIENT_SERVER_DIR                     0x00
#define ZCL_FRAME_SERVER_CLIENT_DIR                     0x01

/*** Telink Manufacturer Code ***/
#define TELINK_MANUFACTURER_CODE                        0x248A


/*** Default TX option and radius settings ***/
#define DFLT_APS_TX_OPTIONS                             0x00
#define DFLT_APS_RADIUS                                 0xf


/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */

// Attributes Information
struct zclAttrInfo {
	u16 id;                     /*!< Attribute ID */
	u8  type;                   /*!< Attribute type */
	u8  access;                 /*!< Attribute access control */
	u8 * data;
};
typedef struct zclAttrInfo zclAttrInfo_t;


union zclFrmCtrl {
	struct {
		u8 type:2;              /*!< ZCL Frame type  */
		u8 manufSpec:1;         /*!< Manufacturer specific frame */
		u8 dir:1;               /*!< Direction. 0:client->server, 1:server->client  */
		u8 disDefResp:1;        /*!< Disable default response */
		u8 reserved:3;          /*!< reserved */
	} bf;                       /*!< bit access field */
	u8 byte;                    /*!< byte access field */
};
typedef union zclFrmCtrl zclFrmCtrl_t;

struct zclHdr {
	zclFrmCtrl_t frmCtrl;       /*!< Frame control field structure */
	u8 seqNum;                  /*!< Sequence number - used to identify response frame */
	u8 cmd;                     /*!< Command ID */
	u8 payld[1];                /*!< Payload */
};
typedef struct zclHdr zclHdr_t;

struct zclHdrExt {
	zclFrmCtrl_t frmCtrl;       /*!< Frame control field structure */
	u16 manufCode;              /*!< Manufacturer code */
	u8 seqNum;                  /*!< Sequence number - used to identify response frame */
	u8 cmd;                     /*!< Command ID */
	u8 payld[1];                /*!< Payload */
};
typedef struct zclHdrExt zclHdrExt_t;


// Read Attribute Command format
typedef struct
{
	u8  numAttr;            // number of attributes in the list
	u16 attrID[1];          // supported attributes list - this structure should
	// be allocated with the appropriate number of attributes.
} zclReadCmd_t;

// Read Attribute Response Status record
typedef struct
{
	u16 attrID;            // attribute ID
	u8  status;            // should be ZCL_STATUS_SUCCESS or error
	u8  dataType;          // attribute data type
	u8  *data;             // this structure is allocated, so the data is HERE
	// - the size depends on the attribute data type
} zclReadRspStatus_t;

// Read Attribute Response Command format
typedef struct
{
	u8              numAttr;     // number of attributes in the list
	zclReadRspStatus_t attrList[1];  // attribute status list
} zclReadRspCmd_t;


// Write Attribute record
typedef struct
{
	u16 attrID;             // attribute ID
	u8  dataType;           // attribute data type
	u8  *attrData;          // this structure is allocated, so the data is HERE
	//  - the size depends on the attribute data type
} zclWriteRec_t;

// Write Attribute Command format
typedef struct
{
	u8            numAttr;     // number of attribute records in the list
	zclWriteRec_t attrList[1];  // attribute records
} zclWriteCmd_t;

// Write Attribute Status record
typedef struct
{
	u8  status;             // should be ZCL_STATUS_SUCCESS or error
	u16 attrID;             // attribute ID
} zclWriteRspStatus_t;

// Write Attribute Response Command format
typedef struct
{
	u8               numAttr;     // number of attribute status in the list
	zclWriteRspStatus_t attrList[1];  // attribute status records
} zclWriteRspCmd_t;

// Configure Reporting Command format
typedef struct
{
	u8  direction;          // to send or receive reports of the attribute
	u16 attrID;             // attribute ID
	u8  dataType;           // attribute data type
	u16 minReportInt;       // minimum reporting interval
	u16 maxReportInt;       // maximum reporting interval
	u16 timeoutPeriod;      // timeout period
	u8  *reportableChange;  // reportable change (only applicable to analog data type)
	// - the size depends on the attribute data type
} zclCfgReportRec_t;

typedef struct
{
	u8             numAttr;    // number of attribute IDs in the list
	zclCfgReportRec_t attrList[1]; // attribute ID list
} zclCfgReportCmd_t;

// Attribute Status record
typedef struct
{
	u8  status;             // should be ZCL_STATUS_SUCCESS or error
	u8  direction;          // whether attributes are reported or reports of attributes are received
	u16 attrID;             // attribute ID
} zclCfgReportStatus_t;

// Configure Reporting Response Command format
typedef struct
{
	u8                numAttr;    // number of attribute status in the list
	zclCfgReportStatus_t attrList[1]; // attribute status records
} zclCfgReportRspCmd_t;

// Read Reporting Configuration Command format
typedef struct
{
	u8  direction; // to send or receive reports of the attribute
	u16 attrID;    // attribute ID
} zclReadReportCfgRec_t;

typedef struct
{
	u8                 numAttr;    // number of attributes in the list
	zclReadReportCfgRec_t attrList[1]; // attribute ID list
} zclReadReportCfgCmd_t;

// Attribute Reporting Configuration record
typedef struct
{
	u8  status;             // status field
	u8  direction;          // to send or receive reports of the attribute
	u16 attrID;             // attribute ID
	u8  dataType;           // attribute data type
	u16 minReportInt;       // minimum reporting interval
	u16 maxReportInt;       // maximum reporting interval
	u16 timeoutPeriod;      // timeout period
	u8  *reportableChange;  // reportable change (only applicable to analog data type)
	// - the size depends on the attribute data type
} zclReportCfgRspRec_t;

// Read Reporting Configuration Response Command format
typedef struct
{
	u8                numAttr;    // number of records in the list
	zclReportCfgRspRec_t attrList[1]; // attribute reporting configuration list
} zclReadReportCfgRspCmd_t;

// Attribute Report
typedef struct
{
	u16 attrID;             // atrribute ID
	u8  dataType;           // attribute data type
	u8  *attrData;          // this structure is allocated, so the data is HERE
	// - the size depends on the data type of attrID
} zclReport_t;

// Report Attributes Command format
typedef struct
{
	u8       numAttr;       // number of reports in the list
	zclReport_t attrList[1];    // attribute report list
} zclReportCmd_t;

// Default Response Command format
typedef struct
{
	u16 clusterID;
	u8  commandID;
	u8  statusCode;
} zclDefaultRspCmd_t;

// Discover Attributes Command format
typedef struct
{
	u16 startAttr;          // specifies the minimum value of the identifier
	// to begin attribute discovery.
	u8  maxAttrIDs;         // maximum number of attribute IDs that are to be
	// returned in the resulting response command.
} zclDiscoverCmd_t;

// Attribute Report info
typedef struct
{
	u16 attrID;             // attribute ID
	u8  dataType;           // attribute data type (see Table 17 in Spec)
} zclDiscoverInfo_t;

// Discover Attributes Response Command format
typedef struct
{
	u8             discComplete; // whether or not there're more attributes to be discovered
	u8             numAttr;      // number of attributes in the list
	zclDiscoverInfo_t attrList[1];   // supported attributes list
} zclDiscoverRspCmd_t;

// String Data Type
typedef struct
{
	u8 strLen;
	u8 *pStr;
} UTF8String_t;


typedef struct {
	u8 dstAddrMode;
	u8 dstEp;
	zb_addr_t dstAddr;
	u16 profileId;
	u8  txOptions;
	u8  radius;
} epInfo_t;

// Incoming ZCL message, this buffer will be allocated, cmd will point to the
// the command record.
typedef struct
{
	apsdeDataInd_t        *msg;        // incoming message
	zclHdrExt_t           hdr;         // ZCL header parsed
	u8                    *pData;      // pointer to data after header
	u16                   pDataLen;    // length of remaining data
	void                  *attrCmd;    // pointer to the parsed attribute or command
} zclIncoming_t;

// Function pointer type to handle incoming messages.
//   msg - incoming message
//   logicalClusterID - logical cluster ID
typedef u8 (*cluster_cmdHdlr_t)( zclIncoming_t *pInHdlrMsg );


/* Command Callback Function Type */
typedef void (*zcl_readRspCb_t)( zclReadRspCmd_t *pCmd );
typedef void (*zcl_writeRspCb_t)( zclWriteRspCmd_t *pCmd);
typedef void (*zcl_dfltRspCb_t)( zclDefaultRspCmd_t *pCmd);

typedef struct {
	zcl_readRspCb_t    readRspCbFunc;
	zcl_writeRspCb_t   writeRspCbFunc;
	zcl_dfltRspCb_t    dfltRspCbFunc;
} zcl_foundation_AppCallbacks_t;

typedef void (*zcl_hookFn_t)( zclIncoming_t *pInHdlrMsg );



/*********************************************************************
 * Public Functions
 */

/*********************************************************************
 * @fn      zcl_reset
 *
 * @brief   Reset ZCL Module
 *
 * @param   None
 *
 * @return  None
 */
void zcl_reset(void);

/*********************************************************************
 * @fn      zcl_init
 *
 * @brief   Initialize ZCL layer
 *
 * @param   None
 *
 * @return  None
 */
void zcl_init(zcl_foundation_AppCallbacks_t *zcl_foundationCb);

/*********************************************************************
 * @fn      zcl_registerHook
 *
 * @brief   Register the ZCL hook function
 *
 * @param   fn The handler function after hook the message out
 *
 * @return  None
 */
void zcl_registerHook(zcl_hookFn_t fn);

/*********************************************************************
 * @fn      zcl_registerCluster
 *
 * @brief   Register the attribute table to ZCL
 *
 * @param   clusterId Specified cluster ID
 * @param   attrNum   Specified attribute number in the cluster
 * @param   pAttrTbl  Specified attributes
 *
 * @return  Status
 */
rst_t zcl_registerCluster(u16 clusterId, u8 attrNum, zclAttrInfo_t* pAttrTbl, cluster_cmdHdlr_t cmdHdlrFn);

/*********************************************************************
 * @fn      zcl_SendCommand
 *
 * @brief   Used to send Profile and Cluster Specific Command messages.
 *
 *          NOTE: The calling application is responsible for incrementing
 *                the Sequence Number.
 *
 * @param   srcEp - source endpoint
 * @param   pDstEpInfo - destination endpoint information
 * @param   clusterID - cluster ID
 * @param   cmd - command ID
 * @param   specific - whether the command is Cluster Specific
 * @param   direction - client/server direction of the command
 * @param   disableDefaultRsp - disable Default Response command
 * @param   manuCode - manufacturer code for proprietary extensions to a profile
 * @param   seqNumber - identification number for the transaction
 * @param   cmdFormatLen - length of the command to be sent
 * @param   cmdFormat - command to be sent
 *
 * @return  None
 */
void zcl_sendCmd(u8 srcEp, epInfo_t* pDstEpInfo, u16 clusterId, u8 cmd, u8 specific,
				 u8 direction, u8 disableDefaultRsp, u8 manuCode, u8 seqNo, u8 cmdPldLen, u8* cmdPld);

/*********************************************************************
 * @fn      zcl_rx_handler
 *
 * @brief   Receive handler for data from APS/AF layer
 *
 * @param   pData     Received data
 *
 * @return  None
 */
void zcl_rx_handler(u8* pData);

rst_t zcl_getAttrVal(u16 clusterId, u16 attrId, u8 *len, u8* val);

rst_t zcl_setAttrVal(u16 clusterId, u16 attrId, u8* val);

void zcl_read( u8 srcEp, epInfo_t* pDstEpInfo, u16 clusterId, u8 disableDefaultRsp, u8 direction, u8 seqNo, zclReadCmd_t *readCmd);

void zcl_write( u8 srcEp, epInfo_t* pDstEpInfo, u16 clusterId, u8 disableDefaultRsp, u8 direction, u8 seqNo, zclWriteCmd_t *writeCmd);