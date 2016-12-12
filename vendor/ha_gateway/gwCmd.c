#include "../../proj/tl_common.h"

#if (__PROJECT_HA_GATEWAY__)

/**********************************************************************
 * INCLUDES
 */
#include "../../proj/app/usbcdc.h"
#include "../../zigbee/zbapi/zb_api.h"
#include "../../zigbee/zcl/zcl_include.h"
#include "../../zigbee/ha/ha.h"

#include "gwCmd.h"
#include "ha_gateway.h"



/**********************************************************************
 * LOCAL CONSTANTS
 */
#define DFLT_GW_TX_OPTION          0
#define DLFT_GW_RADIUS             0x0a

/**********************************************************************
 * TYPEDEFS
 */

u8 haGateway_seqNo;
/**********************************************************************
 * LOCAL FUNCTIONS
 */


/**********************************************************************
 * LOCAL VARIABLES
 */


/**********************************************************************
 * LOCAL Functions Implementation
 */

void gateway_ctrlCmdHandler(u8 srcEp, u16 clusterId, u8 len, u8 cmdID, u8* cmdPayload, u16 nwkAddr)
{
	u8 data[100];
	u8 *p = data;
	u8 i;
	u8 num;

	if ( ZLL_CTRL_CMD_GET_NODES == cmdID ) {
		//num = nodes_curNum();
		//*p++ = num;

		//p += nodes_fillNodeList(p);
		//gateway_sendCtrlCmd(ZLL_CTRL_CMD_GET_NODES, data, p-data, 0);
	} else if(ZLL_CTRL_CMD_END_DEV_BIND == cmdID) {
		//zb_endDeviceBindReq(0x0000, 0x0000, haApp_simpleDesc.app_profile_id, HA_APP_ENDPOINT, ZB_PIB_EXTENDED_ADDRESS(),
			//	APP_IN_CLUSTER_NUM, haApp_inClusterList, APP_OUT_CLUSTER_NUM, haApp_outClusterList);
	} else if(ZLL_CTRL_CMD_SET_TARGET == cmdID) {
        //haApp_setTarget(cmdPayload);
	} else if(ZLL_CTRL_CMD_LEAVE_REQ == cmdID) {
        //haApp_leaveDev(nwkAddr);
	} else if(ZLL_CTRL_CMD_NEIGHBOR_REPORT == cmdID) {
        //haApp_getNeighborTbl(nwkAddr);
	} else if(ZLL_CTRL_CMD_PERMIT_JOIN == cmdID) {
		if (cmdPayload[0] == 0x01)
			zb_nlmePermitJoiningRequest(0xff);
		else if (cmdPayload[0] == 0x0)
			zb_nlmePermitJoiningRequest(0);
	}
}


void gateway_cmdHandler(u8 *pBuf)
{
    data_cmd_t *pDataCmd = NULL;
	ctrl_cmd_t *pCtrlCmd = NULL;
    gw_app_cmd_t* pCmd = (gw_app_cmd_t*)(pBuf);
    
	if (pCmd->cmd0 != 0x49 || pCmd->cmd1 != 0x00) {
		return;
	}

	if (pCmd->data.ctrlCmd.clusterID == 0xffff) {
		pCtrlCmd = &pCmd->data.ctrlCmd;
		/* handle the ctrl command */
		gateway_ctrlCmdHandler(pCtrlCmd->endpoint, pCtrlCmd->clusterID, pCtrlCmd->dataLen, pCtrlCmd->cmdID, pCtrlCmd->payload, pCtrlCmd->nwkAddr);
    } else {
		pDataCmd = &pCmd->data.dataCmd;
        /* Send ZigBee Data */
        gateway_sendZCLCmd(pDataCmd->dstEndpoint, pDataCmd->addrMode, pDataCmd->dstNwkAddr, pDataCmd->clusterID, &pDataCmd->zclFrameCtrl, pDataCmd->dataLen);
    }
}



void gateway_sendCtrlCmd(u8 cmdId, u8* data, u8 len, u16 nwkAddr)
{
	u8 *buf = bufm_allocate(DFLT_SMALL_BUF_SIZE);
	gw_app_cmd_t *pCmd = (gw_app_cmd_t*)buf;
    
    if (!buf) {
          while(1);
      }
	pCmd->token = 0xFE;
	pCmd->cmd0 = 0x49;
	pCmd->cmd1 = 0x81;
	pCmd->data.ctrlCmd.endpoint = 0;
	pCmd->data.ctrlCmd.cmdID = cmdId;
	pCmd->data.ctrlCmd.clusterID = 0xffff;
	pCmd->data.ctrlCmd.dataLen = len+3;
    pCmd->data.ctrlCmd.nwkAddr = nwkAddr;
	pCmd->len = GATEWAY_CTRL_CMD_HDR_LEN + len;

	memcpy(pCmd->data.ctrlCmd.payload, data, len);
#if USB_CDC_ENABLE
    sendCmdToTH(buf, pCmd->len+2);
#endif
	bufm_free(buf);
}


