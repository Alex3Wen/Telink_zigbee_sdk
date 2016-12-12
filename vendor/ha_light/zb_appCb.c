#include "../../proj/tl_common.h"

#if (__PROJECT_HA_LIGHT__)

/**********************************************************************
 * INCLUDES
 */
/* Stack  */
#include "../../zigbee/include/zb_config.h"
#include "../../zigbee/zbapi/zb_api.h"
#include "../../zigbee/zcl/zcl_include.h"
#ifdef ZB_LED_EN
#include "../common/test_led.h"
#endif
/* App */
#include "ha_light.h"


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

/* None */

/**********************************************************************
 * GLOBAL VARIABLES
 */

/**        
 *  @brief Definition for ZigBee callback functions
 */
zb_cbFuncTbl_t haLight_zbFuncCb = {
	haLight_zdoStartDevCnf,             /* ZigBee Start confirmation callback */    
	NULL,                               /* ZigBee Permit join confirmation callback */
	NULL,                               /* ZigBee APS data confirmation callback */
	NULL,                               /* ZigBee APS data indication callback */
	NULL,                               /* ZigBee Device Announce callback */
	NULL,                               /* ZigBee Bind response callback */
	NULL,                               /* ZigBee Unbind response callback */
	
	NULL,                               /* OTA indication callback */
	NULL,                               /* OTA confirmation callback */
	
	NULL,                               /* Active endpoint response callback */
	NULL,                               /* Match description response callback */
	NULL,                               /* Simple description response callback */
	NULL,                               /* Nlme leave comfirm callback */
};


/*********************************************************************
  * @fn      haLight_zdoStartDevCnf
  *
  * @brief   Handler for ZDO Network Start confirm. This function will retry start network if 
  *            current status is FAILURE.
  *
  * @param   pReadRsp - parameter of read attribute response
  *
  * @return  None
  */
void haLight_zdoStartDevCnf(zdoStartDevCnf_t* startDevCnf)
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
        haLight_start();
        
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



#endif  /* __PROJECT_HA_LIGHT__ */



