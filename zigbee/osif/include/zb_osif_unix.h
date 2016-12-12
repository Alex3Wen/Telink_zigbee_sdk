/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: OS and platform depenednt stuff for Unix platform
*/

#ifndef ZB_OSIF_UNIX_H
#define ZB_OSIF_UNIX_H 1

/*! \addtogroup ZB_OSIF_UNIX */
/*! @{ */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>


#define ZB_ABORT abort

#define ZB_SDCC_XDATA
#define ZB_SDCC_BANKED
#define ZB_KEIL_REENTRANT

/* Unix-specific trace */

extern FILE *g_trace_file;

void zb_trace_mutex_lock_unix();
void zb_trace_mutex_unlock_unix();

#define ZB_TRACE_LOCK zb_trace_mutex_lock_unix
#define ZB_TRACE_UNLOCK zb_trace_mutex_unlock_unix

#define ZB_OSIF_GLOBAL_LOCK()
#define ZB_OSIF_GLOBAL_UNLOCK()

#define ZB_XDATA
#define ZB_CODE
#define ZB_STOP_WATCHDOG()

#define DECLARE_SERIAL_INTER_HANDLER()
#define ZB_START_DEVICE()

/**
   Return random value
 */
zb_uint16_t zb_random();
#define ZB_RANDOM() zb_random()

/* use macros to be able to redefine */
#define ZB_MEMCPY memcpy
#define ZB_MEMMOVE memmove
#define ZB_MEMSET memset
#define ZB_MEMCMP memcmp

#define ZVUNUSED(v) (void)v


#define ZB_ENABLE_ALL_INTER()
#define ZB_DISABLE_ALL_INTER()

#define ZB_VOLATILE

#define ZB_BZERO(s,l) ZB_MEMSET((char*)(s), 0, (l))
#define ZB_BZERO2(s) ZB_BZERO(s, 2)

/*! @} */

#endif /* ZB_OSIF_UNIX_H */
