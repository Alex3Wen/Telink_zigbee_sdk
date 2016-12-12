
#pragma once

/*
    ID == -1 is invalid
    if you want to shut down logging a specified id,  assigne -1 to it
*/


///////////////////////////////////////////////////////////////

// Please donot change the following system defines
// 

#define TR_T_invalid            -1



#define TR_T_PBP_TASK           1
#define TR_T_ZRC_TASK           2
#define TR_T_MAC_TASK           3
#define TR_T_MAC_TRX_TASK       4
#define TR_T_NWK_CB             5
#define TR_T_NWK_TASK           6
#define TR_T_ACK_RECV           7
#define TR_T_ZB_PKT             8
#define TR_T_ZRC_RECV_CNF       9
#define TR_T_ZRC_CMD_SEND       10
#define TR_T_NWK_KEY_SEED       11
#define TR_T_SEND_ACK_TIME      12

#define TR_T_SEND_TX_END_EVT    13
#define TR_T_ACK_TIMER          14

#define TR_T_MAC_RX_CB_TASK     15
#define TR_T_TEST_EVENT         16
#define TR_T_CSMA_TIMER         17
#define TR_T_RX_IRQ             18
#define TR_T_TX_IRQ             19
#define TR_T_INDIR_EXPIRE       20

#define TR_T_TRAN_RECV_FROM_HOST 21
#define TR_T_TRAN_SEND_TO_HOST   22

#define TR_T_TRANSCEIVER_TASK    23




#define TR_24_TIMERS_ADDR        0    // this ID cant be used because timer id == 0 is reserved for indicating id not added
#define TR_24_TIMER0_ADDR        1
#define TR_24_TIMER1_ADDR        2
#define TR_24_TIMER2_ADDR        3
#define TR_24_TIMER3_ADDR        4
#define TR_24_TIMER4_ADDR        5
#define TR_24_TIMER5_ADDR        6
#define TR_24_TIMER6_ADDR        7
#define TR_24_TIMER7_ADDR        8
#define TR_24_TIMER8_ADDR        9
#define TR_24_TIMER9_ADDR        10
#define TR_24_TIMER10_ADDR        11
#define TR_24_TIMER11_ADDR        12
#define TR_24_TIMER12_ADDR        13
#define TR_24_TIMER13_ADDR        14
#define TR_24_TIMER14_ADDR        15

#define TR_24_user1                16    // user define data log id, from 16 -- 64,
#define TR_24_user2                17
#define TR_24_RECV_CRC           18
#define TR_24_IRQ_LABEL          19
#define TR_24_MAC_TRX_Q_NUM      20

#define TR_24_PBP_PRIM_ID        21
#define TR_24_NWK_PRIM_ID        22
#define TR_24_ZRC_CMD_CNT        23
#define TR_24_ZRC_RECV_CNF       24
#define TR_24_NWK_CNF            25
#define TR_24_BACKUP_DATA        26

#define TR_24_TRANS_TYPE         27

#define TR_24_MSDU_LEN           37

#define TR_24_MAC_PRIM           38


#define TR_24_MAC_FRAME_PENDING  28
#define TR_24_RF_DROP_TYPE       29







