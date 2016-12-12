
#pragma once

#include "../include/zb_common.h"
#include "../include/zb_zdo.h"
#include "../include/zb_aps_globals.h"
#include "../include/zb_af_globals.h"
#include "../include/zb_aps.h"
#include "../include/zb_mac.h"
#include "../include/zb_address.h"

#define INFINITE_COUNTER 0xFF

/**        
 *  @brief Enum for ZB_API confirm callback functions
 */
enum {
	ZBAPI_ZDO_START_DEV_CNF = 0,
	ZBAPI_NLME_PERMIT_JOIN_CNF,
	ZBAPI_APSDE_DATA_CNF,
	ZBAPI_APSDE_DATA_IND,
	ZBAPI_ZDO_DEV_ANN_IND,
	ZBAPI_ZDO_BIND_RSP,
	ZBAPI_ZDO_UNBIND_RSP,
	ZBAPI_MCPS_OTA_IND,
	ZBAPI_MCPS_DATA_CNF,
	ZBAPI_ACTIVE_EP_RSP,
	ZBAPI_MATCH_DESC_RSP,
	ZBAPI_SIMPLE_DESC_RSP,
	ZBPAI_NLME_LEAVE_CNF,
};


/**        
 *  @brief Macro for NWK addr request type
 */
#define TYPE_NWK_ADDR_REQ            0


/**        
 *  @brief Macro for IEEE addr request type
 */
#define TYPE_IEEE_ADDR_REQ           1

/** @defgroup ZB_API_Types ZB_Types
 *  @brief ZB API structure type definition
 *  @{
 */

/**        
 *  @brief Structure for parameter of startDev callback function
 */
typedef struct zdoStartDevCnf_tag{
    zb_uint8_t status;
    zb_uint8_t logicalChannel;
    zb_uint16_t panId;
    zb_uint16_t shortAddr;
}zdoStartDevCnf_t;


/**        
 *  @brief Structure for parameter of apsdeDataInd callback function
 */
typedef struct apsdeDataInd_tag{
    zb_apsde_data_indication_t indInfo;
    zb_uint8_t asduLen;
    zb_uint8_t asdu[1];
}apsdeDataInd_t;


/**        
 *  @brief Structure for parameter of apsdeDataCnf callback function
 */
typedef struct apsdeDataConf_tag {
    union zb_addr_u destAddress;
    zb_uint8_t destAddrMode;
    zb_uint8_t destEndpoint;
    zb_uint8_t srcEndpoint;
    zb_uint8_t status;
} apsdeDataConf_t;


/**        
 *  @brief Structure for parameter of devAnnInd callback function
 */
typedef struct zdo_devAnnInd_tag {
	u16 nwkAddr;
	u8  extAddr[8];
	u8  nodeCapability;
} zdo_devAnnInd_t;


/**        
 *  @brief Structure for parameter of otaInd callback function
 */
typedef struct mcpsOtaInd_tag{
    zb_mac_mhr_t indInfo;
    zb_uint8_t asduLen;
    zb_uint8_t asdu[1];
}mcpsOtaInd_t;


/**        
 *  @brief Structure for parameter of activeEpRsp callback function
 */
typedef struct zdo_activeEpRsp {
	u8 status;
	u16 nwkAddr;
	u8 epCnt;
	u8 epList[1];
} zdo_activeEpRsp_t;


/**        
 *  @brief Structure for matchDescReq
 */
typedef struct zdo_matchDescReq_tag {
	u16 nwkAddr;
	u16 profileId;
	u8  numInClusters;
	u16 *inClusterList;
	u8  numOutClusters;
	u16 *outClusterList;
} zdo_matchDescReq_t;


/**        
 *  @brief Structure for parameter of matchDescRsp callback function
 */
typedef struct zdo_matchDescRsp_tag {
	u8 status;
	u16 nwkAddr;
	u8 matchLen;
	u8 matchList[1];
} zdo_matchDescRsp_t;


/**        
 *  @brief Structure for address request
 */
