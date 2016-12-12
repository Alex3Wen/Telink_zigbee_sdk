
#include "../drivers/flash.h"
#include "flash_vendor.h"

// be careful not to list all vendor here, in case bloat the code size
const int FLASH_VENDOR_ID	= FLASH_VENDOR_WINBOND;

u32 flash_get_capacity(void){
	u32 cap_id = flash_get_jedec_id() & 0xff;

	if(FLASH_VENDOR_ID == FLASH_VENDOR_WINBOND){
		if(0x10 == cap_id){
			return 0x10000; 		// 64K bytes
		}
		else if(0x11 == cap_id){
			return 0x20000; 		// 1M  bytes
		}else if(0x12 == cap_id){
			return 0x40000; 		// 2M  bytes
		}else if(0x13 == cap_id){ 	// 4M  bytes
			return 0x80000;
		}else{
			return 0x100000;		// 8M bytes
		}
	}

}

