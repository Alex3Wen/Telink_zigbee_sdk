
#pragma once

#include "../config/user_config.h"
#include "../common/types.h"
#include "../common/bit.h"
#include "../common/utility.h"

typedef struct {
	s8 g_sensor_x_l;
	s8 g_sensor_x_h;
	s8 g_sensor_y_l;
	s8 g_sensor_y_h;
	s8 g_sensor_z_l;
	s8 g_sensor_z_h;
	s8 gyro_x_l;
	s8 gyro_x_h;
	s8 gyro_y_l;
	s8 gyro_y_h;
	s8 gyro_z_l;
	s8 gyro_z_h;
	s8 compass_x_l;
	s8 compass_x_h;
	s8 compass_y_l;
	s8 compass_y_h;
	s8 compass_z_l;
	s8 compass_z_h;
	u8 temperature_l;
	u8 temperature_h;
	u8 kb_flag;
	u8 resv[3];
}somatic_sensor_data_t;

void somatic_sensor_init(void);

