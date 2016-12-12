#pragma once


enum {
	ONOFF_DIRECTLY,
	ONOFF_WITHSLOWMOVE,
};

#ifndef USE_SW_PWM
  #ifndef USE_HW_PWM
    #define USE_HW_PWM    1
  #endif
#endif


#define HW_LIGHT_PWM_ID            1
#define HW_LIGHT_PWM_PIN           GPIO_PWM1
#define HW_LIGHT_PWM_FREQ          1000  // 1K Hz

#define SW_LIGHT_PWM_PIN           GPIO_GP23
#define SW_LIGHT_PWM_TIMER         TIMER_IDX_2
#define SW_LIGHT_PWM_FREQ          1     // 1Hz



#define LEVEL_MAX                  0xFE
#define LEVEL_MIN                  0
#define LIGHT_MIN_LEVEL            0x20
#define LEVEL_DFLT_DUTY            99     // dimmable 100%
#define LEVEL_DFLT_LEVEL           0      // dimmable 100%
#define TRANS_TIME_100MS           100000
#define TRANS_TIME_10MS            10000
#define TRANS_TIME_3MS             3000

#define CAL_PWM_DUTY(level)        (255-level)//(100*level/255)

u8   hw_isBusy(void);
void hw_lightOn(u8 effect);
void hw_lightOff(u8 effect, u8 curLvl);
void hw_lightOnToLevel(u8 level, u8 effect);
void hw_lightMoveToLevel(u8 curLv, u8 targetLvl, u16 transTime);
void hw_setLevel(u8 level);
void hw_pwmInit(u8 pwmId, u32 pwmPin, u32 freq);
u8   hw_stopLevelupdTimer(void);

void hw_lightInit(void);