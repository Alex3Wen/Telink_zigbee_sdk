
#include "../tl_common.h"
#include "../common/bufm.h"
#include "flash.h"
#include "image.h"
#include "../app/usbcdc.h"
#include "ota_util.h"
#include "ds.h"

#define FLASH_SIZE      0x40000
#define OTA_PAYLOAD_SIZE 60

typedef struct ota_usbPayload_tag{
    u8 length; /*not include itself*/
    u16 counter;
    u8 payload[OTA_PAYLOAD_SIZE];
} ota_usbPayload_t;



typedef struct {
    u8  ota_en;
    u16 ota_counter;
    u16 sectorNum;
    u32 OTA_Payload_address;
    u32 currFlash_address;
} ota_ctrl_t;

#ifdef STATIC_V_INST
ota_ctrl_t ota_vs;
#endif
ota_ctrl_t *ota_v;

void ota_payload_handler(void* arg)
{
    ota_usbPayload_t *otaPayload = (ota_usbPayload_t*)arg;
    u8 payloadLen = otaPayload->length - 2;

    if(payloadLen != 0){
        image_write(ota_v->currFlash_address, payloadLen, otaPayload->payload);
        ota_v->currFlash_address += payloadLen;
    }
    usbcdc_sendData((u8*)(&otaPayload->counter), 2);
    bufm_free(arg);
    
    if(otaPayload->counter == 0xffff) {
        ota_v->ota_counter = 0;
        ota_v->ota_en = 0;
//        image_copy(ota_v->OTA_Payload_address,ota_v->sectorNum * FLASH_4K_PAGE_NUM * FLASH_PAGE_SIZE);
    }
}

void ota_usbRecvCb(u8* pData)
{
	u8 *pNewBuf;

    if (!pData) {
		return;
	}
    /* If it is not the first ota payload transmission, erase the flash again and init the parameters*/
    if((ota_v->ota_en == 0) && ((ota_v->currFlash_address != ota_v->OTA_Payload_address))) {
        ota_v->currFlash_address = ota_v->OTA_Payload_address;
        image_init(ota_v->OTA_Payload_address, ota_v->sectorNum);
        ota_v->ota_en = 1;
    }
    
    ota_v->ota_counter++;
    
	POST_TASK(ota_payload_handler, (void*)pData);

	/* set a new buffer to receive next USB data */
	pNewBuf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	if (!pNewBuf) {
		while(1);
	}
    
	usbcdc_setRxBuf(pNewBuf);
}

void otaInit(u32 addr, u16 sectorNum)
{
    u8* pBuf;

    if((sectorNum == 0) || ((addr + sectorNum*FLASH_4K_PAGE_NUM * FLASH_PAGE_SIZE) > FLASH_SIZE) 
        || (addr % (FLASH_4K_PAGE_NUM * FLASH_PAGE_SIZE) != 0)) {
        return;
    }
    
#ifdef STATIC_V_INST
	ota_v = &ota_vs;
#else
	ota_v = malloc(sizeof(ota_ctrl_t));
#endif

    image_init(addr, sectorNum);
    ota_v->OTA_Payload_address = addr;
    ota_v->currFlash_address = ota_v->OTA_Payload_address;
    ota_v->sectorNum = sectorNum;
    ota_v->ota_en = 1;
    
#if USB_CDC_ENABLE
	usbcdc_setRxCB(ota_usbRecvCb);
    pBuf = bufm_allocate(DFLT_LARGE_BUF_SIZE);
	if (!pBuf) {
		while(1);
	}
    usbcdc_setRxBuf(pBuf);
#endif
}


