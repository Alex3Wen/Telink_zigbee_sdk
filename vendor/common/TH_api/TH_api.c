
#include "../../../proj/tl_common.h"

#if USB_CDC_ENABLE

#ifdef WIN32
#include "../../../proj/simu/socket_api.h"
#else
#include "../../../proj/app/usbcdc.h"
#endif

#include "TH_api.h"


th_recvCb_t th_cbFn = NULL;
priQueue_t th_txPendingQ;


typedef struct {
    u8  len;
    u8* txBuf;
} th_txPendingEvt_t;


int recvCmdFromTH(u8 *recvBuf, u8 bufLen)
{
#ifdef WIN32
    return simu_recvFromTH(recvBuf, bufLen);
#else
    /* TODO: add USB mode */
    return 0;
#endif
    
}



int sendCmdToTH(u8* buf, u8 len)
{
#ifdef WIN32
    return simu_sendToTH(buf, len);
#else
    th_txPendingEvt_t* pEvt;

    if (usbcdc_isAvailable()) {
        usbcdc_sendData(buf, len);
    } else {
        pEvt = (th_txPendingEvt_t*)bufm_allocate(sizeof(th_txPendingEvt_t));
        if (!pEvt) {
            while(1);
        }
        pEvt->len = len;
        pEvt->txBuf = buf;
        priQ_push(&th_txPendingQ, (u8*)pEvt);
    }
#endif
}





void TH_usbRxHandler(u8* pData)
{
	u8* pBuf;

	/* Post task to handle the received command */
	POST_TASK(th_cbFn, pData);

	/* Set the USB RX buffer again */
    pBuf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	if (!pBuf) {
		while(1);
	}
    memset(pBuf, 0, 150);
	usbcdc_setRxBuf(pBuf);
}


void TH_usbTXFinishCb(u8* pData)
{
    th_txPendingEvt_t* pEvt;
    u8 len;
    u8 *p;

    /* Free the TX buffer at first */
    bufm_free(pData);

    /* If there is pending data, send it again */
    if (th_txPendingQ.current_capacity) {
        pEvt = (th_txPendingEvt_t*)priQ_pop(&th_txPendingQ);
        p = pEvt->txBuf;
        len = pEvt->len;
        bufm_free((u8*)pEvt);
        sendCmdToTH(p, len);
    }
}





void TH_trxInit(th_recvCb_t cb)
{
#ifdef WIN32
    socket_param_init(TEST_SOCKET);
#else
    u8* pBuf;

	/* Initialize USB-UART */
    usbcdc_setCB(TH_usbRxHandler, TH_usbTXFinishCb);
	pBuf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	if (!pBuf) {
		while(1);
	}

	/* Set RX buffer to USB-CDC */
	usbcdc_setRxBuf(pBuf);

	/* Register callback to handle received command */
	th_cbFn = cb;

    /* Initialize USB tx pending Queue */
    priQ_init(&th_txPendingQ, NULL);
    
#endif
}


#endif  /* USB_CDC_ENABLE */


