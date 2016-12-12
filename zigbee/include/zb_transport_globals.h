/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: UART transport globals
*/

#ifndef ZB_TRANSPORT_GLOBALS_H
#define ZB_TRANSPORT_GLOBALS_H 1

/*! \cond internals_doc */
/*! \addtogroup ZB_MAC_TRANSPORT */
/*! @{ */

#ifdef ZB_TRANSPORT_TC32
#include "zb_transport_tc32.h"
#endif

#ifdef ZB_TRANSPORT_8051
#include "zb_transport_8051.h"
#endif

#ifdef ZB_TRANSPORT_LINUX_PIPES
#include "zb_transport_linux_pipes.h"
#endif

#ifdef ZB_TRANSPORT_LINUX_SPIDEV
#include "zb_transport_linux_spidev.h"
#endif

/*! @} */
/*! \endcond */

#endif /* ZB_TRANSPORT_GLOBALS_H */
