
// device id
#include "../tl_common.h"
#include "../drivers/flash.h"
#include "flash_vendor.h"
#include "did.h"

device_id_t did_device_id;

#define DID_PEER_AREA_SIZE		64

void did_read_ids(void){
	int data_updated = 0;
#if(APPLICATION_DONGLE)
	flash_read_page(DID_STORED_ADDRESS, sizeof(did_device_id), (u8*)(&did_device_id));
	while(!did_is_self_id_valid()){
		did_device_id.self_id = (rand() << 16) | rand();
		data_updated = 1;
	}
	if(!did_is_vendor_valid()){
		did_device_id.vend_id = ID_VENDOR;
		data_updated = 1;
	}
	if(data_updated){
		flash_write_page(DID_STORED_ADDRESS, sizeof(did_device_id), (u8*)(&did_device_id));
	}
#else
	u8 temp[DID_PEER_AREA_SIZE + OFFSETOF(device_id_t, peer_id)];
	flash_read_page(DID_STORED_ADDRESS, sizeof(temp), (u8*)temp);

	device_id_t *p = (device_id_t*)(temp);
	did_device_id.self_id = p->self_id;
	did_device_id.vend_id = p->vend_id;

	while(!did_is_self_id_valid()){
		did_device_id.self_id = (rand() << 16) | rand();
		data_updated = 1;
	}
	if(!did_is_vendor_valid()){
		did_device_id.vend_id = ID_VENDOR;
		data_updated = 1;
	}
	
	u32 *p_peer_id = (u32*)(&p->peer_id);
	did_device_id.peer_id = *p_peer_id;
	foreach(i, (DID_PEER_AREA_SIZE / sizeof(did_device_id.peer_id))){
		if(!did_is_id_valid(*p_peer_id)){
			break;
		}
		did_device_id.peer_id = *p_peer_id++;
	}
	if(data_updated){
		flash_write_page(DID_STORED_ADDRESS, sizeof(did_device_id), (u8*)(&did_device_id));
	}
#endif

}

int did_write_peer_id(u32 id){
#if(APPLICATION_DONGLE)
	return 1;			//  the dongle not saving ids 
#else
	if(did_device_id.peer_id == id){
		return 1;
	}
	// update
	did_device_id.peer_id = id;

	u8 temp[DID_PEER_AREA_SIZE];
	flash_read_page(DID_STORED_ADDRESS + OFFSETOF(device_id_t, peer_id), sizeof(temp), (u8*)temp);
	u32 *p_peer_id = (u32*)(temp);
	foreach(i, (DID_PEER_AREA_SIZE / sizeof(did_device_id.peer_id))){
		if(!did_is_id_valid(*p_peer_id)){
			flash_write_page((DID_STORED_ADDRESS + OFFSETOF(device_id_t, peer_id)) + (i << 2), sizeof(id), (u8*)(&id));
			return 1;
		}
		++p_peer_id;
	}
	return 0;
#endif
}

void did_init(void){
	did_read_ids();
}