typedef struct zdo_addrReq_tag {
	u8 type;
	zb_addr_t requestAddr;
	u8 requestType;
	u8 startIndex;
} zdo_addrReq_t;


/**        
 *  @brief Structure for simple descriptor
 */
typedef struct {
	zb_uint8_t    endpoint;                 /* Endpoint */              
	zb_uint16_t   app_profile_id;           /* Application profile identifier */ 
	zb_uint16_t   app_device_id;            /* Application device identifier */ 
	zb_uint8_t    app_device_version:4;     /* Application device version */ 
	zb_uint8_t    reserved:4;               /* Reserved */          
    zb_uint8_t    in_cluster_num;
    zb_uint8_t    out_cluster_num;
    zb_uint16_t   app_cluster_list[1];
} simple_desc_param_t;


/**        
 *  @brief Structure for parameter of simple_desc_resp callback function
 */
typedef struct zdo_simple_desc_resp_tag
{
  zb_zdo_simple_desc_resp_hdr_t hdr;  /*!< header for response */
  simple_desc_param_t simple_desc; /*!< part of Simple Descriptor */
} zdo_simple_desc_resp_t;


/**        
 *  @brief Structure for parameter of nlmeLeaveConf callback function
 */
typedef struct nlmeLeaveConf_tag
{
  zb_uint8_t status; /*!< MAC status codes */
  zb_ieee_addr_t device_address; /*!< 64 bit IEEE address */
} 
nlmeLeaveConf_t;

typedef void (* zdo_startDevCnfCb_t)(zdoStartDevCnf_t* startDevCnf);
typedef void (* nlme_permitJoinCnfCb_t)(u8 status);
typedef void (* zb_commonCb_t) (void *);
typedef void (* aps_dataIndCb_t)(apsdeDataInd_t* dataInd);
typedef void (* aps_dataCnfCb_t)(apsdeDataConf_t* dataCnf);
typedef void (* zdo_devAnnounceCb_t)(zdo_devAnnInd_t* devAnnInd);
typedef void (* zdo_bindRspCb_t)(u8 status);
typedef void (* zdo_unBindRspCb_t)(u8 status);
typedef void (* mcps_otaIndCb_t)(mcpsOtaInd_t* dataInd);
typedef void (* mcps_otaCnfCb_t)(u8 status);
typedef void (* zdo_activeEpRspCb_t)(zdo_activeEpRsp_t* pRsp);
typedef void (* zdo_matchDescRspCb_t)(zdo_matchDescRsp_t* pRsp);
typedef void (* zdo_simpleDescRspCb_t)(zdo_simple_desc_resp_t* pRsp);
typedef void (* nlme_leaveCnfCb_t)(nlmeLeaveConf_t* pRsp);


/**        
 *  @brief Structure for ZB_API callback function table
 */
typedef struct zb_cbFunc_tag{
    zdo_startDevCnfCb_t zdoStartDevCnfCb;          /* ZigBee Start confirmation callback */
    nlme_permitJoinCnfCb_t nlmePermitJoinCnfCb;    /* ZigBee Permit join confirmation callback */
    aps_dataCnfCb_t apsdeDataCnfCb;                /* ZigBee APS data confirmation callback */
    aps_dataIndCb_t apsdeDataIndCb;                /* ZigBee APS data indication callback */
	zdo_devAnnounceCb_t zb_devAnnCb;               /* ZigBee Device Announce callback */
    zdo_bindRspCb_t zdoBindRspCb;                  /* ZigBee Bind response callback */
    zdo_unBindRspCb_t zdoUnBindRspCb;              /* ZigBee Unbind response callback */
	mcps_otaIndCb_t mcpsOtaIndCb;                  /* OTA indication callback */
	mcps_otaCnfCb_t mcpsDataCnfCb;                 /* OTA confirmation callback */
	zdo_activeEpRspCb_t zdo_activeEpRspCb;         /* Active endpoint response callback */
	zdo_matchDescRspCb_t zdo_matchDescRspCb;       /* Match description response callback */
    zdo_simpleDescRspCb_t zdo_simpleDescRspCb;     /* Simple description response callback */
    nlme_leaveCnfCb_t nlmeLeaveCnfCb;              /* nlme leave comfirm callback */
} zb_cbFuncTbl_t;

