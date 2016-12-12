#ifndef ZB_APS_PIB_H
#define ZB_APS_PIB_H 1

/**
   APS Informational Base memory-resident data structure
 */
typedef struct zb_apsib_s
{
  zb_uint8_t  aps_counter;

  /* table 2.138 - Startup parameters */
  zb_uint8_t  aps_designated_coordinator; /*!< This boolean flag indicates whether the
                                            device should assume on startup that it must
                                            become a ZigBee coordinator.  */
  zb_uint8_t  aps_insecure_join; /*!< A boolean flag, which defaults to TRUE and
                                   indicates whether it is OK to use insecure
                                   join on startup.  */
  zb_uint32_t aps_channel_mask; /*!< This is the mask containing allowable
                                  channels on which the device may attempt
                                  to form or join a network at startup time.  */
  zb_ext_pan_id_t aps_use_extended_pan_id; /*!< The 64-bit identifier of the network to join
                                             or form.  */

  zb_ieee_addr_t trust_center_address;
} zb_apsib_t;


#endif

