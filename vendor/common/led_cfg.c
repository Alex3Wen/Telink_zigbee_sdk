
#include "../../proj/tl_common.h"

#include "led_cfg.h"

const int led_aux_pattern[] = {
	0,      	0,                       //QUITE
	500*1000,   500*1000,                //START
	300*1000,  	500*1000,                //PAIRING
	500*1000,  	500*1000,                //PIARED
	100*1000,  	200*1000,                //NOT_CNNET
};

const int led_tv_pattern[] = {
	0, 		     0,
	500*1000,    50*1000,
	300*1000,    500*1000,
	500*1000,    500*1000,
	100*1000,    200*1000,
};

const int led_dvd_pattern[] = {
	0,      	0,
	300*1000,   500*1000,
	300*1000,   500*1000,
	500*1000,   500*1000,
	500*1000,   300*1000,
};

const int led_cbl_pattern[] = {
	0,      	0,
	300*1000,   500*1000,
	300*1000,   500*1000,
	500*1000,   500*1000,
	500*1000,   300*1000,
};


led_ctrl_t led_ctrl[LED_MAX] = {
	{LED_GPIO_AUX, (int*)led_aux_pattern},
	{LED_GPIO_TV, (int*)led_tv_pattern},
	{LED_GPIO_DVD, (int*)led_dvd_pattern},
	{LED_GPIO_CBL, (int*)led_cbl_pattern},
};

static led_time_t led_aux, led_tv, led_dvd, led_cbl;

void led_count_init(void) {
    led_aux.flag.byte = led_tv.flag.byte = led_dvd.flag.byte = led_cbl.flag.byte = 0;
}

void led_set_next_pattern(int led) {
    u8 patt = led_ctrl[led].pattern;
	if( LED_AUX == led ) {
	    if ( patt == LED_AUX_PAT_START ) {
            led_ctrl[led].pattern = LED_AUX_PAT_QUIET;
	    } else if ( patt == LED_AUX_PAT_PAIR_SUCC ) {
            if ( led_aux.flag.bf.cnt1++ == 3 ) {
                led_ctrl[led].pattern = LED_AUX_PAT_QUIET;
                led_aux.flag.bf.cnt1 = 0;
            }
	    } else if ( patt == LED_AUX_PAT_NOT_CONN ) {
            if ( led_aux.flag.bf.cnt2++ == 2 ) {
                led_ctrl[led].pattern = LED_AUX_PAT_QUIET;
                led_aux.flag.bf.cnt2 = 0;
            }
	    }
	}else if( LED_TV == led ) {
		if ( patt == LED_TV_PAT_SEND_SUCC ) {
            led_ctrl[led].pattern = LED_TV_PAT_QUIET;
	    } else if ( patt == LED_TV_PAT_PAIR_SUCC ) {
            if ( led_tv.flag.bf.cnt1++ == 3 ) {
                led_ctrl[led].pattern = LED_TV_PAT_QUIET;
                led_tv.flag.bf.cnt1 = 0;
            }
	    } else if ( patt == LED_TV_PAT_NOT_CONN ) {
            if ( led_tv.flag.bf.cnt2++ == 2 ) {
                led_ctrl[led].pattern = LED_TV_PAT_QUIET;
                led_tv.flag.bf.cnt2 = 0;
            }
	    }
	}else if( LED_DVD == led ){
		if ( patt == LED_DVD_PAT_PAIR_SUCC ) {
            if ( led_dvd.flag.bf.cnt1++ == 3 ) {
                led_ctrl[led].pattern = LED_DVD_PAT_QUIET;
                led_dvd.flag.bf.cnt1 = 0;
            }
	    } else if ( (patt == LED_DVD_PAT_AIR_START_CALI) || (patt == LED_DVD_PAT_AIR_END_CALI) ) {
            if ( led_dvd.flag.bf.cnt2++ == 2 ) {
                led_ctrl[led].pattern = LED_DVD_PAT_QUIET;
                led_dvd.flag.bf.cnt2 = 0;
            }
	    }  
	}else if ( LED_CBL == led ) {
	    if ( patt == LED_CBL_PAT_PAIR_SUCC ) {
            if ( led_cbl.flag.bf.cnt1++ == 3 ) {
                led_ctrl[led].pattern = LED_CBL_PAT_QUIET;
                led_cbl.flag.bf.cnt1 = 0;
            }
	    } else if ( (patt == LED_CBL_PAT_AIR_START_CALI) || (patt == LED_CBL_PAT_AIR_END_CALI) ) {
            if ( led_cbl.flag.bf.cnt2++ == 2 ) {
                led_ctrl[led].pattern = LED_CBL_PAT_QUIET;
                led_cbl.flag.bf.cnt2 = 0;
            }
	    }
	}
}

void led_cfg_init(void){
    led_count_init_cb = led_count_init;
}
