/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Security - API to be used from the applications level
*/

#ifndef ZB_SECUR_API_H
#define ZB_SECUR_API_H 1

/*! \addtogroup secur_api */
/*! @{ */

/**
   Setup pre-configured key to be used by ZCP tests.

   @param key - key to be used
   @param i - key number (0-3)
*/

void zb_secur_setup_preconfigured_key(zb_uint8_t *key, zb_uint8_t i);



/**
   Send new network key to all devices in the net via broadcast

   4.6.3.4  Network Key Update
   4.6.3.4.1  Trust Center Operation

   @param param - buffer with single parameter - short broadcast address. Valid
          values are 0xffff, 0xfffd
 */
void zb_secur_send_nwk_key_update_br(zb_uint8_t param) ;



/**
   Generate switch key.

   According to test 14.24TP/SEC/BV-01-I Security NWK Key Switch (No Pre-
   configured Key)-ZR, this command can be send either to broadcast or unicast
   to all rx-on-when-idle from the neighbor.
   When send unicast, it encrypted by the new (!) key, when send proadcast - by
   the old key.
   That mean, switch our key _after_ this frame transfer and secure - in the
   command send confirm.


   @param param - packet buffer with single parameter - broadcast address. If 0,
          send unicast.
 */
void zb_secur_send_nwk_key_switch(zb_uint8_t param) ;

/**
   Clear preconfigures key (key number 0)
 */
void secur_clear_preconfigured_key();

/*! @} */

#endif /* ZB_SECUR_API_H */
