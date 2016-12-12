#pragma once


/*********************************************************************
 * CONSTANTS
 */

#define HA_PROFILE_ID                      0x0104




/*********************************************************************
 * ENUMS
 */

typedef enum {
	HA_ROLE_COORD,
	HA_ROLE_ROUTER,
	HA_ROLE_END_DEVICE
} ha_role_t;

enum ha_device_id {
	HA_DEV_ONOFF_SWITCH                     = 0x0000,
	HA_DEV_LEVEL_CTRL_SWITCH                = 0x0001,
	HA_DEV_ONOFF_OUTPUT                     = 0x0002,
	HA_DEV_LEVEL_CTRLABLE_OUTPUT            = 0x0003,
	HA_DEV_SCENE_SELECTOR                   = 0x0004,
	HA_DEV_CONFIG_TOOL                      = 0x0005,
	HA_DEV_REMOTE_CTRL                      = 0x0006,
	HA_DEV_COMBINED_INTERFACE               = 0x0007,
	HA_DEV_RANGE_EXTENDER                   = 0x0008,
	HA_DEV_MAINS_PWR_OUTLET                 = 0x0009,
	HA_DEV_DOOR_LOCK                        = 0x000A,
	HA_DEV_DOOR_LOCK_CTRLER                 = 0x000B,
	HA_DEV_SIMPLE_SENSOR                    = 0x000C,
	HA_DEV_HOME_GATEWAY                     = 0x0050,
	HA_DEV_SMART_PLUG                       = 0x0051,
	HA_DEV_WHITE_GOOD                       = 0x0052,
	HA_DEV_METER_INTERFACE                  = 0x0053,

	HA_DEV_ONOFF_LIGHT                      = 0x0100,
	HA_DEV_DIMMABLE_LIGHT                   = 0x0101,
	HA_DEV_COLOR_DIMMABLE_LIGHT             = 0x0102,
	HA_DEV_ONOFF_LIGHT_SWITCH               = 0x0103,
	HA_DEV_DIMMER_SWITCH                    = 0x0104,
	HA_DEV_COLOR_DIMMER_SWITCH              = 0x0105,
	HA_DEV_LIGHT_SENSOR                     = 0x0106,
	HA_DEV_OCC_SENSOR                       = 0x0107,

	HA_DEV_SHADE                            = 0x0200,
	HA_DEV_SHADE_CTRLER                     = 0x0201,
	HA_DEV_WINDOW_COVERING_DEVICE           = 0x0202,
	HA_DEV_WINDOW_COVERING_CTRLER           = 0x0203,

	HA_DEV_HEATING_COOLING_UNIT             = 0x0300,
	HA_DEV_THERMOSTAT                       = 0x0301,
	HA_DEV_TEMPERATURE_SENSOR               = 0x0302,
	HA_DEV_PUMP                             = 0x0303,
	HA_DEV_PUMP_CTRLER                      = 0x0304,
	HA_DEV_PRESSURE_SENSOR                  = 0x0305,
	HA_DEV_FLOW_SENSOR                      = 0x0306,

	HA_DEV_IAS_CIE                          = 0x0400,
	HA_DEV_IAS_ACE                          = 0x0401,
	HA_DEV_IAS_ZONE                         = 0x0402,
	HA_DEV_IAS_WD                           = 0x0403,
};

/*********************************************************************
 * TYPES
 */



/*********************************************************************
 * Public Functions
 */


void ha_reset(void);
void ha_init(zb_af_simple_desc_t *simple_desc);