
#include "../../proj/tl_common.h"


/**********************************************************************
 * INCLUDES
 */
#include "../../proj/drivers/pwm_gpioSim.h"
#include "../../proj/drivers/pwm.h"
#include "light_hwControl.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */

#if USE_SW_PWM
#define LIGHT_SET_LEVEL(level)     pwm_sim_set_duty(level)
#define LIGHT_ON_TO_LEVEL(level)   LIGHT_SET_LEVEL(level)
#define LIGHT_ON()                 pwm_sim_set_duty(100)
#define LIGHT_OFF()                pwm_sim_set_duty(0)
#endif

#if USE_HW_PWM
#define LIGHT_SET_LEVEL(level)     hw_setLevel(level)
#define LIGHT_ON_TO_LEVEL(level)   LIGHT_SET_LEVEL(level)
#define LIGHT_ON()                 hw_setLevel(255);//do {pwm_stop(1); gpio_set_output_en(GPIO_PWM1, 1);gpio_write(GPIO_PWM1, 0);light_ctrl_v->fPwmDisable = 1;}while(0);
#define LIGHT_OFF()                hw_setLevel(0);
#endif

/**********************************************************************
 * TYPEDEFS
 */
typedef struct light_ctrl_tag{
    u8  onOff;
    u8  hwCurLvl;
    u8  hwCurPwmDuty;

    u8  moving;
    u16 remainTim;
    u8  dir;
    u8  fPwmDisable;

	u16 stepLvl_256;
	u16 hwCurLvl_256;

    u8 pwmId;
    u32 pwmPin;
    u32 freq;

	ev_time_event_t timer;

} light_ctrl_t;

/**********************************************************************
 * LOCAL VARIABLES
 */

light_ctrl_t light_ctrl_vs;
light_ctrl_t *light_ctrl_v = &light_ctrl_vs;


/**********************************************************************
 * LOCAL FUNCTIONS
 */

void hw_pwmStart(void)
{
    gpio_set_func(light_ctrl_v->pwmPin, AS_PWM);
    pwm_set(light_ctrl_v->pwmId, light_ctrl_v->freq, -1, light_ctrl_v->pwmId);
    pwm_start(light_ctrl_v->pwmId);
}

void hw_pwmInit(u8 pwmId, u32 pwmPin, u32 freq)
{
    light_ctrl_v->pwmId = pwmId;
    light_ctrl_v->pwmPin = pwmPin;
    light_ctrl_v->freq = freq;

    hw_pwmStart();
}

void hw_setLevel(u8 level)
{
    u8 lev = level;                                                          
    static u8 preLev = 0;

    if(lev == preLev) {
        return;
    }
    
    if(preLev == 255) {
        hw_pwmStart();
    }
    
    if(lev == 255) {
        gpio_set_func(light_ctrl_v->pwmPin, AS_GPIO);
        gpio_set_output_en(light_ctrl_v->pwmPin, 1);
        gpio_write(light_ctrl_v->pwmPin, 0);
    } else {
        if((lev < LIGHT_MIN_LEVEL) && (lev > LEVEL_MIN)){
            lev = LIGHT_MIN_LEVEL;
        }
        REG_ADDR8(0xac) = CAL_PWM_DUTY(lev);
    }
    
    preLev = lev;
}

/*********************************************************************
 * @fn      hw_updateLevel
 *
 * @brief   Calculate the step and doing the actually moving operation
 *
 * @param   None
 *
 * @return  None
 */
