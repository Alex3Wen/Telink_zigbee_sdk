#include "../../proj/tl_common.h"

#if (__PROJECT_HA_LIGHT__)

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
#include "light_hwControl.h"
#include "ha_light.h"


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
extern zb_cbFuncTbl_t haLight_zbFuncCb;


/* ZCL Callback functions */
extern zcl_foundation_AppCallbacks_t haLight_zclFoundationCb;
    
#ifdef ZCL_ON_OFF
    extern zcl_onOff_AppCallbacks_t haLight_onOffCb;
#endif  /* ZCL_ON_OFF */
#ifdef ZCL_LEVEL_CTRL
    extern zcl_level_AppCallbacks_t haLight_levelCb;
#endif  /* ZCL_LEVEL_CTRL */
#ifdef ZCL_GROUP
    extern zcl_group_AppCallbacks_t haLight_groupCb;
#endif  /* ZCL_GROUP */
#ifdef ZCL_IDENTIFY
    extern zcl_identify_AppCallbacks_t haLight_identifyCb;
#endif  /* ZCL_IDENTIFY */



/**********************************************************************
 * LOCAL VARIABLES
 */

/**        
 *  @brief Software timer used in app level
 */
static ev_time_event_t haLight_timer;


/**        
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define HALIGHT_IN_CLUSTER_NUM               5
#define HALIGHT_OUT_CLUSTER_NUM              1

/**        
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
u16 haLight_inClusterList[HALIGHT_IN_CLUSTER_NUM] = 
{
    ZCL_CLUSTER_ID_GEN_POWER_CFG,
	ZCL_CLUSTER_ID_GEN_ON_OFF, 
	ZCL_CLUSTER_ID_GEN_LEVEL_CONTROL,
	ZCL_CLUSTER_ID_GEN_GROUPS,
	ZCL_CLUSTER_ID_GEN_IDENTIFY,
};

/**        
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
u16 haLight_outClusterList[HALIGHT_OUT_CLUSTER_NUM] = 
{
	ZCL_CLUSTER_ID_GEN_ON_OFF,
};


/**        
 *  @brief Definition for simple description for HA profile
 */
zb_af_simple_desc_t haLight_simpleDesc = 
{
	HA_APP_ENDPOINT,                    /* Endpoint */  
	HA_PROFILE_ID,                      /* Application profile identifier */
	HA_DEV_DIMMABLE_LIGHT,              /* Application device identifier */ 
	0,                                  /* Application device version */ 
	0,                                  /* Reserved */   
	HALIGHT_IN_CLUSTER_NUM,             /* Application input cluster count */
	haLight_inClusterList,              /* Application input cluster list */
	0,                                  /* Application output cluster count */
	NULL,                               /* Application output cluster list */
};





/*************************timer callbacks************************************/

int haApp_start_timerCb(void *arg)
{
	/* Start ZigBee device according it's role */
	if (zb_zdoStartDevReq() != RET_OK)
	{
		TRACE_MSG(TRACE_ERROR, "zdo_dev_start failed", (FMT__0));
	}
    
#ifdef ZB_LED_EN
    gpio_write(COMMISSIONING_LED, 1);
#endif

	return -1;
}


/*************************utility functions************************************/


/*********************************************************************
 * @fn      haApp_nwk_jitter
 *
 * @brief   This functions return the jitter value of network start.
 *
 * @param   None
 *
 * @return  None
 */
u32 nwk_jitter(void)
{
	u32 jitter = (zb_random()&(u32)0x7FFF) + 1;
	//jitter = jitter << 9;
	jitter = jitter << 7;
	return jitter;
}

/*********************************************************************
 * @fn      haLight_start
 *
 * @brief   Start the network by jitter timer, which could reduce conflict when more than one
 *             one node start at same time.
 *
 * @param   None
 *
 * @return  None
 */
void haLight_start(void)
{
     /* Start network in Jitter timer*/
    haLight_timer.cb = haApp_start_timerCb;
    ev_on_timer(&haLight_timer, nwk_jitter());
}



/*************************Ha_app initial functions************************************/



/*********************************************************************
 * @fn      haLight_init
 *
 * @brief   Initialize Lighting Application related control variables and hardware setting
 *
 * @param   None
 *
 * @return  None
 */
void haLight_init(void)
{
    /* Init Hw lighting driver, if PIB_RESTORE is enabled, 
    it should restore the value in Flash first. */
    hw_lightInit();
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
	zb_regCbFunc(&haLight_zbFuncCb);

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
	zcl_init(&haLight_zclFoundationCb);

	/* Initialize HA profile */
	ha_init(&haLight_simpleDesc);

    /* Register used server cluster */
    zcl_onOff_register(ZCL_ONOFF_ATTR_NUM, onoff_attrTbl, &haLight_onOffCb);
    zcl_level_register(ZCL_LEVEL_ATTR_NUM, level_attrTbl, &haLight_levelCb);
    zcl_identify_register(ZCL_IDENTIFY_ATTR_NUM, identify_attrTbl, &haLight_identifyCb);
    zcl_group_register(ZCL_GROUP_ATTR_NUM, group_attrTbl, &haLight_groupCb);

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
	haLight_init();

    /* Start Network */
    haLight_start();
}

#endif  /* __PROJECT_HA_LIGHT__ */

