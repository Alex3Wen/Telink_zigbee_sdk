/***************************************************************************
 *                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Globals data definitionfor APS subsystem
*/

#ifndef ZB_APS_GLOBALS_H
#define ZB_APS_GLOBALS_H 1

/*! \cond internals_doc */
/*! \addtogroup ZB_APS */
/*! @{ */

/**
   Global binding table
*/
typedef struct zb_aps_bind_src_table_s
{
  zb_address_ieee_ref_t src_addr;   /*!< source address as ref from nwkAddressMap */
  zb_uint8_t            src_end;    /*!< source endpoint */
  zb_uint16_t           cluster_id; /*!< cluster id */
} ZB_PACKED_STRUCT zb_aps_bind_src_table_t;

typedef struct zb_aps_bind_long_dst_addr_s
{
  zb_address_ieee_ref_t dst_addr;        /*!< destination address as ref from nwkAddressMap */
  zb_uint8_t            dst_end;         /*!< destination endpoint */
} ZB_PACKED_STRUCT zb_aps_bind_long_dst_addr_t;

#define ZB_APS_BIND_DST_ADDR_GROUP 0
#define ZB_APS_BIND_DST_ADDR_LONG  1
typedef struct zb_aps_bind_dst_table_s
{
  zb_uint8_t            dst_addr_mode;   /*!< destination address mode flag, 0
                                          * - group address, otherwise long
                                          * address plus dest endpoint */
  union
  {
    zb_uint16_t group_addr;                /*!< group address */
    zb_aps_bind_long_dst_addr_t long_addr; /*!< @see zb_asp_long_dst_addr_t */
  } u;
  zb_uint8_t            src_table_index; /*!< index from zb_asp_src_table_t */
} ZB_PACKED_STRUCT zb_aps_bind_dst_table_t;

typedef struct zb_aps_binding_table_s
{
  zb_aps_bind_src_table_t src_table[ZB_APS_SRC_BINDING_TABLE_SIZE];
  zb_aps_bind_dst_table_t dst_table[ZB_APS_DST_BINDING_TABLE_SIZE];
  zb_uint8_t              src_n_elements;
  zb_uint8_t              dst_n_elements;
} ZB_PACKED_STRUCT zb_aps_binding_table_t;


#define ZB_APS_GROUP_NAME_LEN    16
/**
  Group table entry
 */
typedef struct zb_aps_group_table_ent_s
{
  zb_uint16_t    group_addr;
  zb_uint8_t     endpoints[ZB_APS_ENDPOINTS_IN_GROUP_TABLE];
  zb_ushort_t    n_endpoints;
  zb_uint8_t     group_name[ZB_APS_GROUP_NAME_LEN];
} ZB_PACKED_STRUCT zb_aps_group_table_ent_t;


ZB_RING_BUFFER_DECLARE(zb_aps_grp_up_q, zb_uint8_t, ZB_APS_GROUP_UP_Q_SIZE);

/**
   Group addressing data structure
 */
typedef struct zb_aps_group_table_s
{
  zb_aps_group_table_ent_t groups[ZB_APS_GROUP_TABLE_SIZE]; /*!< APS group table */
  zb_ushort_t              n_groups;                        /*!< # of entries in APS group table */
  zb_aps_grp_up_q_t        pass_up_q; /*!< queue to be used to pass
                                       * incoming group addresses packets up  */
  zb_aps_grp_up_q_t        local_dup_q; /*!< queue to be used to pass sending
                                          group addresses packets to myself */
  zb_buf_t *active_pass_up_buf; /*!< current buffer we are passing up */
} zb_aps_group_table_t;


enum zb_aps_retrans_ent_state_e
{
  ZB_APS_RETRANS_ENT_FREE,
  ZB_APS_RETRANS_ENT_SENT_MAC_NOT_CONFIRMED_ALRM_RUNNING,
  ZB_APS_RETRANS_ENT_SENT_MAC_NOT_CONFIRMED_APS_ACKED_ALRM_RUNNING,
  ZB_APS_RETRANS_ENT_SENT_MAC_CONFIRMED_ALRM_RUNNING
};

