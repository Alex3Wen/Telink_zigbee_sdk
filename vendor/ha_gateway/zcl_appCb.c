#include "../../proj/tl_common.h"

#if (__PROJECT_HA_GATEWAY__)

/**********************************************************************
 * INCLUDES
 */
#include "../../zigbee/include/zb_config.h"
#include "../../zigbee/zbapi/zb_api.h"
#include "../../zigbee/zcl/zcl_include.h"

#include "ha_gateway.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */



/**********************************************************************
 * TYPEDEFS
 */



/**********************************************************************
 * LOCAL VARIABLES
 */




/**********************************************************************
 * GLOBAL VARIABLES
 */


zcl_foundation_AppCallbacks_t haGateway_zclFoundationCb = 
{
    haGateway_zclReadAttrRspHandler,
    haGateway_zclWriteAttrRspHandler,
    haGateway_zclDfltRspHandler,
};


#ifdef ZCL_ON_OFF
zcl_onOff_AppCallbacks_t haGateway_onOffCb = {NULL};
#endif  /* ZCL_ON_OFF */
#ifdef ZCL_LEVEL_CTRL
zcl_level_AppCallbacks_t haGateway_levelCb = {NULL, NULL, NULL, NULL};
#endif  /* ZCL_LEVEL_CTRL */
#ifdef ZCL_GROUP
zcl_group_AppCallbacks_t haGateway_groupCb = {NULL};
#endif  /* ZCL_GROUP */



/*********************************************************************
  * @fn      haGateway_zclReadAttrRspHandler
  *
  * @brief   Handler for ZCL Read Attribute repsonse command.
  *
  * @param   pReadRsp - parameter of read attribute response
  *
  * @return  None
  */
 void haGateway_zclReadAttrRspHandler(zclReadRspCmd_t* pReadRsp)
 {
 #ifdef WIN32
     printf("\n zcl read response number: 0x%02x \n", pReadRsp->numAttr);
 #endif
     bufm_free((u8*)pReadRsp);
 }

/*********************************************************************
 * @fn      haGateway_zclWriteAttrRspHandler
 *
 * @brief   Handler for ZCL Write Attribute repsonse command.
 *
 * @param   pWriteRsp - parameter of write attribute response
 *
 * @return  None
 */
 void haGateway_zclWriteAttrRspHandler (zclWriteRspCmd_t *pWriteRsp)
 {
 #ifdef WIN32
     printf("\n zcl write response number: 0x%02x \n", pWriteRsp->numAttr);
 #endif
     bufm_free((u8*)pWriteRsp);
 }

/*********************************************************************
 * @fn      haGateway_zclDfltRspHandler
 *
 * @brief   Handler for ZCL Defalut repsonse command.
 *
 * @param   pDfltRsp - parameter of default response
 *
 * @return  None
 */
 void haGateway_zclDfltRspHandler(zclDefaultRspCmd_t* pDfltRsp)
 {
 #ifdef WIN32
     printf("\n zcl default response status: 0x%02x \n", pDfltRsp->statusCode);
 #endif
     bufm_free((u8*)pDfltRsp);
 }
 

#endif  /* __PROJECT_HA_GATEWAY__ */


