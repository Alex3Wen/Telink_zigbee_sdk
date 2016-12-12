#ifndef ZB_NWK_PIB_H
#define ZB_NWK_PIB_H 1

#include "zb_nwk_neighbor.h"
#include "zb_nwk.h"

/* List of buffers waiting to be duplicated  */
typedef struct zb_nwk_buf_alloc_wait_s
{
  zb_bitfield_t used:1;
  zb_bitfield_t wait:7; /* reason to be dup @see zb_nwk_wait_reason_t */
  zb_uint8_t    buf;    /* buffer to be duplicated */
}
zb_nwk_buf_alloc_wait_t;


/* Passive ack bit array size */
#define ZB_NWK_BRCST_PASSIVE_ACK_ARRAY_SIZE (ZB_NEIGHBOR_TABLE_SIZE / 8 + ((ZB_NEIGHBOR_TABLE_SIZE % 8) ? 1 : 0))
/* Broadcast retransmition info */
typedef struct zb_nwk_broadcast_retransmit_s
{
  zb_bitfield_t used:1; /*!< 1 if entry is used, 0 - otherwise */
  zb_bitfield_t wait_conf:1; /*!< Send  */
  zb_bitfield_t retries:6; /*!< Number of send retries */
  zb_uint8_t buf; /* buffer to be sent broadcast */
  zb_ushort_t neighbor_table_iterator; /*!< Next child to unicat broadcast
                                        * frame to */
  zb_time_t next_retransmit; /* next time when broadcast should be retransmitted
                              * */
  zb_uint16_t src_addr;
  zb_uint16_t dst_addr;
  zb_uint8_t seq_num;
  zb_uint8_t passive_ack[ZB_NWK_BRCST_PASSIVE_ACK_ARRAY_SIZE]; /* passive ack
                                                                * bit array */
}
zb_nwk_broadcast_retransmit_t;


/**
   Nwk state
*/
typedef enum zb_nlme_state_e
{
  ZB_NLME_STATE_IDLE,
  ZB_NLME_STATE_DISC,
  ZB_NLME_STATE_FORMATION_ED_SCAN,
  ZB_NLME_STATE_FORMATION_ACTIVE_SCAN,
  ZB_NLME_STATE_FORMATION,
  ZB_NLME_STATE_ROUTER,
  ZB_NLME_STATE_ED_SCAN,
  ZB_NLME_STATE_REJOIN,
  ZB_NLME_STATE_ORPHAN_SCAN,
  ZB_NLME_STATE_RESET,
  ZB_NLME_STATE_PANID_CONFLICT_RESOLUTION,
  ZB_NLME_STATE_ADDR_CONFLICT_RESOLUTION
} ZB_PACKED_STRUCT
zb_nlme_state_t;


/**
   NWK Neighbor relationship between neighbors
*/
enum zb_nwk_relationship_e
{
  ZB_NWK_RELATIONSHIP_PARENT                = 0x00,
  ZB_NWK_RELATIONSHIP_CHILD                 = 0x01,
  ZB_NWK_RELATIONSHIP_SIBLING               = 0x02,
  ZB_NWK_RELATIONSHIP_NONE_OF_THE_ABOVE     = 0x03,
  ZB_NWK_RELATIONSHIP_PREVIOUS_CHILD        = 0x04,
  ZB_NWK_RELATIONSHIP_UNAUTHENTICATED_CHILD = 0x05
};


/**
   NWK route state
*/
typedef enum zb_nwk_route_state_e
{
  ZB_NWK_ROUTE_STATE_ACTIVE,
  ZB_NWK_ROUTE_STATE_DISCOVERY_UNDERWAY,
  ZB_NWK_ROUTE_STATE_DISCOVERY_FAILED,
  ZB_NWK_ROUTE_STATE_DISCOVERY_INACTIVE,
  ZB_NWK_ROUTE_STATE_VALIDATION_UNDERWAY,
  ZB_NWK_ROUTE_STATE_NUM
} zb_nwk_route_state_t;

typedef struct zb_nwk_link_status_s
{
  zb_uint16_t nwk_addr;
  zb_uint8_t incoming_cost:3;
  zb_uint8_t reserved1:1;
  zb_uint8_t outgoing_cost:3;
  zb_uint8_t reserved2:1;
} ZB_PACKED_STRUCT
zb_nwk_link_status_t;