void hw_updateLevel(void)
{
	if ( (light_ctrl_v->dir) && (((light_ctrl_v->hwCurLvl_256 + light_ctrl_v->stepLvl_256)>>8) > LEVEL_MAX )) {
		light_ctrl_v->hwCurLvl_256 = (u16)LEVEL_MAX << 8;
	} else if ( (!light_ctrl_v->dir) && ( ((light_ctrl_v->hwCurLvl_256 - light_ctrl_v->stepLvl_256)/256) < LEVEL_MIN )) {
		light_ctrl_v->hwCurLvl_256 = (u16)LEVEL_MIN << 8;
	} else {
		if (light_ctrl_v->dir) {
			light_ctrl_v->hwCurLvl_256 += light_ctrl_v->stepLvl_256;
		} else {
			light_ctrl_v->hwCurLvl_256 -= light_ctrl_v->stepLvl_256;
		}

	}

	if (light_ctrl_v->dir) {
		//fraction step compensation
		light_ctrl_v->hwCurLvl = ( light_ctrl_v->hwCurLvl_256 + 127 ) / 256;
	} else {
		light_ctrl_v->hwCurLvl = ( light_ctrl_v->hwCurLvl_256 / 256 );
	}

	if (light_ctrl_v->remainTim == 0x0) {
		// align variables
		light_ctrl_v->hwCurLvl_256 = ((u16)light_ctrl_v->hwCurLvl)*256 ;
		light_ctrl_v->stepLvl_256 = 0;
	} else if (light_ctrl_v->remainTim != 0xFFFF) {
		light_ctrl_v->remainTim --;
	}

	if (light_ctrl_v->hwCurLvl > LEVEL_MIN)
		light_ctrl_v->onOff = 1;


	LIGHT_SET_LEVEL( light_ctrl_v->hwCurLvl );

}
#if 0
void hw_updateLevel()
{
	/*if (light_ctrl_v->hwCurLvl_256 < 5) {
		(light_ctrl_v->hwCurLvl_256)++;
		return;
	}*/

//	if ( light_ctrl_v->dir && ((light_ctrl_v->hwCurLvl+1) > LEVEL_MAX )) {
		//light_ctrl_v->hwCurLvl = LEVEL_MAX;
//		goto normal;
//	} else if ( (!light_ctrl_v->dir) && ((light_ctrl_v->hwCurLvl-1) == LEVEL_MIN )) {
		//light_ctrl_v->hwCurLvl = LEVEL_MIN;
//		goto normal;
//	} else {
		if (light_ctrl_v->dir) {
			light_ctrl_v->hwCurLvl += 1;
		} else {
			light_ctrl_v->hwCurLvl -= 1;
		}
//	}

	/*if (light_ctrl_v->dir) {
		//fraction step compensation
		light_ctrl_v->hwCurLvl = ( light_ctrl_v->hwCurLvl_256 + 127 ) / 256;
	} else {
		light_ctrl_v->hwCurLvl = ( light_ctrl_v->hwCurLvl_256 / 256 );
	}*/
normal:
	if (light_ctrl_v->remainTim == 0x0) {
		// align variables
		//light_ctrl_v->hwCurLvl_256 = ((u16)light_ctrl_v->hwCurLvl)*256 ;
		light_ctrl_v->stepLvl_256 = 0;
	} else if (light_ctrl_v->remainTim != 0xFFFF) {
		light_ctrl_v->remainTim--;
	}

	if (light_ctrl_v->hwCurLvl > LEVEL_MIN)
		light_ctrl_v->onOff = 1;

	LIGHT_SET_LEVEL( light_ctrl_v->hwCurLvl );
}
#endif
/*********************************************************************
 * @fn      levelCtrl_timerCb
 *
 * @brief   Timer callback for the each moving step
 *
 * @param   None
 *
 * @return  None
 */
int levelCtrl_timerCb(void* param)
{
	if (light_ctrl_v->remainTim) {
		hw_updateLevel();
	}

	if (light_ctrl_v->hwCurLvl <= LEVEL_MIN) {
		LIGHT_OFF();
		light_ctrl_v->onOff = 0;
	}

	printf("current level: %d current onoff: %d\n", light_ctrl_v->hwCurLvl, light_ctrl_v->onOff);

	if (light_ctrl_v->remainTim) {
		return 0;
	} else {
		printf("\n");
		light_ctrl_v->moving = 0;
		return -1;
	}
}


/*********************************************************************
 * @fn      hw_isBusy
 *
 * @brief   Check whether the moving operation is underway
 *
 * @param   None
 *
 * @return  1 indicating busy
 */
u8 hw_isBusy(void)
{
	return light_ctrl_v->moving;
}


/*********************************************************************
 * @fn      hw_lightMoveToLevel
 *
 * @brief   Execute move to level operation in hardware
 *
 * @param   curLv Current level
 * @param   targetLvl The target level intend to move to
 * @param   transTime The transaction time during the move
 *
 * @return  None
 */
