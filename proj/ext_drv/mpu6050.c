#include "../tl_common.h"
#include "../drivers/i2c.h"

#if(!APPLICATION_DONGLE && GYRO_MPU6050_ENBALE)

#include "mouse_sensor.h"
#include "../drivers/mouse.h"
#include "../../proj_lib/airmouse.h"
#include "../os/sys.h"
#include "mpu6050.h"
#include "mouse_sensor.h"
#include "../drivers/somatic_sensor.h"

#define COMPLEMENTARY_ALGORITHM			1

gyro_mouse_data_t gyro_mouse_dat;
s16			cali_ax, cali_ay, cali_az, cali_gx, cali_gy, cali_gz;
static const u8 tbl_sensor_init[] = {
		0x6b, 0x01,		// internal 8M clk oscillator
		0x38, 0x11,		// data rdy irq  en
		0x1b, 0x00,		// gyro full rage: 250 c/ s
		0x1a, 0x02,		// Fs = 1k,  bandwidth = 98hz
		0x19, 9,		// sample rate =  FS / (0x19+1)
		0x1c, 0x10,		// set 8g mode
#if(AIRMOUSE_FIFO_MODE)
		0x23, 0x78,		// enable gsense/gyro fifo
		0x6a, 0x40,		// enable fifo
#endif

};

u32 mouse_sensor_init(void){
	// wait until MPU power ready
	int ok = 0;
	for (int i = 0; i < 500; ++i) {
		if (i2c_read(MPU6050_I2C_ID, 0x75) == 0x68) {
			ok++;
			if (ok++ > 3) {
				break;
			}
		}
		sleep_us (1000);
	}
	int len = sizeof (tbl_sensor_init);
	for (int j=0; j<len; j+=2) {
		i2c_write(MPU6050_I2C_ID, tbl_sensor_init[j], tbl_sensor_init[j+1]);
	}

	//s16 * p_calib = (s16 *) AIRMOUSE_CALIBRATION_ADDR;
#if(MOUSE_CALI_ENABLE)	
    u8 calicData[12];
	if ( ERR_SUCC != ds_userSaveToFlash(AIR_MOUSE_CALI_NV_ITEM, sizeof(s16) * 6, calicData) ) {
        calicData[0] = 0xef;calicData[1] = 0xfe;calicData[2] = 0xff;calicData[3] = 0xff;
        calicData[4] = 0x24;calicData[5] = 0xff;calicData[6] = 0xff;calicData[7] = 0xef;
        calicData[8] = 0xd5;calicData[9] = 0xff;calicData[10] = 0xff;calicData[11] = 0xff;
	}   
#else
    //u8 calicData[] = {0xd1, 0xfe, 0xb1, 0x01, 0xe0, 0xff, 0x85, 0x02, 0x48, 0x00, 0x6f, 0xfe, 0xff, 0xff, 0xff, 0xff};
    //u8 calicData[] = {0x9e, 0x01, 0xe4, 0xfe, 0xf0, 0x00, 0x61, 0x01, 0xce, 0xff, 0xb7, 0xfb, 0xff, 0xff, 0xff, 0xff};
    //u8 calicData[] = {0x97, 0x01, 0x6b, 0x00, 0xe1, 0x00, 0xba, 0x01, 0xdb, 0xfe, 0x01, 0xfc, 0xff, 0xff, 0xff, 0xff};
	//u8 calicData[] = {0x0d, 0xff, 0xcf, 0xff, 0x65, 0x00, 0x8d, 0x00, 0x65, 0xff, 0x28, 0xed};
	u8 calicData[] = {0x7e, 0x01, 0x91, 0xfe, 0xe2, 0x00, 0x2c, 0x01, 0x24, 0xff, 0xc5, 0xeb};   //RC2
	//u8 calicData[] = {0xe8, 0xfe, 0x32, 0x01, 0xdf, 0xff, 0xd2, 0x00, 0xb5, 0xfe, 0x9f, 0xed};   //RC1
	//u8 calicData[] = {0xf0, 0xfe, 0xdd, 0xff, 0xce, 0x00, 0xd7, 0x01, 0x47, 0xfe, 0xac, 0xed};     //RC
	//u8 calicData[] = {0xcc, 0xfe, 0xa6, 0xff, 0x26, 0x00, 0x52, 0x01, 0x36, 0xff, 0xa3, 0xed};
#endif
	
	s16 * p_calib = (s16 *)calicData;
	cali_gx = p_calib[0];
	cali_gy = p_calib[1];
	cali_gz = p_calib[2];

	cali_ax = p_calib[3];
	cali_ay = p_calib[4];
	cali_az = p_calib[5];
	return 1;
	
}

void mouse_sensor_powerup(void){
	i2c_write(MPU6050_I2C_ID,0x6B,0x01);
}
void mouse_sensor_powerdown(void){
	i2c_write(MPU6050_I2C_ID,0x6B,0x41);
}

void mouse_drv_enable_6_axis(int en){}

u8 air_mouse_enable;
u8 air_mouse_last_enable;

u8  mouse_init_flag = 0;
u32 mouse_init_time;
extern u32 mouse_active_time;
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
	mouse_active_time = clock_time();
	air_mouse_last_enable = en;
	
}

u8 gyro_air_button;
void mouse_drv_getbtn(mouse_data_t *mouse_data){
	if(air_mouse_enable){
		mouse_data->btn = gyro_air_button;
	}
}

