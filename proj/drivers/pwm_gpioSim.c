#include "pwm_gpioSim.h"
#include "../os/timer.h"


enum {
    RISING = 0,
    FALLING
};

struct pwm_sim_vars {
    u8  timerId;
    u8  fTimerRunning;
    u8  fRising;
    u32 risingCnt;
    u32 fallingCnt;
    u32 cycleCnt;
    u32 pin;
    u32 preDuty;
};
typedef struct pwm_sim_vars pwm_sim_vars_t;


#define PWM_TIMER            2
#define PWM_SET_TICK(val)    {reg_tmr_tick(PWM_TIMER) = 0; reg_tmr_capt(PWM_TIMER) = val;}
#define PWM_TIMER_CANCEL()   {clock_enable_clock(PWM_TIMER, 0); reg_tmr_sta |= 1 << PWM_TIMER;}


//#ifndef WIN32

pwm_sim_vars_t pwm_sim_v;

void gpioHigh(void)
{
	gpio_set_output_en(pwm_sim_v.pin, 1);
	gpio_write(pwm_sim_v.pin, 1);
}

void gpioLow(void)
{
    gpio_set_output_en(pwm_sim_v.pin, 1);
    gpio_write(pwm_sim_v.pin, 0);
}

#define GPIO_HIGH()          {gpio_set_output_en(pwm_sim_v.pin, 1); gpio_write(pwm_sim_v.pin, 1);}
#define GPIO_LOW()           {gpio_set_output_en(pwm_sim_v.pin, 1); gpio_write(pwm_sim_v.pin, 0);}

int pwm_timerCb(void* param)
{
    u32 edge = (u32)param;

    if(FALLING == edge) {
        gpioLow();
        hwTmr_set(pwm_sim_v.timerId, pwm_sim_v.fallingCnt, pwm_timerCb, (void*)RISING);
    } else {
        gpioHigh();
        hwTmr_set(pwm_sim_v.timerId, pwm_sim_v.risingCnt, pwm_timerCb, (void*)FALLING);
    }
    return 0;
}

void pwm_sim_timer_init(u8 tmrIdx, u8 mode)
{
    clock_set_tmr_mode(tmrIdx, mode);

    /* Reset interrupt flag and status  */
    reg_tmr_sta |= 1 << tmrIdx;
    reg_irq_src |= 1 << tmrIdx;
    reg_irq_mask |= 1 << tmrIdx;
}

void pwm_sim_init(u32 pin, u8 timerId, u32 freq)
{
    gpio_set_func(pin, AS_GPIO);
//    hwTmr_init(timerId, TIMER_MODE_SCLK);
    pwm_sim_timer_init(timerId, TIMER_MODE_SCLK);
    pwm_sim_v.timerId = timerId;
    pwm_sim_v.pin = pin;
    pwm_sim_v.cycleCnt = TIMER_1S/freq;
    //gpioLow();
    pwm_sim_set_duty(0);  // default set to OFF, xavi_requirement
}

rst_t pwm_sim_set_duty(u8 duty)
{
    if(0 == duty) {
        GPIO_LOW();
        if(1 == pwm_sim_v.fTimerRunning){
        	PWM_TIMER_CANCEL();
            pwm_sim_v.fTimerRunning = 0;
        }
    } else if(DUTY_LEVEL == duty){
        GPIO_HIGH();
        if(1 == pwm_sim_v.fTimerRunning){
        	PWM_TIMER_CANCEL();
            pwm_sim_v.fTimerRunning = 0;
        }

    } else {
        pwm_sim_v.risingCnt = pwm_sim_v.cycleCnt*duty/DUTY_LEVEL;
        pwm_sim_v.fallingCnt = pwm_sim_v.cycleCnt - pwm_sim_v.risingCnt;

        //if((pwm_sim_v.risingCnt <= TIMER_SAFE_BOUNDARY) || (pwm_sim_v.fallingCnt <= TIMER_SAFE_BOUNDARY)) {
        //    return FAILURE;
        //}

        if(0 == pwm_sim_v.fTimerRunning){
            GPIO_HIGH();
            //hwTmr_set(pwm_sim_v.timerId, pwm_sim_v.risingCnt, pwm_timerCb, (void*)FALLING);
            PWM_SET_TICK(pwm_sim_v.risingCnt);
            clock_enable_clock(PWM_TIMER, 1);
            pwm_sim_v.fRising = 0;
            pwm_sim_v.fTimerRunning = 1;
        }
    }
    return SUCCESS;
}

void pwm_sim_stop(void)
{
    if(1 == pwm_sim_v.fTimerRunning){
        hwTmr_cancel(pwm_sim_v.timerId);
    }
    gpioLow();
    memset(&pwm_sim_v, 0, sizeof(pwm_sim_vars_t));
}

void pwm_timer_irq(void)
{
	/* Write 1 to clear */
	reg_tmr_sta |= 1 << PWM_TIMER;

	if(pwm_sim_v.fRising) {
		GPIO_HIGH();
        PWM_SET_TICK(pwm_sim_v.risingCnt);
		pwm_sim_v.fRising = 0;
	} else {
		GPIO_LOW();
		PWM_SET_TICK(pwm_sim_v.fallingCnt);
		pwm_sim_v.fRising = 1;
	}
}

//#endif

#if 0
void pwm_sim_example(void)
{
    pwm_sim_init(GPIO_GP25, TIMER_IDX_2, 3000);
    pwm_sim_set_duty(50);
    pwm_sim_stop();

}
#endif


