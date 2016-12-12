/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: ZDO globals definition
*/

#ifndef ZB_ZDO_GLOBALS_H
#define ZB_ZDO_GLOBALS_H 1

/*! \addtogroup zdo_ib */
/*! @{ */

#define ZB_ZDO_NODE_DESC() (&ZCTRL->zdo_ctx.conf_attr.node_desc)
#define ZB_ZDO_NODE_POWER_DESC() (&ZCTRL->zdo_ctx.conf_attr.node_power_desc)



typedef struct zb_zdo_configuration_attributes_e
{
  zb_af_node_desc_t       node_desc;
  zb_af_node_power_desc_t node_power_desc;
  zb_af_simple_desc_7_8_t zdo_simple_desc;
  /* TODO: make real list support, if multiple EP are supported */
//  zb_af_simple_desc_1_1_t *simple_desc_list[ZB_MAX_EP_NUMBER];
//  zb_uint8_t simple_desc_number;

  zb_af_endpoint_desc_t   endpoint_desc_list[ZB_MAX_EP_NUMBER];
  zb_uint8_t endpoint_desc_number;

  zb_uint8_t nwk_scan_attempts; /* Integer value representing the
                                 * number of scan attempts to make
                                 * before the NWK layer decides which
                                 * ZigBee coordinator or router to
                                 * associate with (see sub-clause
                                 * 2.5.5.5). This attribute has
                                 * default value of 5 */
  zb_uint16_t nwk_time_btwn_scans; /* Integer value representing the
                                    * time duration (in milliseconds)
                                    * between each NWK discovery
                                    * attempt. This attribute has a
                                    * default value of 100 (milliseconds) */
  zb_uint8_t enddev_bind_timeout; /* Timeout value in seconds employed
                                   * in End Device Binding */
  zb_time_t nwk_indirect_poll_rate;

  zb_uint8_t permit_join_duration; /*!< Permit join duration, 0x00 - disable
                                    * join, 0xff - join is allowed forever */
} zb_zdo_configuration_attributes_t;

/*! @} */


/*! \cond internals_doc */
/*! \addtogroup ZB_ZDO */
/*! @{ */


/**
   Some ZDO private data
 */
#define ZB_TEST_DATA_SIZE 10

#define ZB_ZDO_MAX_CLUSTER_LIST 15

/**
   Some ZDO internal flags
 */
typedef struct zp_zdo_handle_s
{
  zb_uint8_t rejoin;            /*!< if !0, this is rejoin  */
  zb_uint8_t dev_annce;         /*!< if !0, device annonce is sent, here is
                                 * buffer id  */
  zb_uint8_t key_sw;            /*!< if !0, key switch is sent and must switch
                                 * the key after this buffer sent  */
  zb_uint8_t started;           /*!< if !0, zdo_startup_complete was called
                                 * already */
  zb_bitfield_t allow_auth:1;   /*!< if !0, auth is allowed */
  zb_bitfield_t reserved:7;
} zp_zdo_handle_t;


#define ZDO_TRAN_TABLE_SIZE 16


typedef struct zdo_cb_hash_ent_s
{
  zb_callback_t func;
  zb_uint8_t    tsn;
  zb_uint8_t resp_counter;
} zdo_cb_hash_ent_t;

#define ZB_ZDO_CHECK_FAILS_MASK     1      /* flag to check if channel interference check is in progress */
#define ZB_ZDO_SEND_WITH_ACK_MASK   1 << 1 /* flag to specify sending with acknowledgement */
#define ZB_ZDO_CHANNEL_CHANGED_MASK 1 << 2 /* flag shows that channel change opration was performed recently (server side) */

#define ZB_ZDO_SET_CHECK_FAILS()   (ZCTRL->zdo_ctx.flags |= ZB_ZDO_CHECK_FAILS_MASK)
#define ZB_ZDO_CLEAR_CHECK_FAILS() (ZCTRL->zdo_ctx.flags &= ~ZB_ZDO_CHECK_FAILS_MASK)
#define ZB_ZDO_GET_CHECK_FAILS()   (ZCTRL->zdo_ctx.flags & ZB_ZDO_CHECK_FAILS_MASK)

#define ZB_ZDO_SET_SEND_WITH_ACK()   (ZCTRL->zdo_ctx.flags |= ZB_ZDO_SEND_WITH_ACK_MASK)
#define ZB_ZDO_CLEAR_SEND_WITH_ACK() (ZCTRL->zdo_ctx.flags &= ~ZB_ZDO_SEND_WITH_ACK_MASK)
#define ZB_ZDO_GET_SEND_WITH_ACK()   (ZCTRL->zdo_ctx.flags & ZB_ZDO_SEND_WITH_ACK_MASK)

