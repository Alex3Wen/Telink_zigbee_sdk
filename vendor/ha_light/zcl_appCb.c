#include "../../proj/tl_common.h"

#if (__PROJECT_HA_LIGHT__)

/**********************************************************************
 * INCLUDES
 */
#include "../../zigbee/include/zb_config.h"
#include "../../zigbee/zbapi/zb_api.h"
#include "../../zigbee/zcl/zcl_include.h"

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
 * LOCAL VARIABLES
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
void haLight_zclMove2levelCmdHandler(moveToLvl_t* cmd);
void haLight_zclIdentifyCmdHandler(u16 identifyTime);


/**********************************************************************
 * GLOBAL VARIABLES
 */


zcl_foundation_AppCallbacks_t haLight_zclFoundationCb = 
{
    haLight_zclReadAttrRspHandler,
    haLight_zclWriteAttrRspHandler,
    haLight_zclDfltRspHandler,
};


#ifdef ZCL_ON_OFF
zcl_onOff_AppCallbacks_t haLight_onOffCb = {haLight_zclOnoffCmdHandler};
#endif  /* ZCL_ON_OFF */
#ifdef ZCL_LEVEL_CTRL
zcl_level_AppCallbacks_t haLight_levelCb = {haLight_zclMove2levelCmdHandler, NULL, NULL, NULL};
#endif  /* ZCL_LEVEL_CTRL */
#ifdef ZCL_GROUP
zcl_group_AppCallbacks_t haLight_groupCb = {NULL};
#endif  /* ZCL_GROUP */
#ifdef ZCL_IDENTIFY
zcl_identify_AppCallbacks_t haLight_identifyCb = {haLight_zclIdentifyCmdHandler};
#endif  /* ZCL_IDENTIFY */





/*********************************************************************
  * @fn      haLight_zclReadAttrRspHandler
  *
  * @brief   Handler for ZCL Read Attribute repsonse command.
  *
  * @param   pReadRsp - parameter of read attribute response
  *
  * @return  None
  */
 void haLight_zclReadAttrRspHandler(zclReadRspCmd_t* pReadRsp)
 {
 #ifdef WIN32
     printf("\n zcl read response number: 0x%02x \n", pReadRsp->numAttr);
 #endif
     bufm_free((u8*)pReadRsp);
 }

/*********************************************************************
 * @fn      haLight_zclWriteAttrRspHandler
 *
 * @brief   Handler for ZCL Write Attribute repsonse command.
 *
 * @param   pWriteRsp - parameter of write attribute response
 *
 * @return  None
 */
 void haLight_zclWriteAttrRspHandler (zclWriteRspCmd_t *pWriteRsp)
 {
 #ifdef WIN32
     printf("\n zcl write response number: 0x%02x \n", pWriteRsp->numAttr);
 #endif
     bufm_free((u8*)pWriteRsp);
 }

/*********************************************************************
 * @fn      haLight_zclDfltRspHandler
 *
 * @brief   Handler for ZCL Defalut repsonse command.
 *
 * @param   pDfltRsp - parameter of default response
 *
 * @return  None
 */
 void haLight_zclDfltRspHandler(zclDefaultRspCmd_t* pDfltRsp)
 {
 #ifdef WIN32
     printf("\n zcl default response status: 0x%02x \n", pDfltRsp->statusCode);
 #endif
     bufm_free((u8*)pDfltRsp);
 }
 

 
#ifdef ZCL_ON_OFF
/*********************************************************************
 * @fn      haLight_zclOnoffCmdHandler
 *
 * @brief   Handler for ZCL ONOFF command. This function will set ONOFF attribute first
 *            and set to related hardware accordingly.
 *
 * @param   cmd - ON/OFF/TOGGLE
 *
 * @return  None
 */
