#pragma once


/*********************************************************************
 * CONSTANTS
 */


/* Attribute ID */
#define ZCL_ATTRID_MAINS_VOLTAGE                        0x0000

/*********************************************************************
 * ENUMS
 */


/*********************************************************************
 * TYPES
 */


/*********************************************************************
 * Public Functions
 */

#ifdef ZCL_POWER
// internal use
rst_t zcl_power_registerCluster(void);
#endif  /* ZCL_POWER */


