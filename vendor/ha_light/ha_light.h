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
//#define APP_COORDINATOR        1
#define APP_ROUTER             1
//#define APP_END_DEVICE         1



/**********************************************************************
 * GLOBAL VARIABLES
 */
extern zb_af_simple_desc_t haLight_simpleDesc;




/**********************************************************************
 * LOCAL FUNCTIONS
 */
void haLight_zdoStartDevCnf(zdoStartDevCnf_t* startDevCnf);
void haLight_devAnnHandler(zdo_devAnnInd_t* pInd);

void haLight_zclDfltRspHandler(zclDefaultRspCmd_t* pDfltRsp);
void haLight_zclReadAttrRspHandler(zclReadRspCmd_t* pReadRsp);
void haLight_zclWriteAttrRspHandler (zclWriteRspCmd_t *pWriteRsp);

void haLight_zclOnoffCmdHandler(u8 cmd);
void haLight_zclMoveToLevelCmdHandler( moveToLvl_t* cmd );
void haLight_zclStepCmdHandler( step_t *cmd );
void haLight_zclStopCmdHandler();

void haLight_start(void);



