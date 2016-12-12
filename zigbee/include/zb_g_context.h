/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Global context definition
*/

#ifndef ZB_G_CONTEXT_H
#define ZB_G_CONTEXT_H 1

#include "../osif/include/zb_osif.h"

/*! \cond internals_doc */
/*! \addtogroup ZB_BASE */
/*! @{ */

/**
   \par Define 'global context' - comon global data structure.
   Vladimir got strange problems in Keil with accessing global variables
   implemented in another modules.
   Also, wants to easiely track memory usage.
   So, unite it all into global context.

   Initially suppose global context will be defined here and implemented in the
   single .c module and passed to all functions by pointer.
   To be able to exclude such pointer pass let's define global context access by
   a macro. The macro can be easiely substituted by the global variable access
   or parameter access.

   Globals can be accessed using ZG macro in constructions like ZG->foo.

   Some subsystems has its own structures in the globals (for example, APS
   globals). It can be accesses by special macros, like APSG->bar.
 */
struct zb_globals_s;
typedef struct zb_globals_s zb_globals_t;

struct zb_intr_globals_s;
typedef struct zb_intr_globals_s zb_intr_globals_t;

struct zb_ctrl_globals_s;
typedef struct zb_ctrl_globals_s zb_ctrl_globals_t;


extern zb_globals_t g_zb;
extern zb_intr_globals_t g_izb;
extern zb_ctrl_globals_t g_ctrl;
/**
   Macro to access globals
 */
/* Hope compiler can optimize &g_zb-> to g_zb. */
#define ZG (&g_zb)
#define ZCTRL (&g_ctrl)
#define ZIG (&g_izb)


/*
  Per-subsystem globals files are named like zb_xxx_globals.h and included here.
 */
#include "zb_scheduler.h"

#include "zb_globals.h"
#include "zb_mac_globals.h"
#include "zb_nwk_globals.h"
#include "zb_aps_globals.h"
#include "zb_af_globals.h"
#include "zb_zdo_globals.h"
#include "zb_zcl_globals.h"
#include "zb_time.h"
#include "zb_ubec24xx.h" /* TODO: configure this include depending
                          * on transceiver */
#include "zb_transport_tc32.h"
#ifdef ZB_CC25xx
#include "zb_cc25xx.h"
#endif

/**
   Global data area for data to be accessed from interrupt handlers
 */
struct zb_intr_globals_s
{
  zb_io_ctx_t             ioctx;
  zb_timer_t              time;
  zb_transceiver_ctx_t    transceiver;
};

/**
   Global data area data for zigbee control
 */
struct zb_ctrl_globals_s
{
    zb_mac_ctx_t            mac_ctx;
    zb_nwk_ctx_t            nwk_ctx;
    zb_aps_ctx_t            aps_ctx;
    zb_zdo_globals_t        zdo_ctx;
    zb_buf_pool_t           bpool;
    zb_sched_globals_t      sched;
};

#define ZB_IOCTX() g_izb.ioctx
#define ZB_TIMER_CTX() g_izb.time
#define TRANS_CTX() (g_izb.transceiver)
#define SER_CTX() ZB_IOCTX().serial_ctx
#define SPI_CTX() ZB_IOCTX().spi_ctx

#define ZB_MAC_STATE()   (g_ctrl.mac_ctx.state)

/*! @} */
/*! \endcond */

#endif /* ZB_G_CONTEXT_H */