void gateway_hookZCLMsg(zclIncoming_t *pInMsg)
{
	u8 *buf = bufm_allocate(DFLT_SMALL_BUF_SIZE);
	gw_app_cmd_t *pCmd = (gw_app_cmd_t*)buf;
    
    if (!buf) {
          while(1);
    }
	/* construct the data response message */
	pCmd->token = 0xFE;
	pCmd->cmd0 = 0x49;
	pCmd->cmd1 = 0x80;
	pCmd->data.dataCmd.endpoint = pInMsg->msg->indInfo.dst_endpoint;
	pCmd->data.dataCmd.dstNwkAddr = pInMsg->msg->indInfo.src_addr;
	pCmd->data.dataCmd.dstEndpoint = pInMsg->msg->indInfo.src_endpoint;
	pCmd->data.dataCmd.clusterID = pInMsg->msg->indInfo.clusterid;
	pCmd->data.dataCmd.dataLen = pInMsg->msg->asduLen;
	pCmd->data.dataCmd.addrMode = 0x02;
	pCmd->len = 13 + pInMsg->msg->asduLen - 3;
	memcpy(&pCmd->data.dataCmd.zclFrameCtrl, pInMsg->msg->asdu, pInMsg->msg->asduLen);
#if USB_CDC_ENABLE
    sendCmdToTH(buf, pCmd->len+2);
#endif
	bufm_free(buf);
}


void gateway_sendZCLCmd(u8 dstEp, u8 dstAddrMode, u16 dstAddr, u16 clusterId, u8* zclHdr, u8 len)
{
    epInfo_t dstEpInfo;
    dstEpInfo.dstAddrMode = dstAddrMode;
    dstEpInfo.dstEp = dstEp;
    dstEpInfo.dstAddr.addr_short = dstAddr;
    dstEpInfo.profileId = HA_PROFILE_ID;
    dstEpInfo.txOptions = DFLT_GW_TX_OPTION;
    dstEpInfo.radius    = DLFT_GW_RADIUS;
    u8 cmdId = *(zclHdr+2);
    
    /* OnOff Command */
    if (ZCL_CLUSTER_ID_GEN_ON_OFF == clusterId) {
        zcl_onOff_sendCmd(cmdId, HA_APP_ENDPOINT, &dstEpInfo, FALSE, haGateway_seqNo++);
    }

    /* Level Command */
    if (ZCL_CLUSTER_ID_GEN_LEVEL_CONTROL == clusterId) {
        u16 transTime;
        u8 level = *(zclHdr+3);
        memcpy((u8*)&transTime, zclHdr + 4, sizeof(u16));

        if (ZCL_CMD_LEVEL_MOVE_TO_LEVEL == cmdId) {
            zcl_level_move2level(HA_APP_ENDPOINT, &dstEpInfo, FALSE, haGateway_seqNo++, level, transTime);
        } else if (ZCL_CMD_LEVEL_MOVE_TO_LEVEL_WITH_ON_OFF == cmdId) {
            zcl_level_move2level_withOnOff(HA_APP_ENDPOINT, &dstEpInfo, FALSE, haGateway_seqNo++, level, transTime);
        }
    }
    

    /* Group Command */
    if (ZCL_CLUSTER_ID_GEN_GROUPS == clusterId) {
        u16 groupId;
        u8 groupName[1];
        groupName[0] = 0;
        memcpy((u8*)&groupId, zclHdr + 3, sizeof(u16));
        if (ZCL_CMD_GROUP_ADD_GROUP == cmdId) {
            zcl_group_add(HA_APP_ENDPOINT, &dstEpInfo, FALSE, haGateway_seqNo++, groupId, groupName);
        } else if (ZCL_CMD_GROUP_REMOVE_GROUP == cmdId) {
            zcl_group_remove(HA_APP_ENDPOINT, &dstEpInfo, FALSE, haGateway_seqNo++, groupId);
        }
    }

    /* Identify Command */
    if (ZCL_CLUSTER_ID_GEN_IDENTIFY == clusterId) {
        u16 identifyTime;
        memcpy((u8*)&identifyTime, zclHdr + 3, sizeof(u16));
        zcl_identify_sendIdentify(HA_APP_ENDPOINT, &dstEpInfo, FALSE, haGateway_seqNo++, identifyTime);
    }
    
}




#endif  /* __PROJECT_HA_GATEWAY__ */

