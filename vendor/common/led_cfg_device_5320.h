
#pragma once

#include "../../proj/drivers/led.h"
enum{
    LED_PWR = 0,
    LED_IND,
    LED_MIC,
    LED_MAX,
};

// led0 = power
enum{
    LED_PWR_PAT_QUIET = 0,    // quiet mode must == 0,  see led_handler
    LED_PWR_PAT_CHARGING,
    LED_PWR_PAT_LOW_PWR,
    LED_PWR_PAT_NO_PWR,
    LED_PWR_PAT_MAX,
};

// led1 = indicatior
enum{
    LED_IND_PAT_QUIET = 0,    // quiet mode must == 0,  see led_handler
    LED_IND_PAT_BOOT,
    LED_IND_PAT_OPER,
    LED_IND_PAT_PAIR_START,
    LED_IND_PAT_PAIR_STOP,
    LED_IND_PAT_NOT_CONN,
    LED_IND_PAT_AM_CALI,
    LED_IND_PAT_MAX,
};

// led2 = mic
enum{
    LED_MIC_PAT_QUIET = 0,    // quiet mode must == 0,  see led_handler
    LED_MIC_PAT_PRE_VOICE,
    LED_MIC_PAT_VOICE,
    LED_MIC_PAT_PAIR_STOP,
    LED_MIC_PAT_AM_CALI,
    LED_MIC_PAT_AM_CALI_ERR,
    LED_MIC_PAT_MAX,
};

#define LED_PAIRED_ONCE_TIME   1000

#define LED_GPIO_PWR    GPIO_PWM0
#define LED_GPIO_IND    GPIO_GP24
#define LED_GPIO_MIC    GPIO_SWM

extern led_ctrl_t led_ctrl[LED_MAX];

void led_set_next_pattern(int led);
void led_cfg_init(void);

