#include "../../../proj/tl_common.h"

/**********************************************************************
 * INCLUDES
 */
#include "../zcl_include.h"


/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * LOCAL TYPES
 */


/**********************************************************************
 * LOCAL VARIABLES
 */
#ifdef ZCL_ON_OFF

/* Default as OFF */
u8 zcl_attr_onoff = ZCL_ONOFF_STATUS_OFF;

/* Attribute record list */
zclAttrInfo_t onoff_attrTbl[ZCL_ONOFF_ATTR_NUM] = 
{
#ifdef ZCL_ATTR_ONOFF_ENABLE
	{ ZCL_ATTRID_ONOFF,  ZCL_DATATYPE_BOOLEAN,   ACCESS_CONTROL_READ,  (u8*)&zcl_attr_onoff},
#endif
};

#endif    /* ZCL_ON_OFF */

