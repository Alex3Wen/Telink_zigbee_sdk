
#include "../../proj/tl_common.h"

#include "led_cfg_module_5328.h"
#if(MODULE_LED_ENABLE && __PROJECT_MODULE_5328__)

const int led_pwr_pattern[] = {
    0,          0,
    1000*1000,  0,
    500*1000,      500*1000,
    0,          0,
};

const int led_ind_pattern[] = {
    0,              0,
    500*1000,    50*1000,
    500*1000,    500*1000,
    100*1000,    200*1000,
    500*1000,    (LED_PAIRED_ONCE_TIME - 500)*1000,
    100*1000,    200*1000,
    500*1000,    500*1000,
};

const int led_mic_pattern[] = {
    0,          0,
    500*1000,   500*1000,
    500*1000,   500*1000,
    500*1000,   (LED_PAIRED_ONCE_TIME - 500)*1000,
    500*1000,   500*1000,
    100*1000,   200*1000,
};

led_ctrl_t led_ctrl[LED_MAX] = {
    {LED_GPIO_PWR, (int*)led_pwr_pattern},
    {LED_GPIO_IND, (int*)led_ind_pattern},
    {LED_GPIO_MIC, (int*)led_mic_pattern},
};

static u32 pair_stop_cnt1 = 0;
static u32 pair_stop_cnt2 = 0;
static u32 lost_conn_cnt = 0;
void led_count_init(void){
    pair_stop_cnt1 = pair_stop_cnt2 = lost_conn_cnt = 0;
}

void led_set_next_pattern(int led){
    u8 patt = led_ctrl[led].pattern;
    if(LED_PWR == led){
    }else if(LED_IND == led){
        switch(patt){
        case LED_IND_PAT_BOOT:
            led_ctrl[led].pattern = LED_IND_PAT_QUIET;
            break;
        case LED_IND_PAT_OPER:
        case LED_IND_PAT_PAIR_STOP:
        case LED_IND_PAT_AM_CALI:
            if(++pair_stop_cnt1 == 3){
                led_ctrl[led].pattern = LED_IND_PAT_QUIET;
                pair_stop_cnt1 = 0;
            }
            break;
        case LED_IND_PAT_NOT_CONN:
            if(++lost_conn_cnt >= 3){
                led_ctrl[led].pattern = LED_IND_PAT_QUIET;
                lost_conn_cnt = 0;
            }
            break;
        default:
            break;
        }
    }else if(LED_MIC == led){
        switch(patt){
        case LED_MIC_PAT_PRE_VOICE:
        case LED_MIC_PAT_VOICE:
            led_ctrl[led].pattern = LED_MIC_PAT_VOICE;
            break;
        case LED_MIC_PAT_PAIR_STOP:
        case LED_MIC_PAT_AM_CALI:
        case LED_MIC_PAT_AM_CALI_ERR:
            if(++pair_stop_cnt2 == 3){
                led_ctrl[led].pattern = LED_MIC_PAT_QUIET;
                pair_stop_cnt2 = 0;
            }
            break;
        default:
            break;
        }
    }else{
    }
}

void led_cfg_init(void){
    led_count_init_cb = led_count_init;
}
#endif