#define ZB_ZDO_SET_CHANNEL_CHANGED()   (ZCTRL->zdo_ctx.flags |= ZB_ZDO_CHANNEL_CHANGED_MASK)
#define ZB_ZDO_CLEAR_CHANNEL_CHANGED() (ZCTRL->zdo_ctx.flags &= ~ZB_ZDO_CHANNEL_CHANGED_MASK)
#define ZB_ZDO_GET_CHANNEL_CHANGED()   (ZCTRL->zdo_ctx.flags & ZB_ZDO_CHANNEL_CHANGED_MASK)

#define ZB_ZDO_NODE_DESC() (&ZCTRL->zdo_ctx.conf_attr.node_desc)

#define ZB_ZDO_NODE_POWER_DESC() (&ZCTRL->zdo_ctx.conf_attr.node_power_desc)
#define ZB_ZDO_SIMPLE_DESC() (&ZCTRL->zdo_ctx.conf_attr.zdo_simple_desc)

#define ZB_ZDO_ENDPOINT_DESC_LIST() (ZCTRL->zdo_ctx.conf_attr.endpoint_desc_list)
#define ZB_ZDO_ENDPOINT_DESC_NUMBER() (ZCTRL->zdo_ctx.conf_attr.endpoint_desc_number)

typedef struct zb_zdo_globals_s
{
  zp_zdo_handle_t handle;
  zb_uint8_t      tsn;
  zb_callback_t   af_data_cb;
  zb_uint8_t      max_parent_threshold_retry;
  zb_uint8_t      parent_threshold_retry;
  zdo_cb_hash_ent_t zdo_cb[ZDO_TRAN_TABLE_SIZE];
  zb_callback_t   system_server_discovery_cb;
  zb_uint8_t      system_server_discovery_tsn;
  zb_uint8_t      flags;
  zb_uint8_t      long_timer; /* long timer, in minutes */
  zb_callback_t   long_timer_cb; /* callback for long timer */
  zb_uint8_t      long_timer_param; /* parameter for long timer */
  zb_uint8_t      parent_link_failure;
  zb_uint8_t      inside_poll;

  zb_zdo_configuration_attributes_t conf_attr; /* Device Configuration Attributes */

  struct zb_zdo_end_device_bind_ctx_s
  {
#define ZB_ZDO_BIND_DEV_1 0
#define ZB_ZDO_BIND_DEV_2 1
#define ZB_ZDO_PEER_DEVICE_NUM(num) (((num) + 1) % 2)

    struct zb_zdo_bind_device_info_s
    {
      zb_uint8_t end_device_bind_param; /* Reference to buffer with
                                         * end_device_bind_req command */
      zb_uint16_t binding_target;  /* The address of the target for the binding */
      zb_uint8_t  src_endp;        /* The endpoint on the binding device */
      zb_uint16_t cluster_list[ZB_ZDO_MAX_CLUSTER_LIST]; /* matched clusters list */
      zb_uint8_t cluster_num;      /* number of matched clusters,
                                    * found during end device bind */
    }
    bind_device_info[2];
    zb_uint8_t current_device; /* current device to send bind/unbind requests */
  }
  end_device_bind_ctx;

  union zb_zdo_ctx_u
  {
    struct zb_nwk_upd_req_ctx_s
    {
      zb_uint32_t scan_channels;
      zb_uint8_t scan_duration;
      zb_uint8_t scan_count;
      zb_uint16_t dst_addr;
      zb_uint8_t tsn;
    }
    nwk_upd_req;
    struct zb_discovery_ctx_s
    {
      zb_uint8_t disc_count;
    }
    discovery_ctx;
    struct zb_get_peer_short_addr_s
    {
      zb_address_ieee_ref_t dst_addr_ref;
      zb_callback_t cb;
      zb_uint8_t param;
    }
    get_short_addr_ctx;
  }
  zdo_ctx;

#ifdef ZB_TEST_PROFILE
  union zb_test_profile_ctx_u
  {
    struct zb_tp_counted_packets_s
    {
      zb_tp_transmit_counted_packets_param_t params;
      zb_callback_t user_cb;
      zb_uint16_t counter;
    }
    tp_counted_packets;
    struct zb_tp_buffer_test_request_s
    {
      zb_callback_t user_cb;
    }
    zb_tp_buffer_test_request;
  }
  test_prof_ctx;
#endif

  zb_callback_t reset_confirm_cb;
} zb_zdo_globals_t;


#define ZDO_CTX() ZCTRL->zdo_ctx

/*! @} */

/*! \endcond */

#endif /* ZB_ZDO_GLOBALS_H */
