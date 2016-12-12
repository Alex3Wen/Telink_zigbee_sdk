/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: This header not used for build. Its meaning is to define groups for
generation of Internals documentation
*/

#ifndef ZB_DOC_ALL_H
#define ZB_DOC_ALL_H 1

/*! @defgroup ll Low level */
/*! @{ */
/**
   @defgroup init_api Stack initialization API
   @defgroup ZB_CONFIG Compile-time configuration parameters
   @defgroup base_types Base typedefs
   @defgroup buf Packet buffers pool
   @defgroup sched Scheduler
   @defgroup time Time
   @defgroup ZB_BASE Low level internals
   @defgroup ZB_OSIF_UNIX OS abstraction layer - Linux-specific
   @defgroup ZB_OSIF_8051 OS abstraction layer - 8051-specific
   @defgroup ZB_DEBUG Debug tools
   @defgroup ZB_TRACE Trace
*/
/*! @} */

/**
   @defgroup mac MAC
 */
/*! @{ */
/**
   @defgroup mac_api MAC API
   @defgroup ZB_MAC MAC internals
   @defgroup ZB_MAC_TRANSPORT MAC transport 
*/
/*! @} */

/**
   @defgroup nwk NWK
 */
/*! @{ */
/**
   @defgroup nwk_api NWK functions visible to applications
   @defgroup nwk_ib NWK Informational Base
   @defgroup ZB_NWK_ADDR NWK Address
   @defgroup ZB_NWK NWK internals
*/
/*! @} */


/**
   @defgroup aps APS
 */
/*! @{ */
/**
   @defgroup aps_api APS functions visible to applications
   @defgroup aps_ib APS Informational Base
   @defgroup ZB_APS APS internals
*/
/*! @} */

/**
   @defgroup zdo ZDO
 */
/*! @{ */
/**
   @defgroup zdo_init ZDO init
   @defgroup zdo_ib ZDO Informational Base
   @defgroup zdo_base ZDO base constants and definitions
   @defgroup zdo_disc ZDO discovery services
   @defgroup zdo_mgmt ZDO management services
   @defgroup ZB_ZDO ZDO Internals
   @defgroup af_api AF functions visible to applications
   @defgroup ZB_AF AF Internals
   @defgroup ZB_ZCL ZCL Internals
*/
/*! @} */


/**
   @defgroup secur Security
 */
/*! @{ */
/**
   @defgroup secur_api Security subsystem API
   @defgroup ZB_SECUR Security internals
*/
/*! @} */

/*! defgroup ZB_TESTS Tests */

#endif /* ZB_DOC_ALL_H */
