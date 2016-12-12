
#include "../tl_common.h"
#include "mma865x.h"
#include "../drivers/i2c.h"

#if((!APPLICATION_DONGLE) && GSENSOR_MMA865X_ENABLE)

#define G_SENSOR_MOTION_WAKEUP		0
int  gensor_init(void)
{
	// MMA865X_REGISTER_TRAN_SRC
	int wakeup_by_me = i2c_read(I2C_ID_MMA865X, MMA865X_REGISTER_TRAN_SRC) & (1 << 6);

	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG1, 0x58);  // standby
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_data_cfg, 0x02);   // 8g mode
#if G_SENSOR_MOTION_WAKEUP	
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_FF_MT_CFG, 0x78);  // motion: x y
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_FF_MT_THR, 0x0c);  // 1.25g 
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_FF_MT_DEB, 0x03);  // 
#else

	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_TRAN_CFG, 0x0e);   // tran: x y z
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_TRAN_THR, 0x06);   // 1.25g 
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_TRAN_DEB, 0x03);   // 
#endif
	
	//i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG2, 0x1c);   // sleep low power; 
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG2, 0x18);   // sleep disable
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG3, 0x2a);   // irq active high, motion wakeup
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG4, 0x25);   // irq on data ready
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG5, 0x25);   // irq on data ready, motion & tran
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG1, 0x59);   // active

	return wakeup_by_me;
	
}
 
void  gsensor_powerup(int up)	// up or sleep
{
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG1, 0x58);   // standby
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG2, up?0x18:0x1b); // low power mode for sleep`
#if G_SENSOR_MOTION_WAKEUP	
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG4, up?0x01:0x04); //motion
#else
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG4, up?0x01:0x20); // transcient
#endif
	i2c_write(I2C_ID_MMA865X, MMA865X_REGISTER_CTRL_REG1, up?0x59:0x69); //active
}

u8	gsensor_active;
void gsensor_set_active(int active){
	if(active){
		u8 id = i2c_read(I2C_ID_MMA865X, 0x0d);
		gsensor_active = (id == 0x4a);
	}else{
		gsensor_active = 0;
	}
}

int gsensor_get_xyz(s16 *x, s16 *y, s16 *z){
	u8 buff[8];
    u32 drdy = gpio_read(GPIO_GSENSOR);
    if(gsensor_active && drdy){
        i2c_burst_read(I2C_ID_MMA865X, 0x0, buff + 1, 7);
        
		*x = (buff[2] << 8) + buff[3];
		*y = (buff[4] << 8) + buff[5];
		*z = (buff[6] << 8) + buff[7];
        return 1;
    }
    return 0;
}

#endif

