
#include "../tl_common.h"
#include "../os/sys.h"
#include "mouse.h"
#include "../ext_drv/mouse_sensor.h"
#include "somatic_sensor.h"

#if(MODULE_MOUSE_ENABLE)

#if(__MOUSE_SIMU__)
#include "../simu/mouse_simu.h"
#endif

fn_ptr mouseDataCb;
mouse_data_t mouse_data;

#if(MOUSE_HAS_BUTTON)
static inline void mouse_check_button(mouse_data_t *data){
#if(!__MOUSE_SIMU__)
	data->btn = 0;
    mouse_drv_getbtn(data);
#else 
	data->btn |= mouse_simu_btn;
#endif

}
#endif

#if(MOUSE_HAS_WHEEL)
int mouse_wheel_chk_dir(u32 w0, u32 w1){
	int ret = 0;
	static char state = 0;
	// waring: do not change to if(1 == w1).   w0, w1 are bool types, not necessary 0 or 1
	if( (!w0) && (!w1)){		// 0, 0
		state = 0;
	}else if(w0 && (!w1)){		// 1, 0
		state = 1;
	}else if((!w0) && w1){		// 0, 1
		state = -1;
	}else{						// 1, 1,  confirm
		if(state > 0){
			ret = 1;
		}else if(state < 0){
			ret = -1;
		}
		state = 0;
	}
	return ret;
}

static int wheel_value = 0;
static inline void mouse_wheel_polling(void){		//  check every mili second
#if(!__MOUSE_SIMU__)
    wheel_value = mouse_drv_getwheel();
	// wheel_value += mouse_wheel_chk_dir(MOUSE_WHEEL_STATUS0,MOUSE_WHEEL_STATUS1);
#else
	wheel_value += mouse_simu_wheel_value;
	mouse_simu_wheel_value = 0;
#endif
}

void mouse_get_wheel(mouse_data_t *data){
    //  每次最多处理-127~127单位滚动
    if(wheel_value > U7_MAX){
        data->w = U7_MAX;
        wheel_value -= U7_MAX;
    }else if(wheel_value < -U7_MAX){
        data->w = -U7_MAX;
        wheel_value += U7_MAX;
    }else{
    	data->w = (s8)wheel_value;
    	wheel_value = 0;
    }
}
#endif





extern int mouse_sensor_getxy(mouse_data_t *mouse_data, somatic_sensor_data_t *somatic_data);
static inline int mouse_check_xy(mouse_data_t *data, somatic_sensor_data_t *somatic_data){
#if(!__MOUSE_SIMU__)
    return mouse_sensor_getxy(data, somatic_data);
#else
	data->x = gyro_mouse_dat.x;;
	data->y = gyro_mouse_dat.y;;
    return 1;
#endif
}

u8 gyro_data_ready;
static u32 last_check_time = 0;
extern u32 speaker_enable;
extern u32 mic_enable;
extern u8 gyro_air_button;
u32 mouse_active_time;
s8  mouse_last_btn;

#define MOUSE_PRESS_BTN_DELAY     (300*1000)
int mouse_dither(int has_data, mouse_data_t *data){
    static u8 first_btn = 1;
    static u8 mouse_delay_start = 0;
    //  鼠标按键去抖
	static u32 delay_check_time = 0;
    if(gyro_air_button){
        if(first_btn){
            first_btn = 0;
			mouse_delay_start = 1;
		    delay_check_time = clock_time();
        }
    }else{
        first_btn = 1;
    }
    if(mouse_delay_start){
        if(clock_time_exceed(delay_check_time, MOUSE_PRESS_BTN_DELAY)){
            mouse_delay_start = 0;
        }else{
        	data->x = data->y = 0;	// must.  set zero in case btn pressed
        	has_data = 0;
        }
    }
	return has_data;
}

u8 lastHasData = 0;
void mouse_check_event(void){
	// 现在使用中断来判定鼠标是否移动, 这样更准确
	mouse_data_t *data = &mouse_data;
#if(MODULE_SOMATIC_ENABLE)
	somatic_sensor_data_t *somatic_data = &(mouse_tx_buf.somatic_data);
#else
	somatic_sensor_data_t *somatic_data = 0;
#endif

#if(MOUSE_HAS_BUTTON)
	mouse_check_button(data);
#endif
	//STATIC_ASSERT((!AIRMOUSE_FIFO_MODE)||MOUSE_SCAN_INTERVAL <= 8000);	// in fifo mode, too small interval result in bad performance

#if((MODULE_PM_ENABLE && PM_SUSPEND_ENABLE) || AIRMOUSE_FIFO_MODE)
	int timeout = clock_time_exceed(last_check_time, 9500);
#else
	//int timeout = clock_time_exceed(last_check_time, MOUSE_SCAN_INTERVAL*3);
	int timeout = clock_time_exceed(last_check_time, MOUSE_SCAN_INTERVAL);
#endif


	if(data->btn != mouse_last_btn || timeout || !lastHasData
#if(!((MODULE_PM_ENABLE && PM_SUSPEND_ENABLE) || AIRMOUSE_FIFO_MODE))
//		|| gyro_data_ready		// 在用 suspend 模式的情况下，不能判断 data_ready, 否则 report 上升，但效果不好
#endif		
	){
		last_check_time = clock_time();

		int has_data = mouse_check_xy(data, somatic_data);
		if(0 == data->x && 0 == data->y){
			has_data = 0;
		}
		has_data = mouse_dither(has_data, data);
		if(data->btn != mouse_last_btn || has_data || (timeout && data->btn)){
		    lastHasData = 1;
			mouse_active_time = clock_time();
			mouse_last_btn = data->btn;
#if(MOUSE_HAS_WHEEL)
			mouse_wheel_polling();						//	check every milisecond
			mouse_get_wheel();
#endif		
			// handle immediately or we have to find somewhere to clear mouse_event
			if (mouseDataCb) {
                mouseDataCb(data);
			}
			//ev_emit_event_syn(EV_MOUSE_EVENT, data);
		}
		else {
		    lastHasData = 0;
		}
	}
}

void mouse_registerCb(fn_ptr cb) 
{
    mouseDataCb = cb;
}

void mouse_init(void){
#if(__MOUSE_SIMU__)
    mouse_simu_init();
#endif
	mouse_drv_init();
	mouse_sensor_enable(0);
	mouse_drv_enable_6_axis(1);
	// Enable interrupt.
//#if(!AIRMOUSE_FIFO_MODE)
//	gpio_set_interrupt(GPIO_GYRO, 0);
//#endif
	ev_on_poll(EV_POLL_MOUSE_EVENT, mouse_check_event);
}

#endif

