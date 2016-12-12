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
#ifdef ZCL_IDENTIFY

u16 zcl_attr_identifyTime = 0;

/* Attribute record list */
zclAttrInfo_t identify_attrTbl[ZCL_IDENTIFY_ATTR_NUM] = 
{
	{ ZCL_ATTRID_IDENTIFY_TIME,  ZCL_DATATYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE,  (u8*)&zcl_attr_identifyTime },
};


#endif    /* ZCL_IDENTIFY */