int mouse_sensor_getdata_no_fifo(s16 *ax, s16 *ay, s16 *az, s16 *gx, s16 *gy, s16 *gz){
	u8 buff[16];
	
	i2c_burst_read (MPU6050_I2C_ID, 0x3b, (u8*)buff, 14);
	
	*ax = (buff[0] << 8) + buff[1];
	*ay = (buff[2] << 8) + buff[3];
	*az = (buff[4] << 8) + buff[5];
	
	*gx = (buff[8] << 8) + buff[9];
	*gy = (buff[10] << 8) + buff[11];
	*gz = (buff[12] << 8) + buff[13];
	return 1;
}

int mouse_sensor_getdata(s16 *ax, s16 *ay, s16 *az, s16 *gx, s16 *gy, s16 *gz){

	u8 buff[16];
	
	i2c_burst_read (MPU6050_I2C_ID, 0x74, (u8*)buff, 12);
	
	*ax = (buff[0] << 8) | buff[1];
	*ay = (buff[2] << 8) | buff[3];
	*az = (buff[4] << 8) | buff[5];
	
	*gx = (buff[6] << 8) | buff[7];
	*gy = (buff[8] << 8) | buff[9];
	*gz = (buff[10] << 8) | buff[11];
	return 1;
}

#if(COMPLEMENTARY_ALGORITHM)
int airmouse_xy(s16 acc_x, s16 acc_y, s16 acc_z, s16 gy_x, s16 gy_y, s16 gy_z, int interval, s8* x, s8* y);
int airmouse_fast_xy(s16 acc_x, s16 acc_y, s16 acc_z, s16 gy_x, s16 gy_y, s16 gy_z, int interval, s8* x, s8* y);
#endif
extern u32 speaker_enable;

u8 gyro_data_ready = 0;

int mouse_sensor_getxy(mouse_data_t *mouse_data, somatic_sensor_data_t *somatic_data){
	if(!air_mouse_enable){
		return 0;
	}
	if(0 == mouse_init_flag && !clock_time_exceed(mouse_init_time, 50*1000)){
		return 0;
	}
	mouse_init_flag = 1;
	
#if(AIRMOUSE_FIFO_MODE)
	u8 buff[2];
	int am_fifo_cnt = 0;
	i2c_burst_read (MPU6050_I2C_ID, 0x72, (u8*)buff, 2);
	am_fifo_cnt = (buff[0] << 8) + buff[1];
	if(am_fifo_cnt <= 0){
		return 0;
	}
	
	static s16 acc_x, acc_y, acc_z, gy_x, gy_y, gy_z;
	while ( am_fifo_cnt != 0 ) {
	    mouse_sensor_getdata(&acc_x, &acc_y, &acc_z, &gy_x, &gy_y, &gy_z);
		i2c_burst_read (MPU6050_I2C_ID, 0x72, (u8*)buff, 2);
	    am_fifo_cnt = (buff[0] << 8) + buff[1];
	}
#else
	gyro_data_ready = 0;
	static s16 acc_x, acc_y, acc_z, gy_x, gy_y, gy_z;	// must static, to keep previous data if no new
	mouse_sensor_getdata_no_fifo(&acc_x, &acc_y, &acc_z, &gy_x, &gy_y, &gy_z);
#endif

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
	AirMouseG (-acc_x, -acc_z, acc_y, &gyro_mouse_dat);
	//	AirMouse(right-to-left,  down-to-up, ....)
	motion = AirMouse(gy_z, -gy_x, gy_y, interval, &gyro_mouse_dat, gyro_air_button);
	if(motion){
		mouse_data->x = gyro_mouse_dat.x;
		mouse_data->y = gyro_mouse_dat.y;
	}
#else	
	// 参数方向为airmouse_xy(left == +x,  front == +y,  down == +z , left,  front,  down,  time, out_x, out_y)
	motion = airmouse_fast_xy(acc_x, acc_y, -acc_z, gy_x, gy_y, -gy_z, interval, &mouse_data->x, &mouse_data->y);
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
static const u8 tbl_sensor_no_fifo_init[] = {
		0x6b, 0x01,		// internal 8M clk oscillator
		0x38, 0x11,		// data rdy irq  en
		0x1b, 0x00,		// gyro full rage: 250 c/ s
		0x1a, 0x02,		// Fs = 1k,  bandwidth = 98hz
		0x19, 0x03,		// sample rate =  FS / (0x19+1)
		0x1c, 0x10,		// set 8g mode
};

u32 mouse_sensor_no_fifo_init(void){
	// wait until MPU power ready
	static int ok = 0;
	for (int i = 0; i < 500; ++i) {
		if (i2c_read(MPU6050_I2C_ID, 0x75) == 0x68) {
			ok++;
			if (ok++ > 3) {
				break;
			}
		}
		sleep_us (1000);
	}
	int len = sizeof (tbl_sensor_no_fifo_init);
	for (int j=0; j<len; j+=2) {
		i2c_write(MPU6050_I2C_ID, tbl_sensor_no_fifo_init[j], tbl_sensor_no_fifo_init[j+1]);
	}
	return 1;
}

#endif	

#if(MOUSE_CALI_ENABLE)
int mouse_cali(s16	*acc_x, s16*acc_y, s16 *acc_z, s16 *gy_x, s16 *gy_y, s16 *gy_z)
{
    return mouse_sensor_getdata_no_fifo(acc_x, acc_y, acc_z, gy_x, gy_y, gy_z);
}

#endif

#endif	

