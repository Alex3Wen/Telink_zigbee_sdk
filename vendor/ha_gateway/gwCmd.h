#pragma once

#include "../../proj/tl_common.h"


/** @addtogroup zll_ctrl_command_id ZLL Control Command ID
 * @{
 */
#define ZLL_CTRL_CMD_TOUCHLINK                          0x01
#define ZLL_CTRL_CMD_RESET_TO_FN                        0x02
#define ZLL_CTRL_CMD_CH_CHANNEL                         0x03
#define ZLL_CTRL_CMD_JOIN_HA                            0x04
#define ZLL_CTRL_CMD_PERMIT_JOIN                        0x05
#define ZLL_CTRL_CMD_SEND_RESET_TO_FN                   0x06
#define ZLL_CTRL_CMD_DEV_ANN_IND                        0x07
#define ZLL_CTRL_CMD_GET_NODES                          0x08
#define ZLL_CTRL_CMD_END_DEV_BIND                       0x09
#define ZLL_CTRL_CMD_SET_TARGET                         0x0a
#define ZLL_CTRL_CMD_SET_GROUP                          0x0b
#define ZLL_CTRL_CMD_SET_GROUP_RSP                      0x0c
#define ZLL_CTRL_CMD_LEAVE_REQ                          0x0d
#define ZLL_CTRL_CMD_LEAVE_CNF                          0x0e
#define ZLL_CTRL_CMD_NEIGHBOR_REPORT                    0x0f
#define ZLL_CTRL_CMD_NEIGHBOR_REPORT_CNF                0x10
/** @} end of group zll_ctrl_command_id */


/** @addtogroup zcl_foundation_cmdid ZCL Foundation Command ID
 * @{
 */
#define ZCL_CMD_READ                                    0x00
#define ZCL_CMD_READ_RSP                                0x01
#define ZCL_CMD_WRITE                                   0x02
#define ZCL_CMD_WRITE_UNDIVIDED                         0x03
#define ZCL_CMD_WRITE_RSP                               0x04
/** @} end of group zcl_foundation_cmdid */


#define GATEWAY_CTRL_CMD_HDR_LEN                        15



typedef struct {
	u8 endpoint;                      //!< This is the application endpoint of the application, it should be set to 0x0B
	u16 nwkAddr;
	u8 reserved0[1];                  //!< All reserved bytes should be set to 0x00
	u16 clusterID;                    //!< should be set to 0xFFFF
	u8 dataLen;                       //!< This should be 6 + the number of parameters in the MT_APP Command
	u8 reserved1[3];                  //!< All reserved bytes should be set to 0x00
	u8 cmdID;                         //!< @ref zll_ctrl_command_id
	u8 reserved2[2];                  //!< All reserved bytes should be set to 0x00
	u8 payload[1];
} ctrl_cmd_t;


typedef struct {
	u8 endpoint;                     //!< This is the application endpoint of the application, it should be set to 0x0B
	u16 dstNwkAddr;                  //!< Network Address (or groupId depending on address mmode) of the device to send the ZCL message to
	u8 dstEndpoint;                  //!< End Point of the device to send the ZCL message to
	u16 clusterID;                   //!< Cluster ID of the ZCL Command to be sent
	u8 dataLen;                      //!< This should be 6 + the number of parameters in the ZCL Command
	u8 addrMode;                     //!< The address mode of the ZCL message
	u8 zclFrameCtrl;                 //!< ZCL Frame Control Field
	u8 zclTransSeqNo;                //!< The transaction ID should be incremented for each ZCL message
	u8 cmdID;                        //!< Command ID of the ZCL Command to be sent
	u8 payload[1];                   //!< Payload of the ZCL Command to be sent
} data_cmd_t;


typedef struct {
    u8 token;
	u8 len;
	u8 cmd0;                         //!< Always be 0x49 
	u8 cmd1;                         //!< Always be 0x00 
	union {
		ctrl_cmd_t ctrlCmd;
		data_cmd_t dataCmd;
	} data;
} gw_app_cmd_t;

typedef struct cmd_dev_info_tag {
	u16 nwkAddr;
	u8  extAddr[8];
	u8  nodeCapability;
    u8  endpoint;
    u16  devId;
} cmd_dev_info_t;

void gateway_cmdHandler(u8 *pBuf);
void gateway_sendCtrlCmd(u8 cmdId, u8* data, u8 len, u16 nwkAddr);
void gateway_hookZCLMsg(zclIncoming_t *pInMsg);
void gateway_sendZCLCmd(u8 dstEp, u8 dstAddrMode, u16 dstAddr, u16 clusterId, u8* cmd, u8 len);

