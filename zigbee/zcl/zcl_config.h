#pragma once


#define ZCL_READ
#define ZCL_WRITE
#define ZCL_REPORT


/**        
 *  @brief Definition for MAX Cluster number for one endpoint
 */
#define MAX_ZCL_CLUSTER_NUM     10

/* General */
//#define ZCL_BASIC
#define ZCL_POWER
//#define ZCL_DEV_TEMPERATURE_CFG
#define ZCL_IDENTIFY
#define ZCL_GROUP
//#define ZCL_SCENE
#define ZCL_ON_OFF
//#define ZCL_ON_OFF_SWITCH_CFG
#define ZCL_LEVEL_CTRL
//#define ZCL_ALARMS
//#define ZCL_TIME
//#define ZCL_RSSI_LOCATION


/* Lighting */
//#define ZCL_COLOR_CONTROL
//#define ZCL_BALLAST_CFG


/* Measurement and Sensing */
//#define ZCL_ILLUMINANCE_MEASUREMENT
//#define ZCL_ILLUMINANCE_LEVEL_SENSING
//#define ZCL_OCCUPANCY_SENSING

/* Safe and Security */
#define ZCL_IAS_ZONE




/********************************************* General ********************************************/

/********************* Power Cluster Configuration **********************/
#ifdef ZCL_POWER
    #define ZCL_ATTR_MAINS_VOLTAGE_ENABLE
    //#define ZCL_ATTR_MAINS_FREQUENCY_ENABLE
    #define ZCL_POWER_ATTR_NUM                     1
#endif /* USE_ZCL_ONOFF_ATTR */



/********************* OnOff Cluster Configuration **********************/
#ifdef ZCL_ON_OFF
    #define ZCL_ATTR_ONOFF_ENABLE
    #define ZCL_ONOFF_ATTR_NUM                     1
#endif /* USE_ZCL_ONOFF_ATTR */


/********************* Level Control Cluster Configuration **********************/
#ifdef ZCL_LEVEL_CTRL
    #define ZCL_ATTR_CUR_LEVEL_ENABLE
    #define ZCL_ATTR_REMAINING_TIME_ENABLE
    //#define ZCL_ATTR_ONOFF_TRANS_TIME_ENABLE
    //#define ZCL_ATTR_ON_LEVEL_ENABLE
    #define ZCL_LEVEL_ATTR_NUM                     2
#endif /* ZCL_LEVEL_CTRL */


/********************* Group Cluster Configuration **********************/
#ifdef ZCL_GROUP
    #define ZCL_ATTR_GROUPS_NAME_SUPPORT_ENABLE
    #define ZCL_GROUP_ATTR_NUM                     1

#endif  /* ZCL_GROUP */


/********************* Identify Cluster Configuration **********************/
#ifdef ZCL_IDENTIFY
    #define ZCL_IDENTIFY_ATTR_NUM                  1
#endif  /* ZCL_IDENTIFY */


/********************* Scene Cluster Configuration **********************/
#ifdef ZCL_SCENE
    #define ZCL_SCENE_ATTR_NUM                  1
#endif  /* ZCL_SCENE */


/********************************************* Measurement and Sensing ********************************************/

/********************* Illuminance Measurement **********************/
#ifdef ZCL_ILLUMINANCE_MEASUREMENT
    #define ZCL_ATTR_MEASURED_VALUE_ENABLE
    #define ZCL_ATTR_MIN_MEASURED_VALUE_ENABLE
    #define ZCL_ATTR_MAX_MEASURED_VALUE_ENABLE
    //#define ZCL_ATTR_TOLERANCE_ENABLE
    //#define ZCL_ATTR_LIGHT_SENSOR_TYPE_ENABLE

    #define ZCL_ILLUMINANCE_MEASUREMENT_ATTR_NUM        3

#endif  /* ZCL_ILLUMINANCE_MEASUREMENT */

/********************************************* Safe and Security ********************************************/

/********************* IAS Zone Cluster Configuration **********************/
#ifdef ZCL_IAS_ZONE
    #define ZCL_ATTR_ZONE_STATE_ENABLE
    #define ZCL_ATTR_ZONE_TYPE_ENABLE
    #define ZCL_ATTR_ZONE_STATUS_ENABLE
    #define ZCL_ATTR_IAS_CIE_ADDR_ENABLE

    #define ZCL_IAS_ZONE_ATTR_NUM                  4

#endif  /* ZCL_IAS_ZONE */



