
#pragma once

#include "../../proj/drivers/led.h"
enum{
	LED_AUX = 0,
	LED_TV,
	LED_DVD,
	LED_CBL,
	LED_MAX
};

typedef struct {
    union {
        struct {
            u8 cnt1 : 4;
            u8 cnt2 : 4;
        } bf;
        u8 byte;
    } flag;   
} led_time_t;

// led0 = AUX
enum{
	LED_AUX_PAT_QUIET = 0,	// quiet mode must == 0,  see led_handler
	LED_AUX_PAT_START,
	LED_AUX_PAT_PAIRING,
	LED_AUX_PAT_PAIR_SUCC,
	LED_AUX_PAT_NOT_CONN,
	LED_AUX_PAT_MAX,
};

// led1 = TV
enum{
	LED_TV_PAT_QUIET = 0,	// quiet mode must == 0,  see led_handler
	LED_TV_PAT_SEND_SUCC,
	LED_TV_PAT_PAIRING,
	LED_TV_PAT_PAIR_SUCC,	
	LED_TV_PAT_NOT_CONN,
	LED_TV_PAT_MAX,
};

// led2 = DVD
enum{
	LED_DVD_PAT_QUIET = 0,	// quiet mode must == 0,  see led_handler
	LED_DVD_PAT_AIR_START_CALI,
	LED_DVD_PAT_PAIRING,
	LED_DVD_PAT_PAIR_SUCC,
	LED_DVD_PAT_AIR_END_CALI,
	LED_DVD_PAT_MAX,
};

// led2 = CBL
enum{
	LED_CBL_PAT_QUIET = 0,	// quiet mode must == 0,  see led_handler
	LED_CBL_PAT_AIR_START_CALI,
	LED_CBL_PAT_PAIRING,
	LED_CBL_PAT_PAIR_SUCC,
	LED_CBL_PAT_AIR_END_CALI,
	LED_CBL_PAT_MAX,
};




#define LED_PAIRED_ONCE_TIME   1000

#ifndef LED_GPIO_AUX
#define LED_GPIO_AUX	GPIO_GP7
#endif

#ifndef LED_GPIO_TV
#define LED_GPIO_TV	GPIO_GP8
#endif

#ifndef LED_GPIO_DVD
#define LED_GPIO_DVD	GPIO_GP9
#endif

#ifndef LED_GPIO_CBL
#define LED_GPIO_CBL	GPIO_GP10
#endif

extern led_ctrl_t led_ctrl[LED_MAX];

void led_set_next_pattern(int led);
void led_cfg_init(void);

