/**************************************************************************************************
  Filename:       priority_queue.h
  Revised:        $Date: 2013-05-27 $

  Description:    Interface of priority queue. A small priority value has a higher priority 
**************************************************************************************************/
#pragma once

#include "../common/types.h"


/** @addtogroup  TELINK_COMMON_MODULE TELINK Common Module
 *  @{
 */

/** @addtogroup  PRIORITY_QUEUE Priority Queue
 *  @{
 */
 
/** @defgroup priQueue_Public_Type PriorityQueue Types
 *  @{
 */

/**        
 *  @brief Type definition for priority calculate function
 */
typedef u32 (*priFunc_t)(arg_t);

/**        
 *  @brief Structure of an item in the priority queue
 */
typedef struct priQueue_item {
    struct priQueue_item *next;        /*!< Pointer to the next element */
    u8 data[1];                        /*!< Pointer to the data */
} priQueue_item_t;


/**
 *  @brief Structure of the priority queue
 */
typedef struct priQueue {
    priQueue_item_t *head;             /*!<  Pointer to the head item of the queue */
    priQueue_item_t *tail;             /*!<  Pointer to the tail item of the queue */
    priFunc_t priFunc;                 /*!<  Priority function, NULL means not use priority */
    u32 current_capacity;              /*!<  Holds the current number of entries in the queue */
} priQueue_t;

/**  @} end of group priQueue_Public_Type */


/** @defgroup priQueue_Public_Function PriorityQueue API
 *  @brief Function declaration of priority queue module
 *  @{
 */

 /**
   * @brief       Initialize the priority queue 
   *
   * @param[in]   priQ     - Pointer to the priority queue
   * @param[in]   priFunc  - Pointer to the function that calculates a priority
   *                         NULL means not use the priority feature
   *
   * @return      ERR_NONE: Success <BR>
   *              Other error code defined in error.h <BR>
   */
rst_t priQ_init( priQueue_t *priQ, priFunc_t priFunc);


 /**
   * @brief       Push a data part of an element into a queue
   *
   * @param[in]   priQ     - Pointer to the priority queue
   * @param[in]   payload  - Pointer to the data part of bufferItem  
   *
   * @return      ERR_NONE: Success <BR>
   *              Other error code defined in error.h <BR>
   */
rst_t priQ_push( priQueue_t* priQ, u8* payload );


/**
  * @brief       Pop data part of the element with the highest priority.
  *              If there are multiple elements, then pop one that arrived the queue first.
  *
  * @param[in]   priQ - Pointer to the priority queue 
  *
  * @return      Pointer to data part of the bufferItem that is being popped
  */
u8* priQ_pop( priQueue_t* priQ );


  /**
   * @brief       Delete an element from the queue
   *
   * @param[in]   priQ     - Pointer to the priority queue
   * @param[in]   payload  - Pointer to data part of the bufferItem that is to be deleted
   *
   * @return      ERR_NONE: Success <BR>
   *              Other error code defined in error.h <BR>
   */
rst_t priQ_delete( priQueue_t* priQ, u8* payload );


  /**
   * @brief       Free up a queue. This also deallocates related buffers.
   *
   * @param[in]   priQ - Pointer to the priority queue
   *
   * @return      ERR_NONE: Success <BR>
   *              Other error code defined in error.h <BR>
   */
rst_t priQ_freeQueue( priQueue_t* priQ);


  /**
   * @brief       Push a raw data into a queue
   *              The element must compatible with the format of priQueue_item_t
   *
   * @param[in]   priQ       - Pointer to the priority queue
   * @param[in]   newElement - Pointer to the new element  
   *
   * @return      ERR_NONE: Success <BR>
   *              Other error code defined in error.h <BR>
   */
rst_t priQ_rawPush( priQueue_t* priQ, priQueue_item_t* newElement );


 /**
   * @brief       Delete an element from the queue
   *              The element must compatible with the format of priQueue_item_t
   *
   * @param[in]   priQ       - Pointer to the priority queue
   * @param[in]   delElement - Pointer to data part of the bufferItem that is to be deleted
   *
   * @return      ERR_NONE: Success <BR>
   *              Other error code defined in error.h <BR>
   */
rst_t priQ_rawDelete(priQueue_t* priQ, priQueue_item_t* delElement);


 /**
  * @brief       Pop data part of the element with the highest priority. 
  *
  * @param[in]   priQ - Pointer to the priority queue 
  *
  * @return      Pointer to first element in the queue
  */
priQueue_item_t* priQ_rawPop(priQueue_t* priQ);

/**  @} end of group priQueue_Public_Function */

/**  @} end of group PRIORITY_QUEUE */

/**  @} end of group TELINK_COMMON_MODULE */

