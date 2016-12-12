
#include "../tl_common.h"

#if(USB_SOMATIC_ENABLE)

#include "usbsomatic_i.h"
#include "usbsomatic.h"
#include "../drivers/usb.h"
#include "../drivers/usbhw.h"
#include "../drivers/usbhw_i.h"
#include "../telink_rf/frame.h"
#include "../os/ev.h"

//somatic_sensor_data_t somatic_data;
//  data ÎªSOMATIC_REPORT_DATA_LEN¸öbyte
int usbsomatic_hid_report(u8 *data, u8 len){
	if(usbhw_is_ep_busy(USB_EDP_SOMATIC_IN))
		return 0;

	reg_usb_ep_ptr(USB_EDP_SOMATIC_IN) = 0;

	// please refer to usbsomatic_i.h somatic_report_desc
	//reg_usb_ep_dat(USB_EDP_SOMATIC_IN) = 5;
	foreach(i, len){
	    reg_usb_ep_dat(USB_EDP_SOMATIC_IN) = data[i]; 
	}
	
	reg_usb_ep_ctrl(USB_EDP_SOMATIC_IN) = FLD_EP_DAT_ACK;		// ACK
#ifdef WIN32
	reg_usb_ep_ctrl(USB_EDP_SOMATIC_IN) = 0;			// clear busy flag
#endif
    return 1;
}

int usbsomatic_hid_report_type(int report_id){
	return 0;
}

void usbsomatic_handle_outdata(void *data){
}

void usbsomatic_proc(somatic_sensor_data_t *data){
//	memcpy4(&somatic_data, data, sizeof(somatic_sensor_data_t));
}
void usbsomatic_handle_host_resp(rf_packet_somatic_resp_to_host_t *ele){
}

void usbsomatic_init(){
	
	static ev_event_t report_ev = {usbsomatic_handle_outdata};
	ev_on_event(EV_USB_OUT_DATA, &report_ev);

//	static ev_event_t report_ev = {usbsomatic_handle_set_report};
//	ev_on_event(EV_USB_SET_REPORT, &report_ev);
	
//	static ev_time_event_t somatic_timer = {usbsomatic_test_report};
//	ev_on_timer(&somatic_timer, 1000*1000);
}
#endif
