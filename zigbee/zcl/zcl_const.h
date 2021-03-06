#pragma once


/*********************************************************************
 * CONSTANTS
 */

// General Clusters
#define ZCL_CLUSTER_ID_GEN_BASIC                             0x0000
#define ZCL_CLUSTER_ID_GEN_POWER_CFG                         0x0001
#define ZCL_CLUSTER_ID_GEN_DEVICE_TEMP_CONFIG                0x0002
#define ZCL_CLUSTER_ID_GEN_IDENTIFY                          0x0003
#define ZCL_CLUSTER_ID_GEN_GROUPS                            0x0004
#define ZCL_CLUSTER_ID_GEN_SCENES                            0x0005
#define ZCL_CLUSTER_ID_GEN_ON_OFF                            0x0006
#define ZCL_CLUSTER_ID_GEN_ON_OFF_SWITCH_CONFIG              0x0007
#define ZCL_CLUSTER_ID_GEN_LEVEL_CONTROL                     0x0008
#define ZCL_CLUSTER_ID_GEN_ALARMS                            0x0009
#define ZCL_CLUSTER_ID_GEN_TIME                              0x000A
#define ZCL_CLUSTER_ID_GEN_LOCATION                          0x000B
#define ZCL_CLUSTER_ID_GEN_ANALOG_INPUT_BASIC                0x000C
#define ZCL_CLUSTER_ID_GEN_ANALOG_OUTPUT_BASIC               0x000D
#define ZCL_CLUSTER_ID_GEN_ANALOG_VALUE_BASIC                0x000E
#define ZCL_CLUSTER_ID_GEN_BINARY_INPUT_BASIC                0x000F
#define ZCL_CLUSTER_ID_GEN_BINARY_OUTPUT_BASIC               0x0010
#define ZCL_CLUSTER_ID_GEN_BINARY_VALUE_BASIC                0x0011
#define ZCL_CLUSTER_ID_GEN_MULTISTATE_INPUT_BASIC            0x0012
#define ZCL_CLUSTER_ID_GEN_MULTISTATE_OUTPUT_BASIC           0x0013
#define ZCL_CLUSTER_ID_GEN_MULTISTATE_VALUE_BASIC            0x0014
#define ZCL_CLUSTER_ID_GEN_COMMISSIONING                     0x0015

#define ZCL_CLUSTER_ID_OTA                                   0x0019
#define ZCL_CLUSTER_ID_GREEN_POWER_PROXY                     0x0021

// Closures Clusters
#define ZCL_CLUSTER_ID_CLOSURES_SHADE_CONFIG                 0x0100
#define ZCL_CLUSTER_ID_CLOSURES_DOOR_LOCK                    0x0101
#define ZCL_CLUSTER_ID_CLOSURES_WINDOW_COVERING              0x0102

// HVAC Clusters
#define ZCL_CLUSTER_ID_HVAC_PUMP_CONFIG_CONTROL              0x0200
#define ZCL_CLUSTER_ID_HAVC_THERMOSTAT                       0x0201
#define ZCL_CLUSTER_ID_HAVC_FAN_CONTROL                      0x0202
#define ZCL_CLUSTER_ID_HAVC_DIHUMIDIFICATION_CONTROL         0x0203
#define ZCL_CLUSTER_ID_HAVC_USER_INTERFACE_CONFIG            0x0204

// Lighting Clusters
#define ZCL_CLUSTER_ID_LIGHTING_COLOR_CONTROL                0x0300
#define ZCL_CLUSTER_ID_LIGHTING_BALLAST_CONFIG               0x0301

// Measurement and Sensing Clusters
#define ZCL_CLUSTER_ID_MS_ILLUMINANCE_MEASUREMENT            0x0400
#define ZCL_CLUSTER_ID_MS_ILLUMINANCE_LEVEL_SENSING_CONFIG   0x0401
#define ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT            0x0402
#define ZCL_CLUSTER_ID_MS_PRESSURE_MEASUREMENT               0x0403
#define ZCL_CLUSTER_ID_MS_FLOW_MEASUREMENT                   0x0404
#define ZCL_CLUSTER_ID_MS_RELATIVE_HUMIDITY                  0x0405
#define ZCL_CLUSTER_ID_MS_OCCUPANCY_SENSING                  0x0406

// Security and Safety (SS) Clusters
#define ZCL_CLUSTER_ID_SS_IAS_ZONE                           0x0500
#define ZCL_CLUSTER_ID_SS_IAS_ACE                            0x0501
#define ZCL_CLUSTER_ID_SS_IAS_WD                             0x0502

