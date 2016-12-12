/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: MAC and trace transport API
*/

#ifndef MAC_TRANSPORT_H
#define MAC_TRANSPORT_H 1

#include "zb_bufpool.h"

/*! \cond internals_doc */
/*! \addtogroup ZB_MAC_TRANSPORT */
/*! @{ */


/**
   \par Trunsport protocol description.

   This protocol used only under 8051 sim. Data, dump and trace goes throught
   one pipe. Each packet has a header. Header consists of a length byte and a
   type byte.
*/

/**
   Packet types.

   This enum describes possible packet types to be transfered throught pipes.
 */
typedef enum zb_mac_transport_type_e
{
  ZB_MAC_TRANSPORT_TYPE_DATA  = 0x00, /*!< Data packet type */
  ZB_MAC_TRANSPORT_TYPE_DUMP  = 0x01, /*!< Dump packet type */
  ZB_MAC_TRANSPORT_TYPE_TRACE = 0x02, /*!< Trace packet type */

  ZB_MAC_TRANSPORT_TYPE_NUM
} ZB_PACKED_STRUCT
zb_mac_transport_type_t;


/**
   Packet header.

   Used for outgoing packets sent via pipe to the pipe_data_router or directly
   to ns-3.
   Each packet to pipe has this header.
   Type field used to multiplex zb traffix, trace and dump via same UART stream.

   Note that packets received from ns-3 or pipe_data_router has only leading
   length and no type field.
 */
typedef struct zb_mac_transport_hdr_s
{
  zb_uint8_t len;  /*!< Packet length, including hdr */
  zb_uint8_t type; /*!< Packet type, @see zb_mac_transport_type_t */
  zb_uint16_t time;             /* time label */
} ZB_PACKED_STRUCT
zb_mac_transport_hdr_t;

#define ZB_NO_IO            0
#define ZB_RECV_FINISHED    2
#define ZB_SEND_FINISHED    3

#define ZB_GET_SEND_STATUS() (ZB_IOCTX().send_finished + 0)
#define ZB_SET_SEND_STATUS(status) (ZB_IOCTX().send_finished = (status))

#define ZB_GET_RECV_STATUS() (ZB_IOCTX().recv_finished + 0)
#define ZB_SET_RECV_STATUS(status) (ZB_IOCTX().recv_finished = (status))

#define ZB_GET_PENDING_BYTES_COUNT(zg) 9 /* TODO: return correct byte count */

#ifndef ZB8051
/**
   8051: Initialize in/out ring buffers
   Unix: Initialize MAC transport for unix.

   @param rpipe_path - path to read pipe. Incoming pipe from the NS. Used only
   on unix.
   @param wpipe_path - path to write pipe. Output pipe to the NS. Used only
   on unix.

   @return nothing.
 */
#ifndef ZB_TRANSPORT_LINUX_SPIDEV
void zb_mac_transport_init() ;
#else
void zb_mac_transport_init() ;
#endif
#else
void zb_mac_transport_init() ;
#endif

/**
   Put zb_buf_t with adapter data to output queue.

   On 8051 this buffer goes to SPI output queue.
   On unix to output buffer.

   @param buf    - output buffer.

   @return nothing.
 */
void zb_mac_transport_put_data(zb_buf_t *buf);


/**
   Initiates receive operation: sets buffer for receive and required
   bytes number to read

   @param buf           - pointer on receive buffer
   @param bytes_to_recv - number of bytes to read

   @return nothing
 */
void zb_mac_transport_start_recv(zb_buf_t *buf, zb_short_t bytes_to_recv);


#if defined ZB_TRAFFIC_DUMP_ON && !defined ZB_TRANSPORT_OWN_TRAFFIC_DUMP_ON
void zb_mac_traffic_dump(zb_buf_t *buf, zb_bool_t is_w) ;
#define ZB_DUMP_INCOMING_DATA(buf) zb_mac_traffic_dump((buf), ZB_FALSE)
#define ZB_DUMP_OUTGOING_DATA(buf) zb_mac_traffic_dump((buf), ZB_TRUE)
#else
#define ZB_DUMP_INCOMING_DATA(buf) while(0) { ZVUNUSED(buf); }
#define ZB_DUMP_OUTGOING_DATA(buf) while(0) { ZVUNUSED(buf); }
#endif


/*! @} */
/*! \endcond */

#endif /* MAC_TRANSPORT_H */