/*@} end of group ZB_API_Types definitions */



/** @defgroup ZB_API_Functions Mzsp_Hal_Functions
 *  @brief API functions statement
 *
 *  @{
 */

/***********************************************************************//**
 * @brief       Register the ZB_API callback function table to zigbee stack
 *
 * @param[in]   cbFunc  - Pointer to ZB_API callback function table
 *
 * @return      None
 *
 **************************************************************************/
void zb_regCbFunc(zb_cbFuncTbl_t* cbFunc);


/***********************************************************************//**
 * @brief       Start device
 *
 * @param       None
 *
 * @return      Status
 *
 **************************************************************************/
zb_ret_t zb_zdoStartDevReq(void);


/***********************************************************************//**
 * @brief       Get MAC short address
 *
 * @param       None
 *
 * @return      2 bytes MAC short address
 *
 **************************************************************************/
zb_uint16_t zb_zdoGetShortAddress(void);


/***********************************************************************//**
 * @brief       Set IEEE address
 *
 * @param[in]   extAddr - Pointer to the 8 bytes IEEE address
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoSetExtendedAddress(zb_uint8_t *extAddr);


/***********************************************************************//**
 * @brief       Set MAC short address
 *
 * @param[in]   shortAddr - 2 bytes MAC short address
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoSetShortAddress(zb_uint16_t shortAddr);


/***********************************************************************//**
 * @brief       Send device announce
 *
 * @param       None
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoSendDevAnnance(void);


/***********************************************************************//**
 * @brief       Send bind request to a device
 *
 * @param[in]   bindReq - Pointer to bind/unbind request structure
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoBindRequest(zb_zdo_bind_req_param_t *bindReq);


/***********************************************************************//**
 * @brief       Send unbind request to a device
 *
 * @param[in]   bindReq - Pointer to bind/unbind request structure
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoUnBindRequest(zb_zdo_bind_req_param_t *bindReq);


/***********************************************************************//**
 * @brief       Send active ep request to a device
 *
 * @param[in]   nwkAddr - Short address of the target device
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoActiveEndpointReq(u16 nwkAddr);


/***********************************************************************//**
 * @brief       Send match descriptor request to a device
 *
 * @param[in]   nwkAddr - Short address of the target device
 *
 * @param[in]   pReq    - Pointer to the simple descriptor used
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoMatchDescReq(u16 nwkAddr, zb_af_simple_desc_t* pReq);


/***********************************************************************//**
 * @brief       Send address request to target device for address information
 *
 * @param[in]   nwkAddr - Short address of the target device
 *
 * @param[in]   pReq    - Pointer to the addrReq structure
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoAddrReq(u16 dstNwkAddr, zdo_addrReq_t* pReq);


/***********************************************************************//**
 * @brief       Send end device bind req to a device to perform an end device bind
 *
 * @param[in]   dstAddr        - Short address of the device which this request will be sent to
 *
 * @param[in]   targetAddr     - Short address of the device need to bind
 *
 * @param[in]   profileId      - Profile id
 *
 * @param[in]   srcEp          - Source endpoint
 *
 * @param[in]   srcIeeeAddr    - Source IEEE address
 *
 * @param[in]   numInClusters  - Number of in clusters
 *
 * @param[in]   inClusterList  - Pointer to the in cluster list
 *
 * @param[in]   numOutClusters - Number of out clusters
 *
 * @param[in]   outClusterList - Pointer to the out cluster list
 *
 * @return      None
 *
 **************************************************************************/
void zb_endDeviceBindReq(u16 dstAddr, u16 targetAddr, u16 profileId, u8 srcEp, u8* srcIeeeAddr, u8 numInClusters, u16* inClusterList, u8 numOutClusters, u16* outClusterList);


