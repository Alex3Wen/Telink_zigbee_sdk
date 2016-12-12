
#include "../tl_common.h"

#if(MODULE_OFN_ENABLE)

#include "../drivers/i2c.h"
#include "../drivers/usbkeycode.h"
#include "../../vendor/common/keycode_custom.h"
#include "ofn_vd5377.h"

u8 ofn_get_motion(s8 x, s8 y){
    u8 ofn_motion = OFN_INVALID;
    static int last_valid = 0;
    static u32 start_time = 0;
    static int xx = 0;
    static int yy = 0; 

    if(x == 0 && y == 0){ 
        //  手势停止状态，判断motion type
        //  hisense ofn实际安装角度大约逆时针偏离45度
        if(last_valid){ 
            if((abs(xx) + abs(yy)) > OFN_SLIDE_MIN_DISTANCE
                && clock_time_exceed(start_time, OFN_QK_SLIDE_THRESHOLD)){
                if((xx <= 0 && yy >= 0 && (1000 * abs(xx)) <= (268 * abs(yy)))
                    || (xx >= 0 && yy >= 0)
                    || (xx >= 0 && yy <= 0 && (268 * abs(xx)) >= (1000 * abs(yy)))){
                    ofn_motion = OFN_LEFT;
                }else if((xx <= 0 && yy >= 0 && (268 * abs(xx)) >= (1000 * abs(yy)))
                    || (xx <= 0 && yy <= 0)
                    || (xx >= 0 && yy <= 0 && (1000 * xx) <= (268 * yy))){
                    ofn_motion = OFN_RIGHT;
                }else if(xx >= 0 && yy <= 0){ 
                    ofn_motion = OFN_UP;
                }else{
                    ofn_motion = OFN_DOWN;
                }
                //  快速滑动,ms 
                if(!clock_time_exceed(start_time, OFN_SLIDE_THRESHOLD)){
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
int ofn_ready(void){
	return gpio_read(GPIO_OFN_MOTION);
}

void ofn_getxy(u8 *xy){
	gpio_write(GPIO_MV, 0);
    // 0x21 x 0x22 y
    i2c_burst_read(vd5377_I2C_ID, 0x21, (u8*)xy, 2);

	gpio_write(GPIO_MV, 1);
    
    //  ofn不正常工作时，会返回0xFF
    if(xy[0] == 0xFF || xy[1] == 0xFF){
        xy[0] = xy[1] = 0;
    }
}

#define 	OFN5377_ID		0xa6

void ofn_power_down(void){
	gpio_write(GPIO_OFN_POWER, 0);
}

void ofn_init(void)
{
    i2c_write(OFN5377_ID,0x16, 0x1e);
    sleep_us(2000);
#if 1
    i2c_write(OFN5377_ID,0x29, 0x20);
    i2c_write(OFN5377_ID,0x2a, 0x08);
    i2c_write(OFN5377_ID,0x2b, 0x08);
    i2c_write(OFN5377_ID,0x51, 0x02);
    i2c_write(OFN5377_ID,0x28, 0x74);
    i2c_write(OFN5377_ID,0x25, 0x10);
#endif
    i2c_write(OFN5377_ID,0x05, 0xbd);
}

#endif

