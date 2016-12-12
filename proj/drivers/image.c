
#include "../tl_common.h"
#include "../drivers/spi.h"
#include "ds.h"
#include "flash.h"
#include "image.h"
/**
  * @brief       read data from flash
  *
  * @param[in]   srcAddr  - the address in flash
  *
  * @param[in]   len  - length of data need to read
  *
  * @param[in]   data - result data
  *
  * @return      None
  *
  */
void image_read(u32 srcAddr, u16 len, u8 *data)
{
	foreach(i, len) {
		data[i] = read_reg8(srcAddr + i);
	}
}

/**
  * @brief       init the flash before write.
  *
  * @param[in]   srcAddr  - the start address of the flash need to erase
  *
  * @param[in]   sectors  - number of sectors need to erase. one sector is 4K bytes
  *
  * @return      None
  *
  */
_attribute_flash_code_ void image_init(u32 srcAddr, u8 sectors)
{
	u8 i;
	for (i=0; i<sectors; i++) {
		flash_erase_sector(srcAddr + i * FLASH_4K_PAGE_NUM * FLASH_PAGE_SIZE);
	}
}


/**
  * @brief       write data to flash
  *
  * @param[in]   srcAddr  - the address in flash
  *
  * @param[in]   len  - length of data need to write
  *
  * @param[in]   data - the date need to save in flash
  *
  * @return      None
  *
  */
_attribute_flash_code_ void image_write(u32 srcAddr, u16 len, u8 *data)
{
	/* get the offset of the srcAddr in one page */
	u8 offset = srcAddr % FLASH_PAGE_SIZE;
	/* check the current page is enough to write */
	if ( FLASH_PAGE_SIZE - offset >= len ) {
		flash_write_page(srcAddr, len, data);
	} else {
		/* write the first FLASH_PAGE_SIZE - offset byte to current page */
		u16 lenSaved = FLASH_PAGE_SIZE - offset;
		flash_write_page(srcAddr, lenSaved, data);
		/* the left length need to save */
		u16 lenLeft = len - lenSaved;
		srcAddr += lenSaved;
		while ( lenLeft >0 ) {
			/* check the left data length, since each time it only can write one page 256 bytes */
			u16 validLen = ( lenLeft > FLASH_PAGE_SIZE) ? FLASH_PAGE_SIZE : lenLeft;
			flash_write_page(srcAddr, validLen, data + lenSaved);
			if ( lenLeft > FLASH_PAGE_SIZE ) {
				lenLeft -= FLASH_PAGE_SIZE;
				lenSaved += FLASH_PAGE_SIZE;
				/* update the srcAddr */
				srcAddr += FLASH_PAGE_SIZE;
			} else {
				lenLeft = 0;
			}
		}
	}
}


_attribute_flash_code_ void image_read_page(u32 srcAddr, u16 len, u8 *data)
{
	/* get the offset of the srcAddr in one page */
	u8 offset = srcAddr % FLASH_PAGE_SIZE;
	/* check the current page is enough to write */
    if ( FLASH_PAGE_SIZE - offset >= len ) {
        flash_read_page(srcAddr, len, data);
    } else {
        /* write the first FLASH_PAGE_SIZE - offset byte to current page */
        u16 lenSaved = FLASH_PAGE_SIZE - offset;
        flash_read_page(srcAddr, lenSaved, data);
        flash_read_page(srcAddr + lenSaved, len - lenSaved, data + lenSaved);
    }
}



#define OTA_DST_ADDR 0//0x1E000

_attribute_flash_code_ void image_copy(u32 srcAddr, u32 len)
{
    u8 buffer[256], sectorNum;
    u32 lenLeft = len, dstAddr = OTA_DST_ADDR;
    u16 readLen = 0;
    
    sectorNum = len/4096;
    
    if (len%4096 != 0){
        sectorNum++;
    }
    
    irq_disable();

    image_init(OTA_DST_ADDR, sectorNum);

    while(lenLeft){
        readLen = (lenLeft > 256)? 256:lenLeft;
        image_read_page(srcAddr, readLen, buffer);
        image_write(dstAddr, readLen, buffer);
        lenLeft -= readLen;
        dstAddr += readLen;
        srcAddr += readLen;
    }
    
    write_reg8(0x800066, 0x06);
    write_reg8(0x80006f, 0x20);
    while(1);
}

/* sample */

/* Start Address 0xC8000, from 200K */
#define START_ADDR      0x32000

void image_test(void)
{
    int i;
	u8 t[60];
	u8 testDate[100];
	image_init(START_ADDR, 10);
	foreach(i, 60) {
		t[i] = i;
	}

	u32 srcAddr = START_ADDR;
	foreach(i, 10) {
		image_write(srcAddr, 60, t);
		srcAddr += 60;
	}
	image_read(START_ADDR, 100, testDate);
}