void haLight_zclOnoffCmdHandler(u8 cmd)
{
    /* Update ZCL Attribute */
    if (cmd == ZCL_CMD_ONOFF_ON) {
     zcl_attr_onoff = ZCL_ONOFF_STATUS_ON;
    } else if (cmd == ZCL_CMD_ONOFF_OFF) {
     zcl_attr_onoff = ZCL_ONOFF_STATUS_OFF;
    } else if (cmd == ZCL_CMD_ONOFF_TOGGLE) {
     zcl_attr_onoff = (zcl_attr_onoff == ZCL_ONOFF_STATUS_OFF) ?
         ZCL_ONOFF_STATUS_ON : ZCL_ONOFF_STATUS_OFF;
    }

    /* Perform physical operation */
#ifdef WIN32
    printf("\ncurrent onoff status: %d\n", zcl_attr_onoff);
#elif (ZB_LED_EN)
    gpio_write(TEST_ONOFF_LED, zcl_attr_onoff);
#else 
    /* Using PWM LED */
    if (ZCL_ONOFF_STATUS_ON == zcl_attr_onoff) {
        hw_lightOn(ONOFF_DIRECTLY);
    } else {
        hw_lightOff(ONOFF_DIRECTLY, zcl_attr_curLevel);
    }
#endif
}
#endif  /* ZCL_ON_OFF */


#ifdef ZCL_LEVEL_CTRL

/*********************************************************************
 * @fn      haLight_zclMove2levelCmdHandler
 *
 * @brief   Handler for ZCL Move to Level command. This function will set ONOFF attribute first
 *            and set to related hardware accordingly.
 *
 * @param   cmd - move to level command
 *
 * @return  None
 */
void haLight_zclMove2levelCmdHandler(moveToLvl_t* cmd)
{
    u8 curLvl = zcl_attr_curLevel;
    u8 targetLvl = cmd->level;
    
    if (hw_isBusy()) {
		return;
	}
    
    /* Update ZCL Attribute */
    if (cmd->withOnOff) {
        if (cmd->level == 0) {
            zcl_attr_onoff = ZCL_ONOFF_STATUS_OFF;
        } else {
            zcl_attr_onoff = ZCL_ONOFF_STATUS_ON;
        }
    }

    zcl_attr_curLevel = targetLvl;
    

    /* Perform physical operation */
#ifdef WIN32
    printf("\ncurrent brightness : %d\n", zcl_attr_curLevel);
#elif (ZB_LED_EN)
    gpio_write(TEST_ONOFF_LED, zcl_attr_onoff);
#else 
    /* Using PWM LED */
    hw_lightMoveToLevel(curLvl, targetLvl, cmd->transitionTime);
#endif
}
#endif  /* ZCL_LEVEL_CTRL */



#ifdef ZCL_IDENTIFY

int haLight_identifyTimerCb(void* arg)
{
#ifdef ZB_LED_EN
    gpio_write(TEST_ONOFF_LED, 0);
#else
    hw_lightOff(ONOFF_DIRECTLY, 0xff);
#endif

    return -1;
}


/*********************************************************************
 * @fn      haLight_zclIdentifyCmdHandler
 *
 * @brief   Handler for ZCL Identify command. This function will set blink LED.
 *
 * @param   cmd - move to level command
 *
 * @return  None
 */
static ev_time_event_t identifyTimer;
void haLight_zclIdentifyCmdHandler(u16 identifyTime)
{
    zcl_attr_identifyTime = identifyTime;
    

    /* Perform physical operation */
#ifdef WIN32
    printf("\nthis light be select\n");
#elif (ZB_LED_EN)
    gpio_write(TEST_ONOFF_LED, 1);
    identifyTimer.cb = haLight_identifyTimerCb;
    ev_on_timer(&identifyTimer, identifyTime*1000*100);
#else 
    hw_lightOn(ONOFF_DIRECTLY);
    identifyTimer.cb = haLight_identifyTimerCb;
    ev_on_timer(&identifyTimer, identifyTime*1000*100);
#endif
}

#endif  /* ZCL_IDENTIFY */




#endif  /* __PROJECT_HA_LIGHT__ */


