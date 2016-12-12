
#pragma once


typedef void (*th_recvCb_t)(u8*);


int recvCmdFromTH(u8 *recvBuf, u8 bufLen);
int sendCmdToTH(u8* buf, u8 len);
void TH_trxInit(th_recvCb_t cb);