/* Broadcast transaction record */
typedef struct zb_nwk_btr_s
{
  zb_bitfield_t used:1;
  zb_bitfield_t expiration_time:7;
  zb_uint16_t   source_addr;
  zb_uint8_t    sequence_number;
} ZB_PACKED_STRUCT
zb_nwk_btr_t;


typedef enum zb_user_state_e
{
	ZB_NLME_IDLE,
	ZB_NLME_PERMIT_JOIN_REQ,
	ZB_NLME_SEND_DEV_ANN,
} ZB_PACKED_STRUCT
zb_user_state_t;
    
/**
   NWK routing
*/
typedef struct zb_nwk_routing_s
{
  zb_bitfield_t used:1; /*!< 1 if entry is used, 0 - otherwise */
  zb_bitfield_t status:3; /*!< The status of the route, @see zb_nwk_route_state_t */
  zb_bitfield_t no_route_cache:1; /*!< Dest does not store source routes */
  zb_bitfield_t many_to_one:1; /*!< Dest is the concentrator and many-to-one
                                * request was used  */
  zb_bitfield_t route_record_required:1; /*!< Route record command frame should
                                          * be sent to the dest prior to the
                                          * next data packet */
  zb_bitfield_t group_id_flag:1; /*!< Indicates that dest_addr is a Group ID */
  zb_uint16_t dest_addr; /*!< 16-bit network address or Group ID of this route */
  zb_uint16_t next_hop_addr; /*!< The 16 bit network address of the next
                                 * hop on the way to the destination */
} ZB_PACKED_STRUCT
zb_nwk_routing_t;

/**
   NWK route discovery
*/
typedef struct zb_nwk_route_discovery_s
{
  zb_bitfield_t used:1; /*!< 1 if entry is used, 0 - otherwise   */
  zb_uint8_t request_id; /*!< Sequence number for a route request */
  zb_uint16_t source_addr; /*!< 16-bit network address of the route
                            * requests initiator */
  zb_uint16_t sender_addr; /*!< 16-bit network address of the device that
                            * has sent the most recent lowest cost route
                            * request */
  zb_uint16_t dest_addr; /*!< 16-bit network destination address of this
                          * request */
  zb_uint8_t forward_cost; /*!< Path cost from the source of the route request
                            * to the current device */
  zb_uint8_t residual_cost; /*!< Path cost from the current to the destination
                             * device */
  zb_uint16_t expiration_time; /*!< Countdown timer indicating when route
                                * discovery expires */
} ZB_PACKED_STRUCT
zb_nwk_route_discovery_t;

/**
   NWK pending list element
*/
typedef struct zb_nwk_pend_s
{
  zb_bitfield_t used:1; /*!< 1 if entry is used, 0 - otherwise */
  zb_buf_t *buf; /*!< buffer waiting for route discovery */
  zb_uint8_t handle; /*!< nsdu handle */
  zb_uint16_t dest_addr; /*!< 16-bit network destination address of this
                          * request */
  zb_bitfield_t expiry:6; /*!< expiration time */
  zb_bitfield_t waiting_buf:1; /*!< if pending buffer waits new buffer to
                                 * start route discovery */

} ZB_PACKED_STRUCT
zb_nwk_pend_t;


/**
   NWK address allocation method.
*/
typedef enum zb_nwk_address_alloc_method_e
{
  ZB_NWK_ADDRESS_ALLOC_METHOD_DISTRIBUTED,
  ZB_NWK_ADDRESS_ALLOC_METHOD_RESERVER,
  ZB_NWK_ADDRESS_ALLOC_METHOD_STOCHASTIC
} ZB_PACKED_STRUCT
zb_nwk_address_alloc_method_t;


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


typedef struct zb_nwk_route_record_s
{
  zb_uint16_t nwk_addr;
  zb_uint8_t relay_cnt;
  zb_uint8_t *relay_path;
} ZB_PACKED_STRUCT
zb_nwk_route_record_t;