/**
   APS retransmissions
 */
typedef struct zb_aps_retrans_ent_s
{
  zb_uint16_t  addr;
  zb_uint16_t  clusterid;
  zb_uint8_t   aps_counter;
  zb_uint8_t   src_endpoint;
  zb_uint8_t   dst_endpoint;
  zb_uint8_t   buf;

  zb_bitfield_t aps_retries:5;
  zb_bitfield_t nwk_insecure:1;
  zb_bitfield_t state:2;        /* \see zb_aps_retrans_ent_state_e */
} ZB_PACKED_STRUCT zb_aps_retrans_ent_t;


ZB_RING_BUFFER_DECLARE(zb_ack_q, zb_uint8_t, ZB_APS_RETRANS_ACK_Q_SIZE);


typedef struct zb_aps_retrans_s
{
  zb_aps_retrans_ent_t hash[ZB_N_APS_RETRANS_ENTRIES];
  zb_uint8_t           ack_buf;
  zb_ack_q_t           ack_q;
#ifdef APS_RETRANSMIT_TEST
  zb_uint8_t   counter;
#endif
} zb_aps_retrans_t;


typedef struct zb_aps_tmp_s
{
  zb_ushort_t            neighbor_table_iterator;
  zb_uint8_t             key_seq_number;
} zb_aps_tmp_t;


#define ZB_APS_ZDO_ED_SCAN_MASK              1
#define ZB_APS_CHANNEL_MANAGER_ED_SCAN_MASK (1 << 1)

#define ZB_APS_SET_ZDO_ED_SCAN_FLAG() ( ZCTRL->aps_ctx.flags |= ZB_APS_ZDO_ED_SCAN_MASK )
#define ZB_APS_CLEAR_ZDO_ED_SCAN_FLAG() ( ZCTRL->aps_ctx.flags &= ~ZB_APS_ZDO_ED_SCAN_MASK )
#define ZB_APS_GET_ZDO_ED_SCAN_FLAG() ( ZCTRL->aps_ctx.flags & ZB_APS_ZDO_ED_SCAN_MASK )

#define ZB_APS_SET_CHANNEL_MANAGER_ED_SCAN_FLAG() ( ZCTRL->aps_ctx.flags |= ZB_APS_CHANNEL_MANAGER_ED_SCAN_MASK )
#define ZB_APS_CLEAR_CHANNEL_MANAGER_ED_SCAN_FLAG() ( ZCTRL->aps_ctx.flags &= ~ZB_APS_CHANNEL_MANAGER_ED_SCAN_MASK )
#define ZB_APS_GET_CHANNEL_MANAGER_ED_SCAN_FLAG() ( ZCTRL->aps_ctx.flags & ZB_APS_CHANNEL_MANAGER_ED_SCAN_MASK )


/**
   APS subsystem globals
 */
typedef struct zb_aps_ctx_s
{
  zb_aps_binding_table_t binding;
  zb_aps_retrans_t       retrans;
  zb_aps_group_table_t   group;
  zb_aps_tmp_t           tmp;

  zb_uint8_t             authenticated; /* if 1, we are authenticated in the network */
  zb_uint8_t             flags;
  zb_uint8_t             dups_alarm_running;
} zb_aps_ctx_t;

/**
   Get APS counter field from AIB.

   @return APS counter
 */
#define ZB_AIB_APS_COUNTER() ZG->aps.aib.aps_counter

/**
   Increment APS counter AIB field.
*/
#define ZB_AIB_APS_COUNTER_INC() ZG->aps.aib.aps_counter++


#define ZB_AIB() ZG->aps.aib


/*! @} */
/*! \endcond */

#endif /* ZB_APS_GLOBALS_H */