// Protocol Interfaces
#define ZCL_CLUSTER_ID_PI_GENERIC_TUNNEL                     0x0600
#define ZCL_CLUSTER_ID_PI_BACNET_PROTOCOL_TUNNEL             0x0601
#define ZCL_CLUSTER_ID_PI_ANALOG_INPUT_BACNET_REG            0x0602
#define ZCL_CLUSTER_ID_PI_ANALOG_INPUT_BACNET_EXT            0x0603
#define ZCL_CLUSTER_ID_PI_ANALOG_OUTPUT_BACNET_REG           0x0604
#define ZCL_CLUSTER_ID_PI_ANALOG_OUTPUT_BACNET_EXT           0x0605
#define ZCL_CLUSTER_ID_PI_ANALOG_VALUE_BACNET_REG            0x0606
#define ZCL_CLUSTER_ID_PI_ANALOG_VALUE_BACNET_EXT            0x0607
#define ZCL_CLUSTER_ID_PI_BINARY_INPUT_BACNET_REG            0x0608
#define ZCL_CLUSTER_ID_PI_BINARY_INPUT_BACNET_EXT            0x0609
#define ZCL_CLUSTER_ID_PI_BINARY_OUTPUT_BACNET_REG           0x060A
#define ZCL_CLUSTER_ID_PI_BINARY_OUTPUT_BACNET_EXT           0x060B
#define ZCL_CLUSTER_ID_PI_BINARY_VALUE_BACNET_REG            0x060C
#define ZCL_CLUSTER_ID_PI_BINARY_VALUE_BACNET_EXT            0x060D
#define ZCL_CLUSTER_ID_PI_MULTISTATE_INPUT_BACNET_REG        0x060E
#define ZCL_CLUSTER_ID_PI_MULTISTATE_INPUT_BACNET_EXT        0x060F
#define ZCL_CLUSTER_ID_PI_MULTISTATE_OUTPUT_BACNET_REG       0x0610
#define ZCL_CLUSTER_ID_PI_MULTISTATE_OUTPUT_BACNET_EXT       0x0611
#define ZCL_CLUSTER_ID_PI_MULTISTATE_VALUE_BACNET_REG        0x0612
#define ZCL_CLUSTER_ID_PI_MULTISTATE_VALUE_BACNET_EXT        0x0613
#define ZCL_CLUSTER_ID_PI_11073_PROTOCOL_TUNNEL              0x0614

// Advanced Metering Initiative (SE) Clusters
#define ZCL_CLUSTER_ID_SE_PRICING                            0x0700
#define ZCL_CLUSTER_ID_SE_LOAD_CONTROL                       0x0701
#define ZCL_CLUSTER_ID_SE_SIMPLE_METERING                    0x0702
#define ZCL_CLUSTER_ID_SE_MESSAGE                            0x0703
#define ZCL_CLUSTER_ID_SE_SE_TUNNELING                       0x0704
#define ZCL_CLUSTER_ID_SE_PREPAYMENT                         0x0705
#define ZCL_CLUSTER_ID_GEN_KEY_ESTABLISHMENT                 0x0800

// Light Link cluster
#define ZCL_CLUSTER_ID_LIGHT_LINK                            0x1000


/*** Data Types ***/
#define ZCL_DATATYPE_NO_DATA                            0x00
#define ZCL_DATATYPE_DATA8                              0x08
#define ZCL_DATATYPE_DATA16                             0x09
#define ZCL_DATATYPE_DATA24                             0x0a
#define ZCL_DATATYPE_DATA32                             0x0b
#define ZCL_DATATYPE_DATA40                             0x0c
#define ZCL_DATATYPE_DATA48                             0x0d
#define ZCL_DATATYPE_DATA56                             0x0e
#define ZCL_DATATYPE_DATA64                             0x0f
#define ZCL_DATATYPE_BOOLEAN                            0x10
#define ZCL_DATATYPE_BITMAP8                            0x18
#define ZCL_DATATYPE_BITMAP16                           0x19
#define ZCL_DATATYPE_BITMAP24                           0x1a
#define ZCL_DATATYPE_BITMAP32                           0x1b
#define ZCL_DATATYPE_BITMAP40                           0x1c
#define ZCL_DATATYPE_BITMAP48                           0x1d
#define ZCL_DATATYPE_BITMAP56                           0x1e
#define ZCL_DATATYPE_BITMAP64                           0x1f
#define ZCL_DATATYPE_UINT8                              0x20
#define ZCL_DATATYPE_UINT16                             0x21
#define ZCL_DATATYPE_UINT24                             0x22
#define ZCL_DATATYPE_UINT32                             0x23
#define ZCL_DATATYPE_UINT40                             0x24
#define ZCL_DATATYPE_UINT48                             0x25
#define ZCL_DATATYPE_UINT56                             0x26
#define ZCL_DATATYPE_UINT64                             0x27
#define ZCL_DATATYPE_INT8                               0x28
#define ZCL_DATATYPE_INT16                              0x29
#define ZCL_DATATYPE_INT24                              0x2a
#define ZCL_DATATYPE_INT32                              0x2b
#define ZCL_DATATYPE_INT40                              0x2c
#define ZCL_DATATYPE_INT48                              0x2d
#define ZCL_DATATYPE_INT56                              0x2e
#define ZCL_DATATYPE_INT64                              0x2f
#define ZCL_DATATYPE_ENUM8                              0x30
#define ZCL_DATATYPE_ENUM16                             0x31
#define ZCL_DATATYPE_SEMI_PREC                          0x38
#define ZCL_DATATYPE_SINGLE_PREC                        0x39
#define ZCL_DATATYPE_DOUBLE_PREC                        0x3a
#define ZCL_DATATYPE_OCTET_STR                          0x41
#define ZCL_DATATYPE_CHAR_STR                           0x42
#define ZCL_DATATYPE_LONG_OCTET_STR                     0x43
#define ZCL_DATATYPE_LONG_CHAR_STR                      0x44
#define ZCL_DATATYPE_ARRAY                              0x48
#define ZCL_DATATYPE_STRUCT                             0x4c
#define ZCL_DATATYPE_SET                                0x50
#define ZCL_DATATYPE_BAG                                0x51
#define ZCL_DATATYPE_TOD                                0xe0
#define ZCL_DATATYPE_DATE                               0xe1
#define ZCL_DATATYPE_UTC                                0xe2
#define ZCL_DATATYPE_CLUSTER_ID                         0xe8
#define ZCL_DATATYPE_ATTR_ID                            0xe9
#define ZCL_DATATYPE_BAC_OID                            0xea
#define ZCL_DATATYPE_IEEE_ADDR                          0xf0
#define ZCL_DATATYPE_128_BIT_SEC_KEY                    0xf1
#define ZCL_DATATYPE_UNKNOWN                            0xff


