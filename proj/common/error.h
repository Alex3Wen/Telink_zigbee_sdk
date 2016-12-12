/**************************************************************************************************
  Filename:       error.h
  Revised:        $Date: 2013-05-27 $

  Description:    Definition of Error code.
**************************************************************************************************/
#pragma once

/** @addtogroup  TELINK_COMMON_MODULE TELINK Common Module
 *  @{
 */

/** @addtogroup  ERROR_MODULE Error Code
 *  @{
 */
 
/** @defgroup Error_Public_Constant Error Code Base
 *  @{
 */

/**
 *  @brief No error
 */
#define ERR_NONE            0x00000000

/**
 *  @brief Error code base of system
 */
#define ERR_SYS_BASE        0x00001000

/**
 *  @brief Error code base of buffer management
 */
#define ERR_BUF_BASE        0x00010000

/**
 *  @brief Error code base of software timer
 */
#define ERR_SOFT_TIMER_BASE 0x00020000

/**
 *  @brief Error code base of priority queue
 */
#define ERR_PRIQ_BASE       0x00030000

/**
 *  @brief Error code base of flash
 */
#define ERR_FLASH_BASE      0x00040000

/**
 *  @brief Error code base of hardware timer
 */
#define ERR_TIMER_BASE      0x00050000

/**
 *  @brief Error code base of OS task
 */
#define ERR_EV_TASK_BASE    0x00060000

/**
 *  @brief Error code base of AES module
 */
#define ERR_AES_BASE        0x00070000

/**
 *  @brief Error code base of NV Operation
 */
#define ERR_NV_BASE         0x00080000


/**
 *  @brief Error code base of USB CDC
 */
#define ERR_USB_BASE        0x00090000


/**
 *  @brief Error code base of PHY
 */
#define ERR_PHY_BASE        0x00100000

/**
 *  @brief Error code base of MAC
 */
#define ERR_MAC_BASE        0x00200000

/**
 *  @brief Error code base of NWK
 */
#define ERR_NWK_BASE        0x00300000

/**
 *  @brief Error code base of Profile
 */
#define ERR_PROFILE_BASE    0x00400000

/**
 *  @brief Error code base of ZCL
 */
#define ERR_ZCL_BASE        0x00500000


 /** @addtogroup common_error_code Error Code
 * Definition for Error Code
 * @{
 */

enum {
    ERR_SUCC = ERR_NONE,                        /**< ERR_NONE and ERR_SUCC both means success */

    ERR_SYS_START = ERR_SYS_BASE,               /**< Error code for system module */
    ERR_SYS_END,

    ERR_BUF_START = ERR_BUF_BASE,
    ERR_BUF_INVALID_PARAM,                      /**< Invalid buffer parameter */
    ERR_BUF_DUPLICATE_FREE,                     /**< The buffer is released for more than once */
    ERR_BUF_END,

    ERR_PRIQ_START = ERR_PRIQ_BASE,
    ERR_PRIQ_INVALID_CONTAINER,                 /**< Invalid container for priority queue */
    ERR_PRIQ_INVALID_ELEM,                      /**< Invalid element for priority queue */
    ERR_PRIQ_EMPTY,                             /**< Priority queue is empty */
    ERR_PRIQ_NOT_FOUND,                         /**< Priority queue is not found */
    ERR_PRIQ_OVERFLOW,                          /**< Priority queue is overflowed */
    ERR_PRIQ_END,


    ERR_TIMER_START = ERR_TIMER_BASE,
    ERR_TIMER_IS_RUNNING,                       /**< The requested timer is still running */
    ERR_TIMER_END,

    ERR_TASK_START = ERR_EV_TASK_BASE,
    ERR_TASK_OVERLAP,                           /**< The task is overlap */
    ERR_TASK_END,
   
    ERR_NV_INVALID_MODULS = ERR_NV_BASE,
    ERR_NV_INVALID_ID,
    ERR_NV_ITEM_NOT_FOUND,
    ERR_NV_NOT_ENOUGH_SAPCE,
    ERR_NV_ITEM_LEN_NOT_MATCH,
    ERR_NV_CHECK_SUM_ERROR,



    ERR_PHY_START = ERR_PHY_BASE,
    ERR_PHY_END,

    ERR_MAC_START = ERR_MAC_BASE,
    ERR_MAC_END,

    ERR_NWK_START = ERR_NWK_BASE,

    ERR_AES_DECRYPT_FAIL = ERR_AES_BASE,
    ERR_NWK_END,

	ERR_USB_START = ERR_USB_BASE,
	ERR_USB_BUSY,
	ERR_USB_END,

    ERR_PROFILE_START = ERR_PROFILE_BASE,
    ERR_PROFILE_INVALID_STATE,                   /**< Invalid state for the request to profile */
    ERR_PROFILE_INVALID_DEV_TYPE,                /**< Invalid device type for the request to profile */
    ERR_PROFILE_END,

	ERR_ZCL_START = ERR_ZCL_BASE,
	ERR_ZCL_CLUSTER_TBL_FULL,
	ERR_ZCL_ATTR_NOT_FOUND,
	ERR_ZCL_END,
};
 /**  @} end of group common_error_code */

/**  @} end of group Error_Public_Constant */

/**  @} end of group ERROR_MODULE */

/**  @} end of group TELINK_COMMON_MODULE */
