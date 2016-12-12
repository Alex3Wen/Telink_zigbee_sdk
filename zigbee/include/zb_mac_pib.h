#ifndef ZB_MAC_PIB_H
#define ZB_MAC_PIB_H 1

#include "zb_mac.h"


/**
   MAC PIB
 */
typedef struct
{
#if defined(ZB_CONFIGURABLE_MAC_PIB) || defined(ZB_NS_BUILD) || defined(ZB_CC25XX) || defined(ZB_TC32)
  zb_uint16_t             mac_ack_wait_duration;         /*!< The maximum number of symbols to wait for an
                                                           acknowledgment frame to arrive following a
                                                           transmitted data frame.
                                                           The commencement time is described in 7.5.6.4.2.*/
#endif
  zb_uint8_t              mac_association_permit;        /*!< Indication of whether a coordinator is currently
                                                           allowing association. A value of TRUE indicates
                                                           that association is permitted. */
  zb_uint8_t              mac_auto_request;              /*!< Indication of whether a device automatically
                                                           sends a data request command if its address
                                                           is listed in the beacon frame.
                                                           indication primitive (see 7.1.5.1.2). */
  zb_uint8_t              mac_batt_life_ext;             /*!< Indication of whether BLE, through the reduction of
                                                           coordinator receiver operation time during the CAP,
                                                           is enabled. Also, see 7.5.1.4 for an explanation. */
  zb_mac_beacon_payload_t mac_beacon_payload;            /*!< The contents of the beacon payload. */
  zb_uint8_t              mac_beacon_payload_length;     /*!< The length, in octets, of the beacon payload. */
  zb_uint8_t              mac_beacon_order;              /*!< Specification of how often the coordinator
                                                           transmits its beacon. */
  zb_uint8_t              mac_bsn;                       /*!< The sequence number added to the transmitted
                                                           beacon frame. */
  zb_ieee_addr_t          mac_coord_extended_address;    /*!< The 64-bit address of the coordinator
                                                           through which the device is associated. */
  zb_uint16_t             mac_coord_short_address;       /*!< The 16-bit short address assigned to the coordinator
                                                           through which the device is associated. */
  zb_uint8_t              mac_dsn;                       /*!< The sequence number added to the transmitted data
                                                           or MAC command frame. */
  zb_uint16_t             mac_pan_id;                    /*!< The 16-bit identifier of the PAN on which
                                                           the device is operating. If this value is 0xffff,
                                                           the device is not associated. */
  zb_uint8_t              mac_rx_on_when_idle;           /*!< Indication of whether the MAC sublayer is to enable
                                                           its receiver during idle periods. */
  zb_uint16_t             mac_short_address;             /*!< The 16-bit address that the device uses
                                                           to communicate in the PAN. */
  zb_uint16_t             mac_superframe_order;          /*!< The length of the active portion of the outgoing
                                                           superframe, including the beacon frame. */
#if defined(ZB_CONFIGURABLE_MAC_PIB) || defined(ZB_NS_BUILD) || defined(ZB_CC25XX) | defined(ZB_TC32)
  zb_uint8_t              mac_max_frame_retries;         /*!< The maximum number of retries allowed after a
                                                           transmission failure. */
#endif
#ifdef ZB_CONFIGURABLE_MAC_PIB
  zb_uint16_t             mac_transaction_persistence_time; /*!< The maximum time (in unit periods) that
                                                              a transaction is stored by a coordinator and
                                                              indicated in its beacon. */
  zb_uint8_t              mac_response_wait_time;        /*!< The maximum time, in multiples of aBaseSuperframeDuration,
                                                           a device shall wait for a response command frame to
                                                           be available following a request command frame. */
  zb_uint16_t             mac_max_frame_total_wait_time; /*!< The maximum number of CAP symbols in a beaconenabled
                                                           PAN, or symbols in a nonbeacon-enabled PAN, to wait
                                                           either for a frame intended as a response to a
                                                           data request frame or for a broadcast frame following a
                                                           beacon with the Frame Pending subfield set to one. */
/* next parameters are also unused */
  zb_uint16_t             mac_base_superframe_duration;  /*!< The number of symbols forming a superframe when
                                                           the superframe order is equal to 0. */
  zb_uint8_t              mac_max_csma_backoffs;         /*!< The maximum number of backoffs the CSMA-CA algorithm
                                                           will attempt before declaring a channel access failure. */
  zb_uint8_t              mac_batt_life_ext_periods;     /*!< In BLE mode, the number of backoff periods
                                                           during which the receiver is enabled after
                                                           the IFS following a beacon. */
  zb_uint8_t              mac_gts_permit;                /*!< TRUE if the PAN coordinator is to accept
                                                           GTS requests. FALSE otherwise. */
  zb_uint8_t              mac_promiscuous_mode;          /*!< Indication of whether the MAC sublayer is in a
                                                           promiscuous (receive all) mode. */
  zb_uint8_t              mac_min_be;                    /*!< *The minimum value of the backoff exponent (BE)
                                                           in the CSMA-CA algorithm. See 7.5.1.4
                                                           for a detailed explanation */  
#endif
  zb_uint8_t              phy_current_page;  

  zb_uint8_t              phy_current_channel;

  zb_ieee_addr_t          mac_extended_address;          /*!< The 64-bit (IEEE) address assigned to the device. */
#ifdef ZB_MAC_SECURITY
  zb_mac_device_table_t mac_device_table[MAC_DEVICE_TABLE_SIZE];
  zb_uint8_t            mac_device_table_entries;
  zb_uint32_t           mac_frame_counter;
  zb_uint8_t            mac_key[16];
#endif

} ZB_PACKED_STRUCT
 zb_mac_pib_t;


#endif

