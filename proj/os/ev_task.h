#pragma once

#include "../common/types.h"
#include "../common/priority_queue.h"


/** @addtogroup  TELINK_COMMON_MODULE TELINK Common Module
 *  @{
 */

/** @addtogroup  OS_TASK OS Task
 *  @{
 */
 
/** @defgroup OS_TASK_Constants OS Task Constants
 *  @{
 */

/**
 *  @brief Enumeration for task priority level 
 */
 typedef enum taskPri_t {
    EV_TASK_PRI_HIGH = 0,                   /**< High priority task */
    EV_TASK_PRI_MED,                        /**< Medium priority task */
    EV_TASK_PRI_LOW,                        /**< Low priority task */
    EV_TASK_PRI_NUM                         /**< Task priority number */
} taskPri_t;

/**
 *  @brief Definition for maximum active task number 
 */
#define EV_MAX_TASK_NUM    10

/** @} end of group OS_TASK_Constants */


/** @defgroup OS_TASK_Type OS Task Types
 *  @{
 */
 
/**
 *  @brief Type definition for task callback function 
 */
typedef void (*ev_task_callback_t)(void *data);
 
/**
 *  @brief Type definition for every task event 
 */
typedef struct ev_task_t {
    struct ev_task_t   *next;               /*!< Pointer to the next task */
    u8                 priority;            /*!< The priority of the task */
    ev_task_callback_t pfTask;              /*!< The callback function of the task */
    void*              arg;                 /*!< The argument of task callback function */
} ev_task_t;

/** @} end of group OS_TASK_Type */


/** @defgroup OS_TASK_Functions OS Task API
 *  @{
 */
 
 /**
  * @brief       Initialize the task module
  *
  * @param       None
  *
  * @return      None
  */
void ev_taskInit(void);

 /**
  * @brief       Post a new priority task
  *
  * @param[in]   pri    - Priority defined in @ref taskPri_t
  * @param[in]   pfTask - Pointer for the task callback function
  * @param[in]   arg    - Argument of the callback function
  *
  * @return      ERR_NONE: Success <BR>
  *              Other error code defined in error.h <BR>
  */
rst_t ev_postPriTask (u8 pri, ev_task_callback_t pfTask, void* arg);

 /**
  * @brief       Post a LOW priority task
  *
  * @param[in]   task - Pointer for the task callback function
  * @param[in]   arg  - Argument of the callback function
  *
  * @return      ERR_NONE: Success <BR>
  *              Other error code defined in error.h <BR>
  */
#define POST_TASK(task, arg)      (ev_postPriTask(EV_TASK_PRI_LOW,  task, arg))

 /**
  * @brief       Post a LOW Medium task
  *
  * @param[in]   task - Pointer for the task callback function
  * @param[in]   arg  - Argument of the callback function
  *
  * @return      ERR_NONE: Success <BR>
  *              Other error code defined in error.h <BR>
  */
#define POST_MED_TASK(task, arg)  (ev_postPriTask(EV_TASK_PRI_MED,  task, arg))

 /**
  * @brief       Post a High priority task
  *
  * @param[in]   task - Pointer for the task callback function
  * @param[in]   arg  - Argument of the callback function
  *
  * @return      ERR_NONE: Success <BR>
  *              Other error code defined in error.h <BR>
  */
#define POST_HIGH_TASK(task, arg) (ev_postPriTask(EV_TASK_PRI_HIGH, task, arg))

/**  @} end of group OS_TASK_Functions */

/**  @} end of group OS_TASK */

/**  @} end of group TELINK_COMMON_MODULE */
