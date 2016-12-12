
#include "../../proj/tl_common.h"
#include "../../proj/drivers/mouse.h"
#include "../../proj/drivers/keyboard.h"
#include "keycode_custom.h"
#include "../../proj/ext_drv/mouse_drv.h"
#include "led_cfg.h"
#include "../../proj/drivers/led.h"
#include "../../proj/telink_rf/frame.h"

#if (__PROJECT_RC__)

#define KB_LONGPRESS_THRESHOLD (1000*1000)  // in us

int            st_mouse_active = 0;
int            st_escape = 0;
int            real_key_cnt = 0;
static kb_longpress_ctrl_t kb_longpress_ctrl[] = {
    {VK_F5,          VK_A,  0,  0,  KB_LONGPRESS_THRESHOLD},
    {VK_B,          VK_L,  0,  0,  KB_LONGPRESS_THRESHOLD},
    {VK_PAGE_UP,    VK_P,  0,  0,  KB_LONGPRESS_THRESHOLD},
    {VK_PAGE_DOWN,    VK_E,  0,  0,  KB_LONGPRESS_THRESHOLD},
};

u8 gyro_air_button;
u8 air_mouse_enable;
void mouse_drv_getbtn(mouse_data_t *mouse_data){
    mouse_data->btn = gyro_air_button;
}
extern u32 mic_enable;
extern u32 mic_active_time;
extern u32 speaker_enable;
extern u32 speaker_active_time;

extern void mouse_drv_enable_6_axis(int en);
extern void mouse_sensor_enable(int en);

int mouse_drv_enabled = 0;
int am_calibrating;
void device_key_handle(void* data){
    int kb_cnt = 0;
    gyro_air_button = 0;

    kb_data_t * kb_data = (kb_data_t *)(data);
    
    if(kb_data->cnt == 2 && kb_data->keycode[0] == VK_PAGE_UP && kb_data->keycode[1] == VK_PAGE_DOWN){
        kb_data->cnt = 0;
        ev_emit_event_syn(EV_CALI_START, 0);
        return;
    }

    if(kb_data->cnt && !am_calibrating){
        if(rf_mac.conn_sta == RF_CONN_STATE_CONNECTED){
            led_set_pattern(LED_IND, LED_IND_PAT_OPER);
        }else{
            if(kb_data->cnt == 2 && kb_data->keycode[0] == VK_PAGE_UP && kb_data->keycode[1] == VK_DOWN){
                ev_emit_event_syn(EV_PAIRING_START, 0);
            }else{
                led_set_pattern(LED_IND, LED_IND_PAT_NOT_CONN);
            }
            if(rf_mac.conn_sta == RF_CONN_STATE_SEARCHING){
                kb_data->cnt = 0;
            }
            return;
        }
    }

    foreach(i, ARRAY_SIZE(kb_longpress_ctrl)){
        int need_mv = 0;
        int key_idx = 0;
        int ret = kb_check_longpress(kb_longpress_ctrl, i, &key_idx);
        if(ret == KB_IS_LONGPRESS){
            if(!kb_longpress_ctrl[i].processed){
                kb_longpress_ctrl[i].processed = 1;
                //  达到长按键条件且未处理过，处理一次
                if(kb_longpress_ctrl[i].val_org == VK_L){    //laser on
                    kb_data->cnt = 0;    // ?
                    need_mv = 1;
                }
                else {
                    kb_data->keycode[key_idx] = kb_longpress_ctrl[i].val_chg;
                }
            }else{
                need_mv = 1;
            }
        }else if(ret == KB_KEY_RELEASE){
            //  长按键release
            if(!kb_longpress_ctrl[i].processed){
                // Laser Off
                if(kb_longpress_ctrl[i].val_org == VK_L){
                    kb_data->cnt = 0;
                }
                if(kb_data->cnt < KB_RETURN_KEY_MAX){
                    kb_data->keycode[kb_data->cnt++] = kb_longpress_ctrl[i].val_org;
                    ++real_key_cnt;
                }
            }
            kb_longpress_ctrl[i].processed = 0;
        }else{
          //  没有长按键动作
            if(kb_longpress_ctrl[i].this_pressed){
                need_mv = 1;
            }
        }

        if(need_mv){
            --kb_data->cnt;
            --real_key_cnt;
            for(int j = key_idx; j < kb_data->cnt; ++j){
                kb_data->keycode[j] = kb_data->keycode[j+1];
            }
        }
    }

    foreach(i, kb_data->cnt){
        if(kb_data->keycode[i]==VK_MOUSE_LEFT){
            gyro_air_button |= MOUSE_LEFT_BTN_DOWN_MASK;
            kb_data->keycode[i] = 0;
        }else if(kb_data->keycode[i]==VK_MOUSE_RIGHT){
            gyro_air_button |= MOUSE_RIGHT_BTN_DOWN_MASK;
            kb_data->keycode[i] = 0;
        }else if(kb_data->keycode[i]==VK_A){
            st_mouse_active = !st_mouse_active;
            if (st_mouse_active) {
                mouse_sensor_enable(1);
                mouse_drv_enable_6_axis(1);
                mouse_drv_enabled = 1;
                kb_data->keycode[i] = VK_A;
                //led_set_pattern(LED_MIC, LED_MIC_PAT_VOICE);
            }
            else {
                //led_set_pattern(LED_MIC, LED_MIC_PAT_QUIET);
                kb_data->keycode[i] = VK_H;
                mouse_sensor_enable(0);
                mouse_drv_enabled = 0;
            }
            kb_data->ctrl_key |= VK_MSK_LCTRL;
            ++kb_cnt;
        } else if(kb_data->keycode[i]==VK_F5){
            st_escape = !st_escape;
            if (st_escape) {
                kb_data->keycode[i] = VK_ESC;
            }
            else {
                kb_data->keycode[i] = VK_F5;
            }
            ++kb_cnt;
        } else if(kb_data->keycode[i]==VK_P){
            kb_data->keycode[i] = kb_data->keycode[i];
            kb_data->ctrl_key |= VK_MSK_LCTRL;
            ++kb_cnt;
        } else if(kb_data->keycode[i]==VK_S){
            mouse_sensor_enable(1);
            mouse_drv_enable_6_axis(0);
            mouse_drv_enabled = 1;
            //led_set_pattern(LED_MIC, LED_MIC_PAT_VOICE);
            gyro_air_button |= MOUSE_LEFT_BTN_DOWN_MASK;
            kb_data->keycode[i] = 0;
        }else{
            kb_data->keycode[kb_cnt]=kb_data->keycode[i];
            ++kb_cnt;
        }
    }
    
    kb_data->cnt = kb_cnt;
}

