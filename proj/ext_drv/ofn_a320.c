
#include "../tl_common.h"

#if(0 && MODULE_OFN_ENABLE)

#include "../drivers/i2c.h"
#include "../drivers/usbkeycode.h"
#include "../../vendor/common/keycode_custom.h"
#include "ofn_a320.h"


#define	A320_RST_ON			gpio_write(GPIO_MIO, 0)
#define	A320_RST_OFF		gpio_write(GPIO_MIO, 1)
#define A320_SHUTDOWN_OFF	gpio_write(GPIO_MV, 0)

u32 ofn_a320_initialized = 0;

u8 ofn_get_motion(s8 x, s8 y){
    u8 ofn_motion = OFN_INVALID;
    static int last_valid = 0;
    static u32 start_time = 0;
    static int xx = 0;
    static int yy = 0;
    if(x == 0 && y == 0){
        //  手势停止状态，判断motion type
        if(last_valid){
            if((abs(xx) + abs(yy)) > OFN_SLIDE_MIN_DISTANCE
                && clock_time_exceed(start_time, OFN_SLIDE_THRESHOLD)){
                //  滑动方向
                if((18 * abs(xx)) >= (10 * abs(yy))){
                    if(xx > 0){
                        ofn_motion = OFN_LEFT;
                    }else{
                        ofn_motion = OFN_RIGHT;
                    }
                }else{
                    if(yy > 0){
                        ofn_motion = OFN_DOWN;
                    }else{
                        ofn_motion = OFN_UP;
                    }
                }
                //  快速滑动,ms
                if(!clock_time_exceed(start_time, OFN_QK_SLIDE_THRESHOLD)){
                    ofn_motion |= OFN_QK_MASK;
                }
            }
    		last_valid = 0;
    		xx = 0;
    		yy = 0;
    	}
    }
    else if(!last_valid){
        xx = x;
        yy = y;
        last_valid = 1;
        start_time = clock_time();
    }else{
        xx += x;
        yy += y;
    }

    return ofn_motion;
}

void ofn_getxy(u8 *xy){
	if(!ofn_a320_initialized){
        xy[0] = xy[1] = 0;
		return;
	}
    // 0x82 motion 0x83 x 0x84 y
    i2c_burst_read(A320_I2C_ID, 0x83, (u8*)xy, 2);
    
    //  ofn不正常工作时，会返回0xFF
    if(xy[0] == 0xFF || xy[1] == 0xFF){
        xy[0] = xy[1] = 0;
    }
}

//  !!!  use timer to save time, which wasted by mere delay
int ofn_do_init(void *data)
{
	static int step = 0;
	if(0 == step){
		++step;
		A320_RST_ON;
		return 48000;
	}else if(1 == step){
		++step;
		A320_RST_OFF;
		return 8000;
	}else if(2 == step){
		++step;
		i2c_write(A320_I2C_ID,0x3a,0x5a);
		return 100;
	}else if(3 == step){
		++step;
		i2c_write(A320_I2C_ID,0x60,0xe4);
		i2c_write(A320_I2C_ID,0x62,0x12);
		i2c_write(A320_I2C_ID,0x63,0x0e);
		i2c_write(A320_I2C_ID,0x64,0x08);
		i2c_write(A320_I2C_ID,0x65,0x06);
		i2c_write(A320_I2C_ID,0x66,0x40);
		i2c_write(A320_I2C_ID,0x67,0x08);
		i2c_write(A320_I2C_ID,0x68,0x48);
		i2c_write(A320_I2C_ID,0x69,0x0a);
		i2c_write(A320_I2C_ID,0x6a,0x50);
		i2c_write(A320_I2C_ID,0x6b,0x48);
		i2c_write(A320_I2C_ID,0x6e,0x34);
		i2c_write(A320_I2C_ID,0x6f,0x3c);
		i2c_write(A320_I2C_ID,0x70,0x18);
		i2c_write(A320_I2C_ID,0x71,0x20);
		i2c_write(A320_I2C_ID,0x75,0x50);
		i2c_write(A320_I2C_ID,0x73,0x99);
		i2c_write(A320_I2C_ID,0x74,0x02);
		i2c_write(A320_I2C_ID,0x77,0x00);
		return 100;
	}
	ofn_a320_initialized = 1;
	return -1;	// delete the timer
	
}

void ofn_init(void)
{
	A320_SHUTDOWN_OFF;

	static ev_time_event_t a320_timer = {ofn_do_init,0,0,0};
	ev_on_timer(&a320_timer, 8000);
}

#endif

