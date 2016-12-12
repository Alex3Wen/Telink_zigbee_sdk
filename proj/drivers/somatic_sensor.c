
#include "../tl_common.h"
#include "../os/sys.h"
#include "somatic_sensor.h"

#if(MODULE_SOMATIC_ENABLE)

static somatic_sensor_data_t somatic_sensor_event;

void somatic_sensor_check_event(void){

	static u32 last_check_time = 0;
	if(clock_time_exceed(last_check_time, SOMATIC_SCAN_INTERVAL)){
		last_check_time = clock_time();
	
		STATIC_ASSERT_INT_DIV(sizeof(somatic_sensor_data_t), 4);
	    u32 this_data_not_zero = !ismemzero4(&somatic_sensor_event, sizeof(somatic_sensor_data_t));
    	
	    static u32 last_data_not_zero = 0;
		if(this_data_not_zero || last_data_not_zero){
		    last_data_not_zero = this_data_not_zero;
			// handle immediately or we have to find somewhere to clear somatic_sensor_event
			ev_emit_event_syn(EV_SOMATIC_EVENT, &somatic_sensor_event);
			zeromem4(&somatic_sensor_event, sizeof(somatic_sensor_data_t));
		}
	}

}

rf_packet_somatic_resp_to_host_t rf_somatic_resp_host = {FRAME_TYPE_SOMATIC_RESP_HOST, sizeof(rf_packet_somatic_resp_to_host_t)};		//	set resp data

//extern void led_test(void);
void somatic_handle_host_cmd(rf_packet_somatic_host_t *ele){

}


void somatic_sensor_init(void){
//	ev_on_poll(EV_POLL_SOMATIC_EVENT, somatic_sensor_check_event);
}
#endif
