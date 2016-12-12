
#pragma once

#include "../common/types.h"
#include "../config/user_config.h"
#include "../mcu/clock.h"

#if  EV_POST_TASK_ENABLE
#include "ev_task.h"
#endif  /* EV_POST_TASK_ENABLE */

#include "ev_timer.h"


enum{EV_FIRED_EVENT_MAX_MASK = EV_FIRED_EVENT_MAX - 1};

typedef void (*ev_poll_callback_t)(void);
typedef void (*ev_event_callback_t)(void *data);

// file event
typedef struct ev_event_t{
    ev_event_callback_t    cb;
    struct ev_event_t *next;
}ev_event_t;

typedef struct ev_fired_event_t{
    int                    e;            //  occupied 8 bytes anyway, use int
    void*                data;
}ev_fired_event_t;



typedef struct ev_poll_t{
    int valid;
    ev_poll_callback_t    cb;
}ev_poll_t;


typedef struct ev_loop_ctrl_t{
    ev_event_t                 *events[EV_EVENT_MAX]; /* Registered file events and callback */
/*
    There could be dozens of registered events, may be only several fired.
    Loop a small fired array is more efficient than that loop all then check fired-flag. 
*/    
    ev_fired_event_t        fired_queue[EV_FIRED_EVENT_MAX];
    int                        fired_count;
    int                        fired_index;
/*
    Pool callbacks can be added and removed frequently. We could use double-linked list instead.
    But it may be less than several vaiable poll events, use array is faster.
*/    
    ev_poll_t                poll[EV_POLL_MAX];
/*
    Time events is sorted, use single linked list
*/    
    ev_time_event_t        *timer_head;
    ev_time_event_t     *timer_nearest;        // find the nearest fired timer, 


#if EV_POST_TASK_ENABLE
    ev_task_t    *taskArray;
    priQueue_t   actTaskQ;
    priQueue_t   freeTaskQ;

#endif  /* EV_POST_TASK_ENABLE */

    
}ev_loop_ctrl_t;

enum { EV_TIMER_SAFE_MARGIN_US = 4000000, EV_TIMER_SAFE_MARGIN = (EV_TIMER_SAFE_MARGIN_US * CLOCK_SYS_CLOCK_1US) };        // in us,  
    

// will be called in every main loop
void ev_on_poll(ev_poll_e e, ev_poll_callback_t cb);
void ev_enable_poll(ev_poll_e e);
void ev_disable_poll(ev_poll_e e);
void ev_on_event(ev_event_e e, ev_event_t *ev);
// void ev_unon_event(ev_event_e e);
void ev_emit_event(ev_event_e e, void *data);
void ev_emit_event_syn(ev_event_e e, void *data);
void ev_clear_event(void);
void ev_start_timer(ev_time_event_t * e);
void ev_set_timer(ev_time_event_t *e, int t_us);
int ev_timer_expired(ev_time_event_t *e);
void ev_main(void);
u8 ev_isTaskDone(void);