/*** Attribute Access Control - bit masks ***/
#define ACCESS_CONTROL_READ                             0x01
#define ACCESS_CONTROL_WRITE                            0x02
#define ACCESS_CONTROL_COMMAND                          0x04
#define ACCESS_CONTROL_AUTH_READ                        0x10
#define ACCESS_CONTROL_AUTH_WRITE                       0x20



/*** Error Status Codes ***/
#define ZCL_STATUS_SUCCESS                              0x00
#define ZCL_STATUS_FAILURE                              0x01
// 0x02-0x7D are reserved.
#define ZCL_STATUS_NOT_AUTHORIZED                       0x7E
#define ZCL_STATUS_MALFORMED_COMMAND                    0x80
#define ZCL_STATUS_UNSUP_CLUSTER_COMMAND                0x81
#define ZCL_STATUS_UNSUP_GENERAL_COMMAND                0x82
#define ZCL_STATUS_UNSUP_MANU_CLUSTER_COMMAND           0x83
#define ZCL_STATUS_UNSUP_MANU_GENERAL_COMMAND           0x84
#define ZCL_STATUS_INVALID_FIELD                        0x85
#define ZCL_STATUS_UNSUPPORTED_ATTRIBUTE                0x86
#define ZCL_STATUS_INVALID_VALUE                        0x87
#define ZCL_STATUS_READ_ONLY                            0x88
#define ZCL_STATUS_INSUFFICIENT_SPACE                   0x89
#define ZCL_STATUS_DUPLICATE_EXISTS                     0x8a
#define ZCL_STATUS_NOT_FOUND                            0x8b
#define ZCL_STATUS_UNREPORTABLE_ATTRIBUTE               0x8c
#define ZCL_STATUS_INVALID_DATA_TYPE                    0x8d
#define ZCL_STATUS_INVALID_SELECTOR                     0x8e
#define ZCL_STATUS_WRITE_ONLY                           0x8f
#define ZCL_STATUS_INCONSISTENT_STARTUP_STATE           0x90
#define ZCL_STATUS_DEFINED_OUT_OF_BAND                  0x91
#define ZCL_STATUS_INCONSISTENT                         0x92
#define ZCL_STATUS_ACTION_DENIED                        0x93
#define ZCL_STATUS_TIMEOUT                              0x94
#define ZCL_STATUS_ABORT                                0x95
#define ZCL_STATUS_INVALID_IMAGE                        0x96
#define ZCL_STATUS_WAIT_FOR_DATA                        0x97
#define ZCL_STATUS_NO_IMAGE_AVAILABLE                   0x98
#define ZCL_STATUS_REQUIRE_MORE_IMAGE                   0x99

// 0xbd-bf are reserved.
#define ZCL_STATUS_HARDWARE_FAILURE                     0xc0
#define ZCL_STATUS_SOFTWARE_FAILURE                     0xc1
#define ZCL_STATUS_CALIBRATION_ERROR                    0xc2
// 0xc3-0xff are reserved.
#define ZCL_STATUS_CMD_HAS_RSP                          0xFF // Non-standard status (used for Default Rsp)