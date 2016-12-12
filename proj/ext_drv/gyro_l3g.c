#include "../tl_common.h"
#include "../drivers/i2c.h"

#if ((!APPLICATION_DONGLE) && GYRO_L3G_ENBALE && GSENSOR_MMA865X_ENABLE)

#include "mouse_sensor.h"
#include "../drivers/mouse.h"
#include "../../proj_lib/airmouse.h"
#include "../os/sys.h"
#include "mouse_drv.h"
#include "gyro_l3g.h"
#include "mouse_sensor.h"
#include "../drivers/somatic_sensor.h"

#define COMPLEMENTARY_ALGORITHM			1

extern int gsensor_get_xyz(s16 *x, s16 *y, s16 *z);
extern void gsensor_set_active(int active);
extern int  gensor_init(void);

gyro_mouse_data_t gyro_mouse_dat;
s16	cali_ax, cali_ay, cali_az, cali_gx, cali_gy, cali_gz;

void gyro_init(void){
	// wait until MPU power ready
	int ok = 0;
	for (int i = 0; i < 500; ++i) {
		if (i2c_read(I2C_ID_GYRO_L3G, 0x0f) == 0xd3) {	// l3g4200D
			ok++;
			if (ok++ > 3) {
				break;
			}
		}
		sleep_us (1000);
	}
	i2c_write(I2C_ID_GYRO_L3G, 0x20, 0x0f);		// 100 reprot rate
	i2c_write(I2C_ID_GYRO_L3G, 0x22, 0x08); 	// data ready interrupt
	
	s16 * p_calib = (s16 *) AIRMOUSE_CALIBRATION_ADDR;
	cali_gx = p_calib[0];
	cali_gy = p_calib[1];
	cali_gz = p_calib[2];

	cali_ax = p_calib[3];
	cali_ay = p_calib[4];
	cali_az = p_calib[5];
}

void mouse_sensor_powerup(void){
	gsensor_powerup(1);
}
void mouse_sensor_powerdown(void){
	gsensor_powerup(0);
}

void mouse_drv_enable_6_axis(int en){
    if(en){
		gsensor_set_active(1);
        gyro_mouse_dat.gx = gyro_mouse_dat.gy = 0;
    }else{
		gsensor_set_active(0);
	    gyro_mouse_dat.gx = 0;
	    gyro_mouse_dat.gy = 256;
    }
}
u32 mouse_sensor_init(void){						//鼠标传感器初始化
	gensor_init();
	gyro_init();
	mouse_sensor_powerup();
	mouse_drv_enable_6_axis(1);
	return 0;
}

//  airmouse生效开关
u8 air_mouse_enable;
u8 air_mouse_last_enable;

u8  mouse_init_flag = 0;
u32 mouse_init_time;
#if(COMPLEMENTARY_ALGORITHM)
void airmouse_start_xy(void);
#endif
void mouse_sensor_enable(int en){
	air_mouse_enable = en;
	if(air_mouse_enable && (!air_mouse_last_enable)){
		mouse_init_flag = 0;
		mouse_init_time = clock_time();
#if(COMPLEMENTARY_ALGORITHM)
		airmouse_start_xy();
#endif	
	}
	air_mouse_last_enable = en;
	
}

u8 gyro_air_button;
void mouse_drv_getbtn(mouse_data_t *mouse_data){
	mouse_data->btn = gyro_air_button;
}
int mouse_sensor_getdata_no_fifo(s16 *ax, s16 *ay, s16 *az, s16 *gx, s16 *gy, s16 *gz){
	return mouse_sensor_getdata(ax, ay, az, gx, gy, gz);
}
int mouse_sensor_getdata(s16 *ax, s16 *ay, s16 *az, s16 *gx, s16 *gy, s16 *gz){

	gsensor_get_xyz(ax, ay, az);

	u16 buff[3];
	i2c_burst_read(I2C_ID_GYRO_L3G, 0x28 | 0x80, (u8*)(&buff), 6);
	*gx = buff[0];
	*gy = buff[1];
	*gz = buff[2];
	return 1;
}

extern u8 gyro_data_ready;
#if(COMPLEMENTARY_ALGORITHM)
int airmouse_xy(s16 acc_x, s16 acc_y, s16 acc_z, s16 gy_x, s16 gy_y, s16 gy_z, int interval, s8* x, s8* y);
#endif	
int mouse_sensor_getxy(mouse_data_t *mouse_data, somatic_sensor_data_t *somatic_data){
	if(!air_mouse_enable){
		return 0;
	}
	if(0 == mouse_init_flag && !clock_time_exceed(mouse_init_time, 50*1000)){
		return 0;
	}
	mouse_init_flag = 1;

	int ret = 0;
	gyro_data_ready = 0;
	static s16 acc_x, acc_y, acc_z, gy_x, gy_y, gy_z;	// must static, to keep previous data if no new
	mouse_sensor_getdata(&acc_x, &acc_y, &acc_z, &gy_x, &gy_y, &gy_z);

	acc_x -= cali_ax;
	acc_y -= cali_ay;
	if(cali_az > 0){
		acc_z = acc_z - cali_az + 0x1000;
	}else{
		acc_z = acc_z - cali_az - 0x1000;
	}
	gy_x -= cali_gx;
	gy_y -= cali_gy;
	gy_z -= cali_gz;
	
	static u32 last_time;

	mouse_data->x = mouse_data->y = 0;
	// 由于浮点算法运算量过大, 所以在 speaker 打开的时候，就用普通算法
	// speaker 不打开的时候，用浮点算法
	int motion;
	
#if(MODULE_PM_ENABLE && PM_SUSPEND_ENABLE)
	int interval = MOUSE_SCAN_INTERVAL; 	//please note that overflows are ok, since for example 0x0001 - 0x00FE will be equal to 2
#else
	u32 now = clock_time();
	int interval = (now - last_time) / CLOCK_SYS_CLOCK_1US; 	//please note that overflows are ok, since for example 0x0001 - 0x00FE will be equal to 2
	last_time = now;					//save for next loop, please note interval will be invalid in first sample but we don't use it
#endif
	
#if(!COMPLEMENTARY_ALGORITHM)
	//	AirMouse(right,  down,	front,	,....)
	AirMouseG (acc_x, acc_z, acc_y, &gyro_mouse_dat);
	//	AirMouse(right-to-left,  down-to-up, ....)
	motion = AirMouse(-gy_z, -gy_x, gy_y, interval, &gyro_mouse_dat, gyro_air_button);
	if(motion){
		mouse_data->x = gyro_mouse_dat.x;
		mouse_data->y = gyro_mouse_dat.y;
	}
#else	
	// 参数方向为airmouse_xy(left == +x,  front == +y,  down == +z , left,  front,  down,  time, out_x, out_y)
	motion = airmouse_xy(acc_x, acc_y, -acc_z, -gy_x,  -gy_y, -gy_z, interval, &mouse_data->x, &mouse_data->y);
#endif

#if(MODULE_SOMATIC_ENABLE)
	somatic_data->gsensor_x = acc_x;
	somatic_data->gsensor_y = acc_y;
	somatic_data->gsensor_z = acc_z;
	somatic_data->gyro_x = gy_x;
	somatic_data->gyro_y = gy_y;
	somatic_data->gyro_z = gy_z;
#endif
	return motion;
}

#if (__PROJECT_CALIB__)
u32 mouse_sensor_no_fifo_init(void){
	mouse_sensor_init();
	return 1;
}

#endif	

#endif