void device_enable_mic(int en){
    if(en){
        if(!mic_enable){    // last not enable
            led_set_pattern(LED_MIC, LED_MIC_PAT_VOICE);
        }
    }else{
        if(mic_enable){    // last enable
            led_set_pattern(LED_MIC, LED_MIC_PAT_QUIET);
        }
    }
    extern void device_app_enable_mic(int en);
    device_app_enable_mic(en);
}
void device_enable_speaker(int en){
    device_app_enable_speaker(en);
}

// must,  为了防止在放音乐的时候，拔掉dongle 导致device 不能sleep
void device_aud_check_timer(void){
#if(MODULE_MIC_ENABLE)    
    if(mic_enable && clock_time_exceed(mic_active_time, AUD_AUTO_CLOSE_TIMEOUT)){
        device_enable_mic(0);
    }
#endif    
#if(MODULE_SPEAKER_ENABLE)    
    if(speaker_enable && clock_time_exceed(speaker_active_time, AUD_AUTO_CLOSE_TIMEOUT)){
        device_enable_speaker(0);
    }
#endif    
}

//  1 second timer for hander user operation
int device_oper_timer(void *data){
    device_aud_check_timer();
    return 0;
} 

#if(MOUSE_CALI_ENABLE)
void device_cali_start_handle(void *data){
    extern int mouse_cali_start(void);
    if(-1 == mouse_cali_start()){
        // flash full
        led_set_pattern(LED_MIC, LED_MIC_PAT_AM_CALI_ERR);
        return;
    }else{
        led_set_pattern(LED_IND, LED_IND_PAT_AM_CALI);
        led_set_pattern(LED_MIC, LED_MIC_PAT_AM_CALI);
    }
    am_calibrating = 1;
    
    return;
}

void device_cali_stop_handle(void *data){
    led_set_pattern(LED_IND, LED_IND_PAT_AM_CALI);
    led_set_pattern(LED_MIC, LED_MIC_PAT_AM_CALI);
    am_calibrating = 0;
    
    return;
}
#endif

void gpio_user_irq_handler(void){
    extern u8 gyro_data_ready;
    if(gpio_read(GPIO_GYRO)){
        gyro_data_ready = 1;
    }
}

void user_init(){
    extern void mouse_drv_init(void);
    mouse_drv_init();
    mouse_sensor_enable(0);
    mouse_drv_enable_6_axis(1);
    static ev_event_t ev = {device_key_handle, 0};
    ev_on_event(EV_KEY_PRESS, &ev);

    static ev_time_event_t oper_timer = {device_oper_timer};
    ev_on_timer(&oper_timer, (1*1000*1000));
    
    led_cfg_init();
    
#if(MOUSE_CALI_ENABLE)
    static ev_event_t cali_start = {device_cali_start_handle, 0};
    ev_on_event(EV_CALI_START, &cali_start);
    static ev_event_t cali_stop = {device_cali_stop_handle, 0};
    ev_on_event(EV_CALI_STOP, &cali_stop);
#endif    
    // Enable interrupt.
    gpio_set_interrupt(GPIO_GYRO,1); 

}
#endif

