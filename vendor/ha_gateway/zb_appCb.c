#include "../../proj/tl_common.h"

#if (__PROJECT_HA_GATEWAY__)

/**********************************************************************
 * INCLUDES
 */
/* Stack  */
#include "../../zigbee/include/zb_config.h"
#include "../../zigbee/zbapi/zb_api.h"
#include "../../zigbee/zcl/zcl_include.h"
#include "../../zigbee/ha/ha.h"
#include "../common/test_led.h"
/* App */
#include "ha_gateway.h"
#include "gwCmd.h"


/**********************************************************************
 * LOCAL CONSTANTS
 */

/* None */

/**********************************************************************
 * TYPEDEFS
 */

/* None */

/**********************************************************************
 * LOCAL VARIABLES
 */

ev_time_event_t haGateway_serviceDiscoveryTimer;

/**********************************************************************
 * LOCAL FUNCTIONS
 */

void haGateway_matchDescRspHandler(zdo_matchDescRsp_t *pRsp);
void haGateway_leaveCnfHandler(nlmeLeaveConf_t* pCnf);
void haGateway_simpleDescRspHandler(zdo_simple_desc_resp_t *pRsp);

/**********************************************************************
 * GLOBAL VARIABLES
 */

/**        
 *  @brief Definition for ZigBee callback functions
 */
zb_cbFuncTbl_t haGateway_zbFuncCb = 
{
    haGateway_zdoStartDevCnf,           /* ZigBee Start confirmation callback */
    NULL,                               /* ZigBee Permit join confirmation callback */
    NULL,                               /* ZigBee APS data confirmation callback */
    NULL,                               /* ZigBee APS data indication callback */
    haGateway_devAnnHandler,            /* ZigBee Device Announce callback */
    NULL,                               /* ZigBee Bind response callback */
    NULL,                               /* ZigBee Unbind response callback */
    NULL,                               /* OTA indication callback */
    NULL,                               /* OTA confirmation callback */
    NULL,                               /* Active endpoint response callback */
    haGateway_matchDescRspHandler,      /* Match descriptor response callback */
    haGateway_simpleDescRspHandler,     /* Simple descriptor response callback */
    haGateway_leaveCnfHandler,          /* leave confirm callback */
};



/*********************************************************************
  * @fn      haGateway_zdoStartDevCnf
  *
  * @brief   Handler for ZDO Network Start confirm. This function will retry start network if 
  *            current status is FAILURE.
  *
  * @param   zdoStartDevCnf_t - parameter of start device confirmation
  *
  * @return  None
  */
void haGateway_zdoStartDevCnf(zdoStartDevCnf_t* startDevCnf)
{

#ifdef ZB_LED_EN
    /* LED to indicate the start confirm received */
    gpio_write(COMMISSIONING_LED, 0);
#endif

    if (startDevCnf->status != SUCCESS) {
#ifdef WIN32
        printf("ha network start failure, error code = 0x%2x\n", startDevCnf->status);
#endif
        /* Try to Start the ZigBee network again */
        haGateway_start();
        
    } else {
#ifdef WIN32
        printf("ha network start success");
#endif
#ifdef ZB_LED_EN
       gpio_set_func(NWK_START_LED, AS_GPIO);
       gpio_set_output_en(NWK_START_LED, 1);
       gpio_write(NWK_START_LED, 1);
#endif
    }

    /* Always remember to free the buffer */
    bufm_free((u8*)startDevCnf);

}


/*********************************************************************
  * @fn      haGateway_serviceDiscovery
  *
  * @brief   This function is a timer callback to discover the service in the new joined device
  *           through ZDP Simple Descriptor request primitive.
  *
  * @param   pInd - parameter of device announce indication
  *
  * @return  -1 means the timer only be called once.
  */
int haGateway_serviceDiscovery(void* arg)
{
	u16 nwkAddr = (u16)arg;

	/* In this sample, we use the HA_APP_ENDPOINT because 
	we actually know the endpoint of the newly joined device.
	If you are not aware of it, please use Active Endpoint Request
	first to explore the destination endpoint.*/
	zb_zdoSimpleDescReq(nwkAddr, HA_APP_ENDPOINT);

	/* Eliminate the Timer */
	return -1;
}


void haGateway_simpleDescRspHandler(zdo_simple_desc_resp_t *pRsp)
{
	cmd_dev_info_t devInfo;

	if (pRsp->hdr.status != SUCCESS) {
		bufm_free((u8*)pRsp);
        return;
	}

	if (RET_OK != zb_address_ieee_by_short(pRsp->hdr.nwk_addr, devInfo.extAddr)) {
        bufm_free((u8*)pRsp);
		return;
	}

	devInfo.nwkAddr = pRsp->hdr.nwk_addr;
	devInfo.endpoint = HA_APP_ENDPOINT;
	devInfo.devId = pRsp->simple_desc.app_device_id;

	if ( (devInfo.devId < HA_DEV_ONOFF_LIGHT) || (devInfo.devId > HA_DEV_COLOR_DIMMABLE_LIGHT)) {
        bufm_free((u8*)pRsp);
		return;
	}

	/* Notify host there is new light joining */
	gateway_sendCtrlCmd(ZLL_CTRL_CMD_DEV_ANN_IND,
	    (u8*)&devInfo,
	    sizeof(cmd_dev_info_t),
	    devInfo.nwkAddr);

    bufm_free((u8*)pRsp);
	
}


/*********************************************************************
  * @fn      haGateway_devAnnHandler
  *
  * @brief   Handler for ZDO Device Announce message. When this function be called means 
  *          there is new node join PAN or a node rejoin the PAN.
  *
  * @param   pInd - parameter of device announce indication
  *
  * @return  None
  */
void haGateway_devAnnHandler(zdo_devAnnInd_t* pInd)
{

#ifdef WIN32
	printf("\nnew device join, network addr is : 0x%x\n", pInd->nwkAddr);
#endif

    haGateway_serviceDiscoveryTimer.cb = haGateway_serviceDiscovery;
    haGateway_serviceDiscoveryTimer.data = (void*)pInd->nwkAddr;
    ev_on_timer(&haGateway_serviceDiscoveryTimer, 1000*1000*1);

    bufm_free((u8*)pInd);
}


/*********************************************************************
  * @fn      haGateway_leaveCnfHandler
  *
  * @brief   Handler for ZDO Leave Confirm message.
  *
  * @param   pRsp - parameter of leave confirm
  *
  * @return  None
  */
void haGateway_leaveCnfHandler(nlmeLeaveConf_t* pCnf)
{
    gateway_sendCtrlCmd(ZLL_CTRL_CMD_LEAVE_CNF, (u8*)&(pCnf->status), sizeof(u8), 0);
    bufm_free((u8*)pCnf);
}

/*********************************************************************
  * @fn      haGateway_matchDescRspHandler
  *
  * @brief   Handler for ZDO Leave Confirm message.
  *
  * @param   pRsp - parameter of leave confirm
  *
  * @return  None
  */
void haGateway_matchDescRspHandler(zdo_matchDescRsp_t *pRsp)
{
	printf("\nFound matched clusters! nwk addr: 0x%4x, endpoint: 0x%x\n", pRsp->nwkAddr, pRsp->matchList[0]);
	bufm_free((u8*)pRsp);
}






#endif  /* __PROJECT_HA_GATEWAY__ */



