
#include "../tl_common.h"
#if(USB_MOUSE_ENABLE)

#include "usbmouse.h"
#include "../drivers/mouse.h"
#include "../drivers/keyboard.h"
#include "../drivers/usb.h"
#include "../drivers/usbhw.h"
#include "../drivers/usbhw_i.h"
#include "../os/ev.h"
#include "../os/sys.h"

#define MOUSE_FRAME_DATA_NUM          4
#define MOUSE_FRAME_NUM_SAFE_GAP    4
#define USBMOUSE_BUFF_DATA_NUM      8
static mouse_data_t mouse_dat_buff[USBMOUSE_BUFF_DATA_NUM];

static u8  usbmouse_wptr, usbmouse_rptr;
static u8  usbmouse_newest_idx = -1;
#if 0
void usbmouse_add_frame (rf_packet_mouse_t *packet_mouse){
    u8 odi = packet_mouse->odi;
    u8 cnt = packet_mouse->cnt;
	u8 ods = odi & (MOUSE_FRAME_DATA_NUM - 1);
    /*
        dongle端的mouse_newest_num，表示已经记录到第n个mouse data
        odi 表示mouse data采样的index，从0~255循环，在pkt里面4个mouse data填充完之前是0，之后++
        ods表示rf_packet_mouse_t里面4个mouse-data最老的一个的index
        PKT_MOUSE_SAFE_GAP表示丢包容错门限为 255-MOUSE_FRAME_NUM_SAFE_GAP
        if(*(u32*)(&packet_mouse->data[ods])) 是为了处理刚开始4个mouse data没有填充满的情况
    */
    for(int i = 0; i < cnt; ++i,++odi){
        if((u8)(usbmouse_newest_idx - odi) > MOUSE_FRAME_NUM_SAFE_GAP){ 
            // push data
            usbmouse_newest_idx = odi;
			
			memcpy4((int*)(&mouse_dat_buff[usbmouse_wptr]), (int*)(&packet_mouse->data[ods]), sizeof(mouse_data_t));
            BOUND_INC_POW2(usbmouse_wptr,USBMOUSE_BUFF_DATA_NUM);
            if(usbmouse_wptr == usbmouse_rptr){
                BOUND_INC_POW2(usbmouse_rptr,USBMOUSE_BUFF_DATA_NUM);
            }
        }
        BOUND_INC_POW2(ods,MOUSE_FRAME_DATA_NUM);
    }
}
#endif
static u32 usbmouse_not_released;
static u32 usbmouse_data_report_time;
void usbmouse_release_check(){
	if(usbmouse_not_released && clock_time_exceed(usbmouse_data_report_time, USB_MOUSE_RELEASE_TIMEOUT)){
	    u32 release_data = 0;
	    if(usbmouse_hid_report(USB_HID_MOUSE, (u8*)(&release_data), MOUSE_REPORT_DATA_LEN)){
		    usbmouse_not_released = 0;
	    }
	}
}

// mouse_send_frame_usb()
void usbmouse_report_frame(){
	if(usbmouse_wptr != usbmouse_rptr){
        u32 data = *(u32*)(&mouse_dat_buff[usbmouse_rptr]);	// that is   >  0
        int ret = usbmouse_hid_report(USB_HID_MOUSE,(u8*)(&data), MOUSE_REPORT_DATA_LEN);
		
		if(ret){
		    //next frame when frame send, or frame no data
            BOUND_INC_POW2(usbmouse_rptr,USBMOUSE_BUFF_DATA_NUM);
		}
		if(0 == data && ret){			//  successfully  release the key
			usbmouse_not_released = 0;
		}else{
			usbmouse_not_released = 1;
			usbmouse_data_report_time = clock_time();
		}
	}
	return;
}

//  data 为MOUSE_REPORT_DATA_LEN个byte
int usbmouse_hid_report(u8 report_id, u8 *data, int cnt){
	if(usb_has_suspend_irq || sys_stat_ctrl.host_suspend_mode){		//  do not report anything when in suspend. Maybe not unnecessary
		return 1;
	}
	if(usbhw_is_ep_busy(USB_EDP_MOUSE))
		return 0;

	reg_usb_ep_ptr(USB_EDP_MOUSE) = 0;

	// please refer to usbmouse_i.h mouse_report_desc
	reg_usb_ep_dat(USB_EDP_MOUSE) = report_id;
	foreach(i, cnt){
	    reg_usb_ep_dat(USB_EDP_MOUSE) = data[i];
	}
	
	reg_usb_ep_ctrl(USB_EDP_MOUSE) = FLD_EP_DAT_ACK;		// ACK
#ifdef WIN32
	reg_usb_ep_ctrl(USB_EDP_MOUSE) = 0;			// clear busy flag
#endif
    return 1;
}

void usbmouse_init(){
	ev_on_poll(EV_POLL_MOUSE_REPORT, usbmouse_report_frame);
	ev_on_poll(EV_POLL_MOUSE_RELEASE_CHECK, usbmouse_release_check);
}

#endif
