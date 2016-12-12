#pragma once


/*********************************************************************
 * CONSTANTS
 */

/* Command ID */
#define ZCL_CMD_GROUP_ADD_GROUP                           0x00
#define ZCL_CMD_GROUP_VIEW_GROUP                          0x01
#define ZCL_CMD_GROUP_GET_MEMBERSHIP                      0x02
#define ZCL_CMD_GROUP_REMOVE_GROUP                        0x03
#define ZCL_CMD_GROUP_REMOVE_ALL_GROUP                    0x04
#define ZCL_CMD_GROUP_ADD_GROUP_IF_IDF                    0x05

#define ZCL_CMD_GROUP_ADD_GROUP_RSP                       0x00
#define ZCL_CMD_GROUP_VIEW_GROUP_RSP                      0x01
#define ZCL_CMD_GROUP_GET_MEMBERSHIP_RSP                  0x02
#define ZCL_CMD_GROUP_REMOVE_GROUP_RSP                    0x03


/* Attribute ID */
#define ZCL_ATTRID_GROUP_NAME_SUPPORT                     0x0000

/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */

typedef struct {
	u8           cmdID;    // which group message - COMMAND_GROUP_ADD_RSP, COMMAND_GROUP_VIEW_RSP,
	// COMMAND_GROUP_REMOVE_RSP or COMMAND_GROUP_GET_MEMBERSHIP_RSP
	u8           status;   // GROUP_STATUS_SUCCESS, GROUP_STATUS_TABLE_FULL,
	// GROUP_STATUS_ALREADY_IN_TABLE, or GROUP_STATUS_NOT_IN_TABLE. Not
	// valid for COMMAND_GROUP_GET_MEMBERSHIP_RSP
	u8           grpCnt;   // number of groups contained in group list
	u16          *grpList; // what group IDs the action was performed on
	u8           capacity; // remaining capacity of group table
	u8           *grpName; // only valid for COMMAND_GROUP_VIEW_RSP
} groupRsp_t;

/* Command Callback Function Type */
typedef void (*zcl_groupRspCb_t)( groupRsp_t *cmd );



typedef struct {
	zcl_groupRspCb_t    groupRspCbFunc;
} zcl_group_AppCallbacks_t;



/*********************************************************************
 * GLOBAL VARIABLES
 */
#ifdef ZCL_GROUP
extern u8 zcl_attr_group_nameSupport;
extern zclAttrInfo_t group_attrTbl[];
#endif


/*********************************************************************
 * Public Functions
 */

/* Client Command */
void zcl_group_add(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId, u8* groupName);
void zcl_group_view(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId);
void zcl_group_remove(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId);
void zcl_group_removeAll(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);
void zcl_group_getMembership(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 groupCnt, u16 *groupList);
void zcl_group_addIfIdentify(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId, u8 *groupName);

/* Server Command */
void zcl_group_add_response(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId, u8 stauts);
void zcl_group_view_response(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId, u8 stauts, u8* groupName);
void zcl_group_getMembership_response(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 capacity, u8 groupCnt, u16* groupList);
void zcl_group_remove_response(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u16 groupId, u8 stauts);


#ifdef ZCL_GROUP
rst_t zcl_group_register(u8 attrNum, zclAttrInfo_t* pAttrTbl, zcl_group_AppCallbacks_t* cb);
#endif  /* ZCL_GROUP */