/**
   This is NWK NIB residental in memory.
   It is not clear yet when it will be save to nvram and when read.
*/
typedef struct zb_nib_s
{
  zb_uint8_t     sequence_number;   /*!< A sequence number used to identify
                                     * outgoing frames */
  zb_uint16_t    passive_ack_timeout; /*!< Maximum time duration allowed for
                                       * the parent and all child to retransmit
                                       * a broadcast message */

  zb_uint8_t     max_broadcast_retries; /*!< The maximum number of retries allowed after a
                                          broadcast transmission failure. */
  zb_ext_pan_id_t  extended_pan_id; /*!< The extended PAN identifier for the PAN
                                   * of which the device is a member */
  zb_uint16_t      short_pan_id; /*!< short PAN id  */

  zb_uint8_t     device_type;   /*!< Current device role, @see zb_nwk_device_type_t */
  zb_uint8_t     update_id;     /*!< nwkUpdateId - The value identifying a
                                  snapshot of the network
                                  settings with which this
                                  node is operating with. */
  zb_nwk_route_record_t route_record_table[ZB_NWK_ROUTE_RECORD_TABLE_SIZE];                               
#if defined ZB_NWK_MESH_ROUTING && defined ZB_ROUTER_ROLE
//#if 1
  zb_nwk_routing_t routing_table[ZB_NWK_ROUTING_TABLE_SIZE]; /*!< Routing
                                                                    * table */
  zb_uint8_t routing_table_cnt; /*!< Routing table used elements */

  zb_nwk_route_discovery_t route_disc_table[ZB_NWK_ROUTE_DISCOVERY_TABLE_SIZE]; /*!< Route discovery table */
  zb_uint8_t route_disc_table_cnt; /*!< Discovery table used elements */

  zb_uint8_t rreq_id; /*!< ID, increments each new route discovery procedure */
  zb_nwk_pend_t pending_table[ZB_NWK_PENDING_TABLE_SIZE]; /*!< store pending
                                                           * buffers while
                                                           * route discovery is
                                                           * in progress */
  zb_uint8_t pending_table_cnt; /*!< number of used elements inside pending
                                 * buffer */
  zb_uint16_t aps_rreq_addr; /*!< APS layer call us to find path to this
                              * address */
  zb_uint32_t nwk_broadcast_delivery_time;
  zb_uint8_t nwk_capability_info;
#endif /* ZB_NWK_MESH_ROUTING && ZB_ROUTER_ROLE */

  zb_uint8_t     max_depth; /*!< The depth a device can have */
  zb_uint8_t     max_children; /*!< The number of children a device is allowed
                                * to have */

#if defined ZB_NWK_DISTRIBUTED_ADDRESS_ASSIGN && defined ZB_ROUTER_ROLE
  zb_uint8_t     max_routers; /*!< The number of routers any one device is
                               * allowed to have as children. */
  zb_uint16_t    cskip; /*!< Cskip value - size of the address sub-block beeing
                         * distributed */
  zb_uint8_t     depth; /*!< current node depth */
#endif

  zb_bitfield_t use_tree_routing:1; /*!< if device is able to use tree routing */

  zb_bitfield_t addr_alloc:3; /*!< Address assign method @see
                               * zb_nwk_address_alloc_method_t */
  zb_bitfield_t nwk_sys_link:1;
  zb_bitfield_t nwk_use_tree_routing:1;

  zb_bitfield_t nwk_use_multicast:1;

  zb_bitfield_t nwk_is_concentrator:1;
  zb_bitfield_t reserved:1;

#ifdef ZB_SECURITY
  zb_bitfield_t           security_level:4; /*!< The security level for
                                            outgoing and incoming
                                            NWK frames; the
                                            allowable security level
                                            identifiers are presented
                                            in Table 4.38.
                                            For ZB 2007 (Standard security only)
                                            only values 0 and 5 are possible.
                                            Or, seems, only value 5 is possible?
                                            */
  /* all_fresh is always 0 for Standard security */
  zb_bitfield_t           secure_all_frames:1;

  zb_bitfield_t           active_secur_material_i:2; /*!< index in
                                                      * secur_material_set for
                                                      * keys with
                                                      * key_seq_number == active_key_seq_number  */

  zb_secur_material_set_t secur_material_set[ZB_SECUR_N_SECUR_MATERIAL]; /*!< Set of network security
                                                                  material descriptors
                                                                  capable of maintaining
                                                                  an active and alternate
                                                                  network key.  */
  zb_uint8_t              active_key_seq_number; /*!< The sequence number of
                                                   the active network key in
                                                   nwkSecurityMaterialSet.  */
  zb_uint32_t             outgoing_frame_counter; /*!< OutgoingFrameCounter
                                                   * stored here (not in the
                                                   * secured material).
                                                   * Rationale: will never use
                                                   * "old" key - why store more
                                                   * then 1 counter?
                                                   */
  zb_uint32_t             prev_outgoing_frame_counter;
#endif
  zb_uint16_t nwk_manager_addr; /*!< The address of the designated
                                 * network channel manager function. */
  zb_uint8_t nwk_max_source_route;     

  zb_uint16_t nwk_transaction_persistence_time;

  zb_uint16_t nwk_network_address;

  zb_uint8_t nwk_stack_profile;
  
  zb_uint8_t nwk_concentrator_radius;

  zb_uint8_t nwk_concentrator_discovery_time;

  zb_uint8_t nwk_link_status_period;

  zb_uint8_t nwk_router_age_limit;

  zb_uint8_t nwk_neighbor_age_limit;

  zb_uint16_t nwk_tx_total; /*!< A count of unicast transmissions made
                             * by the NWK layer on this device */
  zb_uint16_t nwk_tx_fail; /*!< A count of failed transmissions */

  zb_bitfield_t nwk_unique_addr:1;
  zb_bitfield_t nwk_time_stamp:1;
  zb_bitfield_t nwk_leave_request_allowed:1;

  zb_bitfield_t nwk_report_constant_cost:1; /*!< If this is set to 0, the NWK
                                             * layer shall calculate link cost
                                             * from all neighbor nodes using the
                                             * LQI values reported by the MAC
                                             * layer; otherwise, it shall report
                                             * a constant value. */
} zb_nib_t;


