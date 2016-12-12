#pragma once


/**********************************************************************
 * CONSTANT
 */

/**        
 *  @brief Definition for Application layer info
 */
#define APP_CHANNEL            13
#define HA_APP_ENDPOINT        0x0B


/**        
 *  @brief Definition for node role
 */
#define APP_COORDINATOR        1
//#define APP_ROUTER             1
//#define APP_END_DEVICE         1




/**********************************************************************
 * LOCAL FUNCTIONS
 */
void haGateway_zdoStartDevCnf(zdoStartDevCnf_t* startDevCnf);
void haGateway_devAnnHandler(zdo_devAnnInd_t* pInd);

void haGateway_zclDfltRspHandler(zclDefaultRspCmd_t* pDfltRsp);
void haGateway_zclReadAttrRspHandler(zclReadRspCmd_t* pReadRsp);
void haGateway_zclWriteAttrRspHandler (zclWriteRspCmd_t *pWriteRsp);


void haGateway_start(void);



