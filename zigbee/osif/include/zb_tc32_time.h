/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: TC32-specific timer implementation
*/

#ifndef ZB_TC32_TIME_H
#define ZB_TC32_TIME_H 1

/** @addtogroup hardware_timer_index Hardware Timer Index
 * @{
 */
#define TIMER_IDX_0             0                   //!< Timer0 used as system tick
#define TIMER_IDX_1             1                   //!< Timer1 used as software timer @ref SOFTTIMER
#define TIMER_IDX_2             2                   //!< Timer2 is for user use
#define TIMER_NUM               3                   //!< Total number of timer
#define TIMER_FOR_USER          TIMER_IDX_2         //!< Macro for the timerIdx used by user
/** @} end of group hardware_timer_index */

/** @addtogroup hardware_timer_mode Hardware Timer Mode
 * @{
 */
#define TIMER_MODE_SCLK         0                   //!< Timer running in the system clock mode, it will free run from 0 to 0xffffffff
#define TIMER_MODE_GPIO         1                   //!< Timer running in the system clock mode, it will free run from 0 to 0xffffffff
#define TIMER_MODE_WIDTH_GPI    2
#define TIMER_MODE_TICK         3
/** @} end of group hardware_timer_mode */


/*! \addtogroup ZB_OSIF_TC32 */
/*! @{ */

#ifdef ZB_TC32_TIMER
/**
   \par Time implementation based on HW timer in TC32.

   The idea is to use timer interrupt.

   All that functions are internal timer implementation.
   See zb_scheduler.h for the public timer API.
 */

/*
  1 operation time = 1/ZB_XTAL_FREQ
  ticks count (per 1 msec) = 1 msec / operation_time (msec)

*/

/* for SDCC: handler prototype MUST be defined in the same file with main() function */
#define DECLARE_TIMER0_INTER_HANDLER() \
  void timer0_inter_handler(void) INTERRUPT_DEFINITION(TIMER0_INTER_NUMBER, REGISTER_BANK_3);
  

/*
It seems all timeouts in MAC are multiples for beacon interval. Maximal value of
timeout in MAC is (2^14 + 1) = 16385 beacon intervals. 1 beacon interval = 15.36 ms
and it is calculated as follows:
1 beacon interval = aBaseSuperframeDuration * symbol duration
aBaseSuperframeDuration = aBaseSlotDuration * aNumSuperframeSlots
aBaseSlotDuration = 60
aNumSuperframeSlots = 16
1 symbol = 16e-6 sec
TC32 with 24.5 MHz oscilator with 16-bit timer maximal time interval is 128 ms
(with system clock division by 48) it is nearly equal to 8 beacon intervals,
and 32 ms with system clock division by 12.

So, the idea is to use 1 beacon interval to measure timeout interval. Timer is set
to fire timer interrupt handler every 15.36 ms and internal counter is used to measure
time interval in "beacon intervals".
*/

/* timer value = (15360 * Oscillator MHz) / (clock divider) */
#ifdef CTC32F120
#define ZB_SYSTEM_OSCILLATOR_DIVIDER 48
#elif defined ZB_CC25XX
#define ZB_SYSTEM_OSCILLATOR_DIVIDER 128
#else
#define ZB_SYSTEM_OSCILLATOR_DIVIDER 2
#endif
/* TODO: check me for TI_CC2530 */
#ifdef ZB_CC25XX
#define ZB_TC32_TIMER_VALUE (zb_uint16_t)(((zb_uint16_t)ZB_BEACON_INTERVAL_USEC / ZB_SYSTEM_OSCILLATOR_DIVIDER) * ZB_SHORT_XTAL_FREQ)
#else
#define ZB_TC32_TIMER_VALUE (ZB_MAX_TIME_VAL - (zb_uint16_t)(((zb_uint16_t)ZB_BEACON_INTERVAL_USEC / ZB_SYSTEM_OSCILLATOR_DIVIDER) * ZB_SHORT_XTAL_FREQ))
#endif

#define ZB_TIMER_LOW_BYTE ZB_GET_LOW_BYTE(ZB_TC32_TIMER_VALUE)
#define ZB_TIMER_HI_BYTE  ZB_GET_HI_BYTE(ZB_TC32_TIMER_VALUE)

#define ZB_TIMER_INIT() zb_5320_init()

extern u8 tc_isTimerRuning;

#define ZB_CHECK_TIMER_IS_ON() ( tc_isTimerRuning == 1 ) /* TRUE if timer is ON */

/* start timer 1 */

#define ZB_START_HW_TIMER() zb_start_5320_timer(1)


void zb_5320_init(void);

void zb_start_5320_timer(u8 tmrIdx);

#endif  /* ZB_TC32_TIMER */

/*! @} */

#endif /* ZB_TC32_TIME_H */
