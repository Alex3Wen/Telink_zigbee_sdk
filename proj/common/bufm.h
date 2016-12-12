/**************************************************************************************************
  Filename:       bufm.h
  Revised:        $Date: 2013-05-27 $

  Description:    Interface of buffer management
**************************************************************************************************/

#pragma once

#include "../common/types.h"


/** @addtogroup  TELINK_COMMON_MODULE TELINK Common Module
 *  @{
 */

/** @addtogroup  BUFF_MGMT Buffer Management
 *  @{
 */
 
/** @defgroup bufm_Public_Constant Buff Management Constants
 *  @{
 */


/** @addtogroup bufm_size_index BUFM Block Sizes
 * Length of the data field in the bufferItem
 * @{
 */
#define SIZE_0                   32         /*!< size of buffer block_0 */
#define SIZE_1                   64         /*!< size of buffer block_1 */
#define SIZE_2                   200        /*!< size of buffer block_2 */
#define SIZE_MAX                 SIZE_2     /*!< size of the maximum buffer block */

/** @} end of group bufm_size_index */

/**
 * @brief Default buffer item number in each size
 */
#define DFLT_BUFFER_ITEM_COUNT   8


/** @addtogroup bufm_typical_size BUFM Typical Application Size
 * Default buffer size for different typical usage
 * @{
 */
#define DFLT_SMALL_BUF_SIZE      48         /*!< In this size, buffer module will allocate the SIZE_1 buffer */
#define DFLT_LARGE_BUF_SIZE      190        /*!< In this size, buffer module will allocate the SIZE_2 buffer */

/** @} end of group bufm_typical_size */

/**  @} end of group bufm_Public_Constant */


/** @defgroup bufm_Public_Type Buff Management Types
 *  @{
 */

/**
 *  @brief Structure of a buffer item
 */
typedef struct bufferItem {
    /* the pointer to the next buffer
     * This is to be used by priority queue or a buffer manager.
     * Not to be used for a user of buffers
     */
    struct bufferItem* next;    /*!< Pointer to the next buffer */

    /* the size (payload) of the buffer : SIZE_0, SIZE_1, SIZE_2
     * in free buf pool, all size field are set to 0x00
     * when allocated, it will be set to the actual size (SIZE_0, SIZE_1, SIZE_2)
     * when deallocated, it will be set back to 0x00
     * we can use this to check whether a buf ptr is in free buf pool
     */
    u32 sizeIdx;                 /*!< Size of the buffer */

    /* In memory allocation, additional bytes are followed.
     * For example, if the we use SIZE_0(=64), (63 + AUX_LEN) bytes come after data[0],
     * in the actual allocation, the size of the buffer is forced to be in a multiple of 4 bytes
     * (refer to bufm_getBufferSize())
     */
    u8 data[1];                 /*!< Additional bytes are followed */
} bufferItem_t;

/**  @} end of group bufm_Public_Type */


/** @defgroup bufm_Public_Function Buff Management API
 *  @{
 */

 /**
  * @brief       Reset the buffer management module
  *
  * @param       None
  *
  * @return      None
  */
void bufm_reset(void);

 /**
  * @brief       Initialize the buffer management module
  *
  * @param       None
  *
  * @return      None
  */
void bufm_init(void);

 /**
  * @brief       Allocate an available buffer according to the requested size
  *              The allocated buffer will have only three kind of size, defined 
  *              in bufm_Public_Constant
  *
  * @param       size - The requested size
  *
  * @return      Pointer to an allocated buffer, the size of the buffer should be 
  *              defined in bufm_Public_Constant.
  */
u8* bufm_allocate(u16 size);


 /**
  * @brief       Return a previously allocated buffer to a free-buffer Queue 
  *
  * @param       dataPtr - the pointer to free
  *
  * @return      ERR_NONE: Success <BR>
  *              Other error code defined in @ref ERROR_MODULE <BR>
  */
rst_t bufm_free(u8* dataPtr);

 /**
  * @brief       Get the header pointer of a buffer item  
  *
  * @param       pd - the pointer of a data, which is previously allocated
  *
  * @return      Pointer of bufferItem
  */
bufferItem_t* bufm_getHeadPtr(u8* pd);


/**  @} end of group bufm_Public_Function */

/**  @} end of group BUFF_MGMT */

/**  @} end of group TELINK_COMMON_MODULE */


