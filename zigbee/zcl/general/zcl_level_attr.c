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
#ifdef ZCL_LEVEL_CTRL

#ifdef ZCL_ATTR_CUR_LEVEL_ENABLE
    u8 zcl_attr_curLevel = 0;
#endif
#ifdef ZCL_ATTR_REMAINING_TIME_ENABLE
    u16 zcl_attr_remainTime = 0;
#endif
#ifdef ZCL_ATTR_ONOFF_TRANS_TIME_ENABLE
    u16 zcl_attr_onOffTransTime = 0;
#endif
#ifdef ZCL_ATTR_ON_LEVEL_ENABLE
    u8 zcl_attr_onLevel = 0xFE;
#endif

/* Attribute record list */
zclAttrInfo_t level_attrTbl[ZCL_LEVEL_ATTR_NUM] = 
{
#ifdef ZCL_ATTR_CUR_LEVEL_ENABLE
	{ ZCL_ATTRID_LEVEL_CURRENT_LEVEL,  ZCL_DATATYPE_UINT8,   ACCESS_CONTROL_READ,  (u8*)&zcl_attr_curLevel },
#endif

#ifdef ZCL_ATTR_REMAINING_TIME_ENABLE
	{ ZCL_ATTRID_LEVEL_REMAINING_TIME, ZCL_DATATYPE_UINT16,   ACCESS_CONTROL_READ,  (u8*)&zcl_attr_remainTime },
#endif

#ifdef ZCL_ATTR_ONOFF_TRANS_TIME_ENABLE
	{ ZCL_ATTRID_LEVEL_ON_OFF_TRANSITION_TIME,  ZCL_DATATYPE_UINT16,   ACCESS_CONTROL_READ|ACCESS_CONTROL_WRITE,  (u8*)&zcl_attr_onOffTransTime },
#endif

#ifdef ZCL_ATTR_ON_LEVEL_ENABLE
	{ ZCL_ATTRID_LEVEL_ON_LEVEL,       ZCL_DATATYPE_UINT8,   ACCESS_CONTROL_READ|ACCESS_CONTROL_WRITE,  (u8*)&zcl_attr_onLevel },
#endif
};


#endif    /* ZCL_LEVEL_CTRL */

