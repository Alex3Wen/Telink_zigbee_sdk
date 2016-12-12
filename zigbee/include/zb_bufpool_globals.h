/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Buffer pool globals declaration
*/

#ifndef ZB_BUFPOOL_GLOBALS_H
#define ZB_BUFPOOL_GLOBALS_H 1

/*! \cond internals_doc */
/*! \addtogroup ZB_BASE */
/*! @{ */

#include "zb_bufpool.h"
#include "zb_ringbuffer.h"

typedef struct
{
  zb_callback_t callback;
  zb_ret_t      ret_code;
} zb_buf_pool_delayed_t;

ZB_RING_BUFFER_DECLARE( zb_ring_buf_pool, zb_buf_pool_delayed_t, ZB_SCHEDULER_Q_SIZE );

typedef struct zb_buf_pool_s
{
  zb_ring_buf_pool_t delayed_allocs;
  zb_buf_s_t pool[ZB_IOBUF_POOL_SIZE];
  zb_buf_t ZB_XDATA *head;
  zb_uint8_t bufs_allocated[2];
  
} zb_buf_pool_t;

/*! @} */
/*! \endcond */

#endif /* ZB_BUFPOOL_GLOBALS_H */
