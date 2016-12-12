#pragma once

#include "../tl_common.h"

/** @addtogroup PWM_GPIO_SIM
 *  @{
 */

/** @defgroup PWM_GPIO_SIM_Public_Macro
 *  @brief Macro definition of PWM Sim 
 *  @{
 */

/**
 *  @brief This macro TIMER_1S should be changed for different frequency.
 *  This simulative pwm function is based on timer interrupt. When the frequency is 1Hz, only 2 interrupts
 *  will be generated in one second. But in 3KHz, the number of interrupts will be 6K. The TIMER_1S macro 
 *  value should be smaller to avoid additional cost of interrupt handling when the frequency is higher.
 *
 *  This is the reference value for 1Hz, 1KHz and 3KHz:
 *  1Hz:  30000000
 *  1KHz: 23500000
 *  3kHz: 17000000
 */
#define TIMER_1S 30000000

/**
 *  @brief The minimum value of hardware timer interval. If the pwm_sim_set_duty function always return FAIL,
    when the frequency is high, this value should be smaller.
 */
#define TIMER_SAFE_BOUNDARY   10*CLOCK_SYS_CLOCK_1US

#define DUTY_LEVEL            100

/*  @} end of group PWM_GPIO_SIM_Public_Macro */


/** @defgroup PWM_GPIO_SIM_Public_Functions
 *  @brief Function declaration of PWM Sim 
 *  @{
 */

/**
 * @brief: Initialize the pwm sim, choose the GPIO pin, timer ID and set the frequency.
 *
 * @param [in] pin - select GPIO pin.
 *
 * @param [in] timerId - select timer.
 *
 * @param [in] freq - set pwm frequency, its unit is Hz.
 *
 * @return void
 */
void pwm_sim_init(u32 pin, u8 timerId, u32 freq);

/**
 * @brief: Stop pwm. The duty-cycle will be 0.
 *
 * @param none
 *
 * @return void
 */
void pwm_sim_stop(void);

/**
 * @brief: Change duty cycle. The frequency is the value set by pwm_sim_init function.
 *
 * @param [in] duty - set pwm duty-cycle, range 0~100.
 *
 * @return status
 */

rst_t pwm_sim_set_duty(u8 duty);

/*  @} end of group PWM_GPIO_SIM_Public_Functions */

/*  @} end of group PWM_GPIO_SIM */