/**
   Place to store values between multiply operations
*/
typedef struct zb_nwk_handle_s
{
  zb_nlme_state_t state; /*!< Current network subsystem state */

  zb_address_ieee_ref_t parent; /*!< parent address (valid if we ar not ZC and joined)  */

  union saved_req_u
  {
    zb_nlme_network_formation_request_t formation;
    zb_nlme_join_request_t join;
  } saved_req;

  union tmp_u
  {
    struct join_tmp_s
    {
      zb_ext_neighbor_tbl_ent_t *parent;
    } join;
    struct rejoin_tmp_s
    {
      zb_ext_pan_id_t extended_pan_id;
      zb_mac_capability_info_t capability_information;
      zb_ext_neighbor_tbl_ent_t *parent;
    } rejoin;
    struct formation_s
    {
      zb_uint8_t energy_detect[ ZB_MAC_SUPPORTED_CHANNELS ]; /*!< Channel energy scan
                                                              * result, used during formation */
      zb_uint8_t channel_pan_count[ZB_MAC_SUPPORTED_CHANNELS];
      zb_uint8_t panid_handled_bm[ZB_PANID_TABLE_SIZE / 8 + 1];
    } formation;
  } tmp;

  zb_uint8_t  status_ind; /* Used to report NWK status indication */
  zb_uint16_t status_addr; /* Used to report NWK status indication */
  zb_uint16_t status_ind_addr; /* Used to report NWK status indication */

  zb_uint8_t permit_join; /*!< True if permit join is in progress */
  zb_uint8_t joined;      /*!< Non-zero if we are joined into the network */

  zb_uint8_t router_started; /*!< True if we are a router and we are
                              * started */
  zb_uint8_t is_tc;             /*!< true if we are Trust Center  */

  /* FIXME: next values are unnecessary for ED with rx_on_when_idle == 0 */
  zb_nwk_btr_t btt[ZB_NWK_BTR_TABLE_SIZE]; /*!< Broadcast transaction
                                            * table see 3.6.5 */
  zb_uint8_t btt_cnt;
  /* end FIXME: */

#ifdef ZB_ROUTER_ROLE
  zb_nwk_broadcast_retransmit_t brrt[ZB_NWK_BRR_TABLE_SIZE]; /* Broadcast
                                                              * retransmition
                                                              table */
  zb_uint8_t brrt_cnt;
#endif

  zb_nwk_buf_alloc_wait_t wait_alloc[ZB_NWK_WAIT_ALLOC_TABLE_SIZE]; /* list of
                                                                     * buffers
                                                                     * waitng to
                                                                     * be
                                                                     * duplicated */
  zb_uint8_t wait_alloc_cnt;

  zb_uint16_t rejoin_req_table[ZB_NWK_REJOIN_REQUEST_TABLE_SIZE];
  zb_uint8_t  rejoin_req_table_cnt;


  /* For PANID conflict resolution */
  zb_uint16_t known_panids[ZB_PANID_TABLE_SIZE];
  zb_uint16_t new_panid;
  zb_uint8_t  panid_conflict;
  /* For indicating we're joined to PRO as end device */
  zb_uint8_t joined_pro;
  zb_user_state_t user_state;
  zb_uint8_t nwk_flags;
} ZB_PACKED_STRUCT zb_nwk_handle_t;


#endif

