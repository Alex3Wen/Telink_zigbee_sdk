/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Address compression, hash and etc.
*/

#ifndef ZB_ADDR_GLOBALS_H
#define ZB_ADDR_GLOBALS_H 1

/*! \cond internals_doc */
/*! \addtogroup ZB_NWK */
/*! @{ */

/**
   \par Define 'global address context' - common place to store and manage
   various ZigBee addresses. It contains array of PANID's, IEEE(64 bit) and 16
   bit address pairs. Protocol tables contains only 1 byte reference to the
   corresponding array. These arrays are hashes indeed, this speed up address
   search. To minimize memory usage open address hash is used.

   Address context consists of:
    - PANID's array - open addressing hash contains known PANID's. Seems MAC or NWK
   should clear it before new scan operation.
    - IEEE/16 bits address pair hash. Array of ieee/16bit address pair. ieee
   address is the key in this hash.
    - 16 bits address hash. The key of this hash is 16 bit address, used for 16
   bits address and corresponding ieee address search. This array contains
   reference to ieee array.

   Clear and reuse elements in ieee/16bit address map:
   Each IEEE/16 bits address pair has lock counter. Lock counter is zero when
   this address is not used in any table, those not used addresses organized in
   lru list. Head of lru list contains address elements that's not used for a
   long time.
*/

#include "zb_address.h"

#define ZB_DEV_MANUFACTORER_TABLE_SIZE 16


/**
   Manufacturer part of the ieee address
*/
typedef struct zb_dev_manufacturer_s
{
  zb_uint8_t device_manufacturer[3]; /*!< Manufactureer identifier - 3 octets */
} zb_dev_manufacturer_t;


/**
   64 bit / 16 bit address map
*/
typedef struct zb_address_map_s
{
  zb_ieee_addr_compressed_t  ieee_addr; /*!< Comressed ieee address */
  zb_uint16_t                addr; /*!< 16 bit device address */
  zb_uint8_t                 aps_dup_counter;
  zb_bitfield_t              used:1; /*!< if 0, this entry is free (never used)  */
  zb_bitfield_t              lock_cnt:4; /*!< lock counter. not locked if 0  */
  zb_bitfield_t              clock:1;    /*!< clock value for the clock usage algorithm  */
  zb_bitfield_t              aps_dup_clock:2;
} ZB_PACKED_STRUCT zb_address_map_t;


/**
   ext pan id and short pan id -> pan ref map
 */
typedef struct zb_pan_id_map_s
{
  zb_ext_pan_id_t long_panid;
  zb_uint16_t     short_panid;
} ZB_PACKED_STRUCT zb_pan_id_map_t;


/*! @} */
/*! \endcond */

#endif /* ZB_ADDR_GLOBALS_H */
