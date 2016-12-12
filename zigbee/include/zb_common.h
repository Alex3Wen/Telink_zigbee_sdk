/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Common include file for ZigBee
*/

#ifndef ZB_COMMON_H
#define ZB_COMMON_H 1

#include "zb_config.h"
#include "zb_types.h"
#include "zb_errors.h"
#include "zb_debug.h"
#include "zb_g_context.h"

#include "../osif/include/zb_osif.h"
#include "zb_trace.h"

/*! \addtogroup init_api */
/*! @{ */

void zb_init();


void zb_handle_parms_before_start();

/*! @} */


/*! \internal \addtogroup ZB_BASE */
/*! @{ */

/**
   Load Informational Bases from NVRAM or file
 */
rst_t zb_ib_load(void);


/**
   Set Informational Bases refaults.

   @param rx_pipe - rx pipe name (for Unix) or node number (for ns build
                            in 8051 simulator)
 */
void zb_ib_set_defaults(void) ;


/**
   Save Informational Bases to NVRAM or other persistent storage
 */
void zb_pib_save(void) ;
void zb_tab_save(void) ;
void zb_ib_reset(void) ;
/*! @} */

#endif /* ZB_COMMON_H */
