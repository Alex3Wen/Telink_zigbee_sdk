/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: NWK subsystem globals
*/

#ifndef ZB_NWK_GLOBALS_H
#define ZB_NWK_GLOBALS_H 1

#include "zb_mac.h"
#include "zb_nwk_neighbor.h"
#include "zb_nwk.h"

/*! \cond internals_doc */
/*! \addtogroup ZB_NWK */
/*! @{ */


#define LINK_STATUS_JITTER_MASK 0x007F   


#define ZB_NWK_SENDING_NWK_STATUS_MASK    0x1
//#define ZB_NWK_IO_IN_USE_MASK     0x2
//#define ZB_NWK_BEACON_REQ_MASK    0x4
//#define ZB_NWK_SCAN_TIMEOUT_MASK  0x8
//#define ZB_NWK_POLL_REQUEST_MASK  0x10
//#define ZB_NWK_TRANS_SLP_MASK     0x20
//#define ZB_NWK_SECURITY_PROCESS   0x40
//#define ZB_NWK_ACK_WITH_PENDING   0x80


#define ZB_NWK_SET_SENDING_NWK_STATUS()  (ZG->nwk.handle.nwk_flags |= ZB_NWK_SENDING_NWK_STATUS_MASK)
#define ZB_NWK_GET_SENDING_NWK_STATUS()  (ZG->nwk.handle.nwk_flags & ZB_NWK_SENDING_NWK_STATUS_MASK)
#define ZB_NWK_CLEAR_SENDING_NWK_STATUS()  (ZG->nwk.handle.nwk_flags &= ~ZB_NWK_SENDING_NWK_STATUS_MASK)


/**
   Network device type
*/
typedef enum zb_nwk_device_type_e
{
  ZB_NWK_DEVICE_TYPE_ED,
  ZB_NWK_DEVICE_TYPE_ROUTER,
  ZB_NWK_DEVICE_TYPE_COORDINATOR,
  ZB_NWK_DEVICE_TYPE_NONE
} ZB_PACKED_STRUCT
zb_nwk_device_type_t;


/* Wait for buffer allocation reasons */
typedef enum zb_nwk_wait_reason_e
{
  ZB_NWK_WAIT_REASON_IND_AND_RETRANSMIT, /* waitong for a new buffer to call
                                          * indicate data and retransmit it */
  ZB_NWK_WAIT_NUM
} ZB_PACKED_STRUCT
zb_nwk_wait_reason_t;


#if 0
/**
   NWK route request entry
*/
typedef struct zb_nwk_route_request_s
{
  zb_bitfield_t used:1; /*!< 1 if entry is used, 0 - otherwise */
  zb_uint8_t retries; /*!< Number of retries for the route request */
  zb_uint8_t radius; /*!< Radius for the route request */
  zb_uint16_t originator; /*!< Originator of the route request */
  zb_nwk_cmd_rreq_t cmd; /*!< Command data for the route request */
} ZB_PACKED_STRUCT
zb_nwk_rreq_t;
#endif


typedef struct zb_leave_pending_list_s
{
  zb_uint8_t             used;
  zb_uint8_t             buf_ref;
  zb_uint8_t             tsn;
  zb_uint16_t            src_addr;
} ZB_PACKED_STRUCT zb_leave_pending_list_t;


typedef struct zb_leave_ind_prnt_s
{
  zb_address_ieee_ref_t addr_ref;
  zb_uint8_t rejoin;
} zb_leave_ind_prnt_t;

/**
  leave context
*/
typedef struct zb_leave_context_s
{
  zb_leave_pending_list_t pending_list[ZB_ZDO_PENDING_LEAVE_SIZE];
  zb_uint8_t pending_list_size;
  zb_uint8_t rejoin_after_leave;
  zb_uint8_t leave_after_mgmt_leave_rsp_conf;
  zb_leave_ind_prnt_t leave_ind_prnt;
} zb_leave_context_t;


#ifdef ZB_SECURITY
/**
   Part of the secured material stored in array.

   Other secured material components stored elsewhere:
   OutgoingFrameCounter - NIB
   IncomingFrameCounterSet - neighbor table
 */
typedef struct zb_secur_material_set_t
{
  zb_uint8_t          key[ZB_CCM_KEY_SIZE];
  zb_uint8_t          key_seq_number;
} zb_secur_material_set_t;
#endif


typedef struct zb_nwk_ctx_s
{
  zb_leave_context_t leave_context; /* leave context */
} zb_nwk_ctx_t;

/* NWK Broadcast delivery time See 3.5.2.1 */
#if 0
/* according to this formula we get to large value for
 * BROADCAST_DELIVERY_TIME - 192 sec, lets decrease it down to 30 */
#define ZB_NWK_BROADCAST_DELIVERY_TIME() ( 2*ZG->nwk.nib.max_depth*(/*0.05 +*/ ZB_NWK_MAX_BROADCAST_JITTER/2 \
                                                                    + ZG->nwk.nib.passive_ack_timeout*ZB_MWK_INITIAL_RREQ_RETRIES/1000) )
#endif
#define ZB_NWK_BROADCAST_DELIVERY_TIME() 3//9

zb_void_t zb_nwk_set_device_type(zb_nwk_device_type_t device_type);

#define ZB_NWK() ZG->nwk.nib

#define ZB_SET_USER_STATE(_state_)    (ZG->nwk.handle.user_state = _state_)
#define ZB_GET_USER_STATE()    (ZG->nwk.handle.user_state)

#define ZB_NWK_GET_RREQ_ID() (++ZB_NWK().rreq_id)

/*! @} */
/*! \endcond */

#endif /* ZB_NWK_GLOBALS_H */
