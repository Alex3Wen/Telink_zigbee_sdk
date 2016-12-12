#ifndef ZB_CONFIG_PIB_H
#define ZB_CONFIG_PIB_H 1


/**
   Number of packet buffers. More buffers - more memory. Less buffers - risk to be blocked due to buffer absence.
 */
#define ZB_IOBUF_POOL_SIZE 16

/**
   Size, in bytes, of the packet buffer

   Be sure keep it multiple of 4 to exclude alignment problems at ARM
 */
#define ZB_IO_BUF_SIZE 148


#define MAC_DEVICE_TABLE_SIZE 4

/**
   NWK many-to-one route stuff: route record table size
*/
#define ZB_NWK_ROUTE_RECORD_TABLE_SIZE 5

/**
   NWK Mesh route stuff: routing table size
*/
#define ZB_NWK_ROUTING_TABLE_SIZE 5


/**
   NWK Mesh route stuff: route discovery table size
*/
#define ZB_NWK_ROUTE_DISCOVERY_TABLE_SIZE 5

#define ZB_NWK_PENDING_TABLE_SIZE 5

/* NLS5 - All devices shall maintain at least 2 NWK keys with the frame
   counters consistent with the security mode of the network (Standard or High).*/
#define ZB_SECUR_N_SECUR_MATERIAL 3

/**
 NWK: size os the long-short panid translation table
*/
#define ZB_PANID_TABLE_SIZE 8

#define ZB_NWK_BTR_TABLE_SIZE 16

#define ZB_NWK_BRR_TABLE_SIZE 8

#define ZB_NWK_WAIT_ALLOC_TABLE_SIZE 5

/**
 Maximum number of rejoin requests in progress
*/
#define ZB_NWK_REJOIN_REQUEST_TABLE_SIZE 3

#ifdef ZB_ED_ROLE
/* Only parent is meangful for ED */
/**
 NWK: size of the neighbor table
*/
  #define ZB_NEIGHBOR_TABLE_SIZE 1

/**
 NWK: size of the neighbor table used during discovery phase of join
*/
  #define ZB_EXT_NEIGHBOR_TABLE_SIZE 8
#else
/**
 NWK: size of the neighbor table
*/
  #define ZB_NEIGHBOR_TABLE_SIZE 32
#endif

/**
 NWK: size of the long-short address translation table
*/
#define ZB_IEEE_ADDR_TABLE_SIZE 101

/**
   Maximum number of ZCL clusters
*/
#define ZB_ZCL_CLUSTER_NUM 8

#endif

