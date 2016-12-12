
#pragma once

typedef struct{
	u16 vend_id;		// vendor id
	u16 rsv;
	u32 self_id;		// self device serial
	u32 peer_id;
}device_id_t;

extern device_id_t did_device_id;

static inline u32 did_get_vend_id(void){
	return did_device_id.vend_id;
}

static inline u32 did_get_self_id(void){
	return did_device_id.self_id;
}

#if(APPLICATION_DONGLE)	// a dongle could have many peer ids,  a device has only one peer -- the dongle
int did_find_peer_id(u32 id);
#else
static inline u32 did_get_peer_id(void){
	return did_device_id.peer_id;
}
#endif

static inline int did_is_vendor_valid(void){
	return did_device_id.vend_id && (did_device_id.vend_id != U16_MAX);
}

static inline int did_is_id_valid(u32 id){
	return id && (id != U32_MAX);
}

static inline int did_is_self_id_valid(void){
	return did_is_id_valid(did_device_id.self_id);
}

#if!(APPLICATION_DONGLE)
static inline int did_is_peer_id_valid(void){
	return did_is_id_valid(did_device_id.peer_id);
}
#endif

int did_write_peer_id(u32 id);
void did_init(void);

