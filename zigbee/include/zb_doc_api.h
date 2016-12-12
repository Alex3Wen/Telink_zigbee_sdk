/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: This header not used for build. Its meaning is to define groups for
generation of API reference document.
*/

#ifndef ZB_DOC_API_H
#define ZB_DOC_API_H 1

/**
  @mainpage ZigBee Stack API

  This document describes ZigBee stack API.

  \see init_api
  \see zdo_init
  \see zdo_api
  \see af_api
  \see aps_api
  \see nwk_api
  \see mac_api
  \see secur_api

  \see base_types
  \see buf
  \see sched
  \see time
  \see ZB_CONFIG

 */
/**
   @defgroup init_api Stack initialization API
*/
/*! @{ */
/**
   @defgroup zdo_init ZDO init and main() structure
*/
/*! @} */
/**
   @defgroup zdo_api ZDO API
 */
/*! @{ */
/**
   @defgroup zdo_ib ZDO Informational Base
   @defgroup zdo_base ZDO base constants and definitions
   @defgroup zdo_disc ZDO discovery services
   @defgroup zdo_mgmt ZDO management services
*/
/*! @} */

/**
   @defgroup af_api AF functions visible to applications
   @defgroup aps_api APS functions visible to applications
*/
/*! @{ */
/*!   @defgroup aps_ib APS Informational Base */
/*! @} */

/*! @defgroup nwk_api NWK functions visible to applications */
/*! @{ */
/*!   @defgroup nwk_ib NWK Informational Base */
/*! @} */

/**
   @defgroup mac_api MAC API
   @defgroup secur_api Security subsystem API
*/

/*! @defgroup ll Low level API */
/*! @{ */
/**
   @defgroup ZB_CONFIG Compile-time configuration parameters
   @defgroup base_types Base typedefs
   @defgroup buf Packet buffers pool
   @defgroup sched Scheduler
   @defgroup time Time
   @defgroup ZB_TRACE Debug trace
*/
/*! @} */

#endif /* ZB_DOC_API_H */
