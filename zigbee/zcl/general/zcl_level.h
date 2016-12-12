#pragma once


/*********************************************************************
 * CONSTANTS
 */

/* Command ID */
#define ZCL_CMD_LEVEL_MOVE_TO_LEVEL                       0x00
#define ZCL_CMD_LEVEL_MOVE                                0x01
#define ZCL_CMD_LEVEL_STEP                                0x02
#define ZCL_CMD_LEVEL_STOP                                0x03
#define ZCL_CMD_LEVEL_MOVE_TO_LEVEL_WITH_ON_OFF           0x04
#define ZCL_CMD_LEVEL_MOVE_WITH_ON_OFF                    0x05
#define ZCL_CMD_LEVEL_STEP_WITH_ON_OFF                    0x06
#define ZCL_CMD_LEVEL_STOP_WITH_ON_OFF                    0x07

/*** Level Control Move (Mode) Command values ***/
#define LEVEL_MOVE_UP                                     0x00
#define LEVEL_MOVE_DOWN                                   0x01

/*** Level Control Step (Mode) Command values ***/
#define LEVEL_STEP_UP                                     0x00
#define LEVEL_STEP_DOWN                                   0x01


/* Attribute ID */
#define ZCL_ATTRID_LEVEL_CURRENT_LEVEL                    0x0000
#define ZCL_ATTRID_LEVEL_REMAINING_TIME                   0x0001
#define ZCL_ATTRID_LEVEL_ON_OFF_TRANSITION_TIME           0x0010
#define ZCL_ATTRID_LEVEL_ON_LEVEL                         0x0011

/*********************************************************************
 * ENUMS
 */



/*********************************************************************
 * TYPES
 */

typedef struct {
	u8  level;          // new level to move to
	u8  withOnOff;      // with On/off command
	u16 transitionTime; // time to take to move to the new level (in seconds)
} moveToLvl_t;

typedef struct {
	u8 moveMode;  // move mode which is either LEVEL_MOVE_STOP, LEVEL_MOVE_UP,
	// LEVEL_MOVE_ON_AND_UP, LEVEL_MOVE_DOWN, or LEVEL_MOVE_DOWN_AND_OFF
	u8 rate;      // rate of movement in steps per second
	u8 withOnOff; // with On/off command
} move_t;

typedef struct {
	u8  stepMode;       // step mode which is either LEVEL_STEP_UP, LEVEL_STEP_ON_AND_UP,
	// LEVEL_STEP_DOWN, or LEVEL_STEP_DOWN_AND_OFF
	u8  stepSize;       // number of levels to step
	u16 transitionTime; // time, in 1/10ths of a second, to take to perform the step
	u8  withOnOff;      // with On/off command
} step_t;


/* Command Callback Function Type */
typedef void (*zcl_level_moveToLevelCb_t)( moveToLvl_t* cmd );
typedef void (*zcl_level_moveCb_t)( move_t* cmd );
typedef void (*zcl_level_stepCb_t)( step_t* cmd );
typedef void (*zcl_level_stopCb_t)( void );

typedef struct {
	zcl_level_moveToLevelCb_t    move2levelCbFunc;
	zcl_level_moveCb_t           moveCbFunc;
	zcl_level_stepCb_t           stepCbFunc;
	zcl_level_stopCb_t           stopCbFunc;
} zcl_level_AppCallbacks_t;



/*********************************************************************
 * GLOBAL VARIABLES
 */

#ifdef ZCL_LEVEL_CTRL
  #ifdef ZCL_ATTR_CUR_LEVEL_ENABLE
    extern u8 zcl_attr_curLevel;
  #endif
  #ifdef ZCL_ATTR_REMAINING_TIME_ENABLE
    extern u16 zcl_attr_remainTime;
  #endif
  #ifdef ZCL_ATTR_ONOFF_TRANS_TIME_ENABLE
    extern u16 zcl_attr_onOffTransTime;
  #endif
  #ifdef ZCL_ATTR_ON_LEVEL_ENABLE
    extern u8 zcl_attr_onLevel;
  #endif

extern zclAttrInfo_t level_attrTbl[];
#endif


/*********************************************************************
 * Public Functions
 */
#ifdef ZCL_LEVEL_CTRL
rst_t zcl_level_register(u8 attrNum, zclAttrInfo_t* pAttrTbl, zcl_level_AppCallbacks_t* cb);
#endif

void zcl_level_move2level(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 level, u16 transTime);
void zcl_level_move(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 mode, u8 rate);
void zcl_level_step(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 stepMode, u8 stepSize, u16 transTime);
void zcl_level_stop(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo);
void zcl_level_move2level_withOnOff(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 level, u16 transTime);
void zcl_level_move_withOnOff(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 mode, u8 rate);
void zcl_level_step_withOnOff(u8 srcEp, epInfo_t* pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, u8 stepMode, u8 stepSize, u16 transTime);