void hw_lightMoveToLevel(u8 curLv, u8 targetLvl, u16 transTime)
{
	/*if (targetLvl <= LEVEL_MIN) {
		LIGHT_OFF();
		return;
	}*/

	if (light_ctrl_v->fPwmDisable) {
		/* Restart PWM */
		pwm_start(1);
		light_ctrl_v->fPwmDisable = 0;
	}

	if (targetLvl == curLv)
		return;

	//transTime = 1;
	light_ctrl_v->hwCurLvl = curLv;
	light_ctrl_v->hwCurLvl_256 = curLv << 8;
	light_ctrl_v->remainTim = (transTime == 0) ? 1 : transTime;

	if (targetLvl > curLv) {
		light_ctrl_v->dir = 1;
		light_ctrl_v->stepLvl_256 = (targetLvl - curLv) << 8;
	} else {
		light_ctrl_v->dir = 0;
	    light_ctrl_v->stepLvl_256 = (curLv - targetLvl) << 8;
	}
	light_ctrl_v->stepLvl_256 /= light_ctrl_v->remainTim;


	printf("target level: %d  current level: %d current onoff: %d\n", targetLvl, light_ctrl_v->hwCurLvl, light_ctrl_v->onOff);
	hw_updateLevel();
	printf("                  current level: %d current onoff: %d\n", light_ctrl_v->hwCurLvl, light_ctrl_v->onOff);

	if (light_ctrl_v->remainTim) {
		light_ctrl_v->moving = 1;
		light_ctrl_v->timer.cb = levelCtrl_timerCb;
		ev_on_timer(&light_ctrl_v->timer, TRANS_TIME_100MS);
	}

}
#if 0
void hw_lightMoveToLevel(u8 curLv, u8 targetLvl, u16 transTime)
{
	if (light_ctrl_v->fPwmDisable) {
		/* Restart PWM */
		pwm_start(1);
		light_ctrl_v->fPwmDisable = 0;
	}

	if (targetLvl == curLv)
		return;

	//transTime = 1;
	light_ctrl_v->hwCurLvl = curLv;
	u8 timeCount;
	//light_ctrl_v->hwCurLvl_256 = curLv << 8;

	if (targetLvl > curLv) {
		light_ctrl_v->dir = 1;
		timeCount = targetLvl - curLv;
	} else {
		light_ctrl_v->dir = 0;
	    timeCount = curLv - targetLvl;
	}
	light_ctrl_v->stepLvl_256 = 1;
	light_ctrl_v->remainTim = timeCount;
	//light_ctrl_v->hwCurLvl_256 = 0;

	printf("target level: %d  current level: %d current onoff: %d\n", targetLvl, light_ctrl_v->hwCurLvl, light_ctrl_v->onOff);
	hw_updateLevel();
	printf("                  current level: %d current onoff: %d\n", light_ctrl_v->hwCurLvl, light_ctrl_v->onOff);

	if (light_ctrl_v->remainTim) {
		light_ctrl_v->moving = 1;
		light_ctrl_v->timer.cb = levelCtrl_timerCb;
		ev_on_timer(&light_ctrl_v->timer, TRANS_TIME_3MS);
	}
}
#endif
/*********************************************************************
 * @fn      hw_lightOff
 *
 * @brief   Execute off operation in hardware
 *
 * @param   effect Specify the effect during OFF
 * @param   curLvl Current level
 *
 * @return  None
 */
void hw_lightOff(u8 effect, u8 curLvl)
{
	if (light_ctrl_v->fPwmDisable) {
	    /* Restart PWM */
		pwm_start(1);
		light_ctrl_v->fPwmDisable = 0;
	}

    if (effect == ONOFF_DIRECTLY) {
        LIGHT_OFF();
    } else {
    	hw_lightMoveToLevel(curLvl, 99, 10);
    }
}

/*********************************************************************
 * @fn      hw_lightOn
 *
 * @brief   Execute ON operation in hardware
 *
 * @param   effect Specify the effect during OFF
 *
 * @return  None
 */
void hw_lightOn(u8 effect)
{
	if (effect == ONOFF_DIRECTLY) {
		LIGHT_ON();
	} else {
		//hw_lightMoveToLevel(LEVEL_MIN, 0, 10);
	}
}


/*********************************************************************
 * @fn      hw_lightOnToLevel
 *
 * @brief   Execute ON operation in hardware, but it go to the specified level
 *
 * @param   level  Specify target level
 * @param   effect Specify the effect during ON
 *
 * @return  None
 */
void hw_lightOnToLevel(u8 level, u8 effect)
{
	if (effect == ONOFF_DIRECTLY) {
		//if (level <= LEVEL_MIN) {
		//    level = 10;
		//}
		LIGHT_ON_TO_LEVEL(level);
	} else {
		//hw_lightMoveToLevel(LEVEL_MIN, level, 10);
	}
}

u8 hw_stopLevelupdTimer()
{
	ev_unon_timer(&light_ctrl_v->timer);

	light_ctrl_v->moving = 0;
	if (light_ctrl_v->remainTim) {
		light_ctrl_v->remainTim = 0;
	}

	return light_ctrl_v->hwCurLvl;
}



void hw_lightInit(void)
{
#ifdef USE_HW_PWM
  #ifndef ZB_LED_EN
    hw_pwmInit(HW_LIGHT_PWM_ID, HW_LIGHT_PWM_PIN, HW_LIGHT_PWM_FREQ);
  #endif
#else
    pwm_sim_init(LED_LIGHTING, TIMER_IDX_2, XAVI_PWM_FREQ);
#endif

#if SAVE_FLASH
    // TODO: Load the light attribute saved in the flash and restore.
#endif
}
