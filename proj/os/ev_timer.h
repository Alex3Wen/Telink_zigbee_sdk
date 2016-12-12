#pragma once

#include "../common/types.h"

/** @addtogroup  TELINK_COMMON_MODULE TELINK Common Module
 *  @{
 */

/** @addtogroup  SOFTTIMER Software Timer
 *  @{
 */
 
/** @defgroup SOFTTIMER_TYPE Software Timer Types
 *  @{
 */

/**
 *  @brief Type definition for timer callback function
 */
typedef int (*ev_timer_callback_t)(void *data);
 
/**
 *  @brief Definition for timer event
 */
typedef struct ev_time_event_t {
    ev_timer_callback_t     cb;            //!< Callback function when expire, this must be specified
    u32                     t;             //!< Used internal
    u32                     interval;      //!< Used internal
    void                    *data;         //!< Callback function arguments.
    struct ev_time_event_t  *next;         //!< Used internal
#if(__LOG_RT_ENABLE__)
    int                      id;           //!< Used internal, for realtime VCD log only
#endif
} ev_time_event_t;

/** @} end of group SOFTTIMER_TYPE */

/** @defgroup SOFTTIMER_Functions Software Timer API
 *  @{
 */

/**
  * @brief       Set a new timer
  *
  * @param[in]   e  - The timer event including the callback function
  * @param[in]   us - Interval time in microsecond
  *
  * @return      None
  */
void ev_on_timer(ev_time_event_t * e, u32 t_us);

/**
  * @brief       Cancel an existed timer
  *
  * @param[in]   e  - The existed timer event
  *
  * @return      None
  */
void ev_unon_timer(ev_time_event_t * e);

/**
  * @brief       Check whether a specified timer expired or not
  *
  * @param[in]   e  - The specified timer event
  *
  * @return      True indicating the timer is already expired. <BR>
  *              False indicating the timer is still exist. <BR>
  */
int is_timer_expired(ev_time_event_t *e);

/**  @} end of group SOFTTIMER_Functions */

/**  @} end of group SOFTTIMER */

/**  @} end of group TELINK_COMMON_MODULE */