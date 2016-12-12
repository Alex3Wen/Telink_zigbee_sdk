#ifndef ZB_GLOBALS_H
#define ZB_GLOBALS_H

#include "zb_types.h"
#include "zb_errors.h"
#include "zb_debug.h"


#include "zb_bufpool_globals.h"
#include "zb_transport_globals.h"

#include "zb_addr_globals.h"
#include "zb_mac_pib.h"
#include "zb_nwk_pib.h"
#include "zb_aps_pib.h"
#include "zb_zcl_pib.h"
/**
   MAC global context
*/
typedef struct zb_mac_globals_s
{
  zb_mac_pib_t    pib;
} zb_mac_globals_t;

/**
   NWK global context
*/
typedef struct zb_nwk_globals_s
{
  zb_nib_t           nib;
  zb_nwk_handle_t    handle;
  zb_neighbor_tbl_t  neighbor;
} zb_nwk_globals_t;

/**
   APS global context
 */
typedef struct zb_aps_globals_s
{
  zb_apsib_t             aib;
} zb_aps_globals_t;

/**
   Global ZCL structure
*/
typedef struct zb_zcl_globals_s
{
  zb_uint8_t seq_number; /*!< ZCL sequence number used when send zcl frames */

  zb_uint8_t cluster_num; /*!< Number of registered clusters */
  zb_zcl_cluster_t cluster[ZB_ZCL_CLUSTER_NUM]; /*!< Cluster array */
} zb_zcl_globals_t;


/**
   Global address context
*/
typedef struct zb_addr_globals_s
{
  zb_uint8_t used_manufacturer[ZB_DEV_MANUFACTORER_TABLE_SIZE / 8 + 1];   /*!<
                                                                           * dev_manufacturer
                                                                           * usage mask  */
  zb_dev_manufacturer_t dev_manufacturer[ZB_DEV_MANUFACTORER_TABLE_SIZE]; /*!<
                                                                           * Manufacturers
                                                                           * array */

  zb_pan_id_map_t pan_map[ZB_PANID_TABLE_SIZE]; /*!< PAN ID's hash */
  zb_uint8_t used_pan_addr[ZB_PANID_TABLE_SIZE / 8 + 1]; /*!< pan_addr usage mask  */

  zb_address_map_t addr_map[ZB_IEEE_ADDR_TABLE_SIZE]; /*!< Address map - open
                                                       * hash by 64-bit address */
  zb_uint8_t short_sorted[ZB_IEEE_ADDR_TABLE_SIZE]; /*!< 16 bits address sort array */
  zb_ushort_t n_elements;                            /*!< # of elements in the
                                                     * address translation table  */
  zb_ushort_t n_sorted_elements; /*!< # of elements in the short_sorted[] */
  zb_ushort_t clock_i;
} zb_addr_globals_t;

/**
   Global data area for data not to be accessed from interrupt handlers
 */
struct zb_globals_s
{
  zb_mac_globals_t        mac;
  zb_nwk_globals_t        nwk;
  zb_aps_globals_t        aps;
  zb_zcl_globals_t        zcl;
  zb_addr_globals_t       addr_record;
};

#endif