/***********************************************************************//**
 * @brief       Send simple descriptor request to a device
 *
 * @param[in]   nwkAddr - Short address of the target device
 *
 * @param[in]   ep      - Endpoint
 *
 * @return      None
 *
 **************************************************************************/
void zb_zdoSimpleDescReq(zb_uint16_t nwkAddr, zb_uint8_t ep);


/***********************************************************************//**
 * @brief       Perform an APSME bind
 *
 * @param[in]   bindReq - Pointer to the apsme bind/unbind structure
 *
 * @return      Status
 *
 **************************************************************************/
zb_uint8_t zb_apsmeBindingRequest(zb_apsme_binding_req_t *bindReq);


/***********************************************************************//**
 * @brief       Perform an APSME unbind
 *
 * @param[in]   bindReq - Pointer to the apsme bind/unbind structure
 *
 * @return      Status
 *
 **************************************************************************/
zb_uint8_t zb_apsmeUnBindingRequest(zb_apsme_binding_req_t *bindReq);


/***********************************************************************//**
 * @brief       Send an APSDE data request
 *
 * @param[in]   dataReq - Pointer to the apsde data request structure
 *
 * @param[in]   asdu    - Pointer to the asdu
 *
 * @param[in]   length  - Length of asdu
 *
 * @return      None
 *
 **************************************************************************/
void zb_apsdeDataRequest(zb_apsde_data_req_t *dataReq, zb_uint8_t* asdu, zb_uint8_t length);


/***********************************************************************//**
 * @brief       Send an APSDE data request
 *
 * @param[in]   permit_duration - Time in seconds during which the device allows to join
 *
 * @return      None
 *
 **************************************************************************/
void zb_nlmePermitJoiningRequest(zb_uint8_t permit_duration);


/***********************************************************************//**
 * @brief       Perform a leave to  a device or self
 *
 * @param[in]   req - Pointer to the leave request structure
 *
 * @return      None
 *
 **************************************************************************/
void zb_nlmeLeaveReq(zb_nlme_leave_request_t * req);


/***********************************************************************//**
 * @brief       Send an APSDE data request
 *
 * @param[in]   period_in_sec - Time in seconds between two link status msg
 *
 * @return      None
 *
 **************************************************************************/
void zb_nlmeSetLinkStsPeriod(zb_uint8_t period_in_sec);


/***********************************************************************//**
 * @brief       Send an OTA request
 *
 * @param[in]   dstAddr - Short address of the target device
 *
 * @param[in]   asdu    - Pointer to the asdu
 *
 * @param[in]   length  - Length of asdu
 *
 * @return      None
 *
 **************************************************************************/
void zb_otaRequest(zb_uint16_t dstAddr, zb_uint8_t* asdu, zb_uint8_t length);


/***********************************************************************//**
 * @brief       Send an OTA request
 *
 * @param[in]   endpoint     - Endpoint
 *
 * @param[in]   simple_desc  - Pointer to simple descriptor
 *
 * @param[in]   cb           - Callback function to handle the APS data sent to this endpoint
 *
 * @return      None
 *
 **************************************************************************/
zb_ret_t zb_regEndpointDesc(u8 endpoint, zb_af_simple_desc_t* simple_desc, zb_endpoint_cb_t cb);


/***********************************************************************//**
 * @brief       Internal Use
 *
 * @param       None
 *
 * @return      None
 *
 **************************************************************************/
void zb_setRespCounter(u8 msgId, u8 counter);


/***********************************************************************//**
 * @brief       Internal Use
 *
 * @param       None
 *
 * @return      None
 *
 **************************************************************************/
void zb_callCbFunc(zb_commonCb_t funCb, arg_t resp);


/***********************************************************************//**
 * @brief       Internal Use
 *
 * @param       None
 *
 * @return      None
 *
 **************************************************************************/
zb_commonCb_t zb_findCbFunc(u8 msgId);\

/*@} end of group ZB_API_Functions */

