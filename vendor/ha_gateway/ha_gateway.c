#include "../../proj/tl_common.h"

#if (__PROJECT_HA_GATEWAY__)

/**********************************************************************
 * INCLUDES
 */
#include "../../proj/drivers/ds.h"
#include "../../rf/rf.h"
#include "../../zigbee/include/zb_config.h"
#include "../../zigbee/zbapi/zb_api.h"
#include "../../zigbee/zcl/zcl_include.h"
#include "../../zigbee/ha/ha.h"
#ifdef ZB_LED_EN
#include "../common/test_led.h"
#endif
#include "ha_gateway.h"
#include "gwCmd.h"


/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */

/* ZigBee Callback functions */
extern zb_cbFuncTbl_t haGateway_zbFuncCb;


/* ZCL Callback functions */
extern zcl_foundation_AppCallbacks_t haGateway_zclFoundationCb;

#ifdef ZCL_ON_OFF
    extern zcl_onOff_AppCallbacks_t haGateway_onOffCb;
#endif  /* ZCL_ON_OFF */
#ifdef ZCL_LEVEL_CTRL
    extern zcl_level_AppCallbacks_t haGateway_levelCb;
#endif  /* ZCL_LEVEL_CTRL */
#ifdef ZCL_GROUP
    extern zcl_group_AppCallbacks_t haGateway_groupCb;
#endif  /* ZCL_GROUP */



/**********************************************************************
 * LOCAL VARIABLES
 */

/**        
 *  @brief Software timer used in app level
 */
static ev_time_event_t haGateway_timer;


/**        
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define HAGATEWAY_IN_CLUSTER_NUM               1
#define HAGATEWAY_OUT_CLUSTER_NUM              3

/**        
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
u16 haGateway_inClusterList[HAGATEWAY_IN_CLUSTER_NUM] = 
{
    ZCL_CLUSTER_ID_GEN_POWER_CFG,
};

/**        
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
u16 haGateway_outClusterList[HAGATEWAY_OUT_CLUSTER_NUM] = 
{
	ZCL_CLUSTER_ID_GEN_ON_OFF,
    ZCL_CLUSTER_ID_GEN_LEVEL_CONTROL,
    ZCL_CLUSTER_ID_GEN_GROUPS,
};


/**        
 *  @brief Definition for simple description for HA profile
 */
zb_af_simple_desc_t haGateway_simpleDesc = 
{
	HA_APP_ENDPOINT,                    /* Endpoint */  
	HA_PROFILE_ID,                      /* Application profile identifier */
	HA_DEV_HOME_GATEWAY,                /* Application device identifier */ 
	0,                                  /* Application device version */ 
	0,                                  /* Reserved */   
	HAGATEWAY_IN_CLUSTER_NUM,           /* Application input cluster count */
	haGateway_inClusterList,            /* Application input cluster list */
	HAGATEWAY_OUT_CLUSTER_NUM,          /* Application output cluster count */
	haGateway_outClusterList,           /* Application output cluster list */
};





/*************************timer callbacks************************************/




/*************************utility functions************************************/



/*********************************************************************
 * @fn      haGateway_start
 *
 * @brief   Start the network by jitter timer, which could reduce conflict when more than one
 *             one node start at same time.
 *
 * @param   None
 *
 * @return  None
 */
void haGateway_start(void)
{
     /* Start network in Jitter timer*/
    if (zb_zdoStartDevReq() != RET_OK) {
		printf("zdo_dev_start failed\n");
	}
    
#ifdef ZB_LED_EN
    gpio_write(COMMISSIONING_LED, 1);
#endif
}

/*********************************************************************
 * @fn      haGateway_usbCmdHandler
 *
 * @brief   Handler when usb-uart command received.
 *
 * @param   None
 *
 * @return  None
 */
void haGateway_usbCmdHandler(u8* pData)
{
	u8 *pNewBuf;

	if (!pData) {
		return;
	}

    if (*pData != 0xFE) {
        /* the command is not for me */
        bufm_free((u8*)pData);
        return;
    }

	/* Process the USB-UART command */
    gateway_cmdHandler(pData);

	/* Free the buffer */
	bufm_free((u8*)pData);
}




/*************************Ha_app initial functions************************************/

void haGateway_usbInit(void)
{
#if USB_CDC_ENABLE
    /* Init USB-UART Transceiver */
    TH_trxInit(haGateway_usbCmdHandler);
#endif
}


/*********************************************************************
 * @fn      haGateway_init
 *
 * @brief   Initialize Gateway Application related control variables and hardware setting
 *
 * @param   None
 *
 * @return  None
 */
void haGateway_init(void)
{
    /* Init USB-UART transceiver to Host */
    haGateway_usbInit();
    
#ifdef ZB_LED_EN
    zb_led_init();
#endif

    /* Apply Global Settings */
    rf_paEnable = MODULE_RF_PA_ENABLE;
}


/*********************************************************************
 * @fn      stack_init
 *
 * @brief   This function initialize the ZigBee stack and related profile. If HA/ZLL profile is 
 *          enabled in this application, related cluster should be registered here.
 *
 * @param   None
 *
 * @return  None
 */
void stack_init(void)
{
	/* Register ZB stack callback handler */
	zb_regCbFunc(&haGateway_zbFuncCb);

    /* Initialize ZBOSS stack */
	zb_init();
    
    /* Device Role Setting */
#if (APP_COORDINATOR)
    ZB_AIB().aps_designated_coordinator = 1;
    MAC_PIB().mac_pan_id = 0x1931;
#else
    ZB_AIB().aps_designated_coordinator = 0;
#endif
    ZB_AIB().aps_channel_mask = (1<<APP_CHANNEL);


    /* Initialize ZCL layer */
	zcl_init(&haGateway_zclFoundationCb);

	/* Initialize HA profile */
	ha_init(&haGateway_simpleDesc);

}


/*********************************************************************
 * @fn      user_init
 *
 * @brief   User level initialization code.
 *
 * @param   None
 *
 * @return  None
 */
void user_init(void)
{
	/* Initialize Stack */
	stack_init();

    /* Initialize Application */
	haGateway_init();

    /* Start Network */
    haGateway_start();
}

#endif  /* __PROJECT_HA_GATEWAY__ */

