#pragma once


/*********************************************************************
 * CONSTANTS
 */


/* Attribute ID */
#define ZCL_ATTRID_MEASURED_VALUE                         0x0000
#define ZCL_ATTRID_MIN_MEASURED_VALUE                     0x0001
#define ZCL_ATTRID_MAX_MEASURED_VALUE                     0x0002
#define ZCL_ATTRID_TOLERANCE                              0x0003
#define ZCL_ATTRID_LIGHT_SENSOR_TYPE                      0x0004



/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */



/*********************************************************************
 * Public Functions
 */



#ifdef ZCL_ILLUMINANCE_MEASUREMENT
// internal use
rst_t zcl_illuminanceMeasure_registerCluster(void);
#endif  /* ZCL_ILLUMINANCE_MEASUREMENT */