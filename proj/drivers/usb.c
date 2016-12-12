#include "../tl_common.h"

#if (MODULE_USB_ENABLE)

#include "usb.h"
#include "usbdesc.h"
#include "../os/ev.h"
#include "../os/sys.h"
#include "../usbstd/StdRequestType.h"
#include "../app/usbaud.h"
#include "../app/usbkb.h"
#include "../app/usbmouse.h"
#include "usbhw.h"				// inline
#include "usbhw_i.h"


#if (USB_MOUSE_ENABLE)
#include "../app/usbmouse_i.h"
#endif

#if (USB_KEYBOARD_ENABLE)
#include "../app/usbkb_i.h"
#endif

#if (USB_SOMATIC_ENABLE)
#include "../app/usbsomatic_i.h"
#include "somatic_sensor.h"
#endif

#if (USB_SPEAKER_ENABLE || USB_MIC_ENABLE)
#include "../app/usbaud_i.h"
#endif

#if (USB_CDC_ENABLE)
#include "../app/usbcdc.h"
#endif

#ifdef WIN32
#include <stdio.h>
#endif

u8		host_keyboard_status;
u8		host_cmd[8];
u8		host_cmd_paring_ok = 0;
static USB_Request_Header_t control_request;
static u8 * g_response = 0;
static u16 g_response_len = 0;
static int g_stall = 0;
u8 usb_mouse_report_proto = 0; //default 1 for report proto
u8 g_rate = 0; //default 0 for all report

#if (USB_SPEAKER_ENABLE || USB_MIC_ENABLE)
u8 usb_alt_intf[USB_INTF_MAX];
#endif
void usb_send_response(void) {
	u16 n;
#ifdef WIN32
	n = g_response_len;
#else
	if (g_response_len < 8) {
		n = g_response_len;
	} else {
		n = 8;
	}
	g_response_len -= n;
#endif
	usbhw_reset_ctrl_ep_ptr();
	while (n-- > 0) {
		usbhw_write_ctrl_ep_data(*g_response);
		++g_response;
	}
}

void usb_prepare_desc_data(void) {
	u8 value_l = (control_request.wValue) & 0xff;
	u8 value_h = (control_request.wValue >> 8) & 0xff;

	g_response = 0;
	g_response_len = 0;

	switch (value_h) {
		
	case DTYPE_Device:
		g_response = usbdesc_get_device();
		g_response_len = sizeof(USB_Descriptor_Device_t);
		break;

	case DTYPE_Configuration:
		g_response = usbdesc_get_configuration();
		g_response_len = sizeof(USB_Descriptor_Configuration_t);
		break;

	case DTYPE_String:
		if (USB_STRING_LANGUAGE == value_l) {
			g_response = usbdesc_get_language();
			g_response_len = sizeof(LANGUAGE_ID_ENG);
		} else if (USB_STRING_VENDOR == value_l) {
			g_response = usbdesc_get_vendor();
			g_response_len = sizeof(STRING_VENDOR);
		} else if (USB_STRING_PRODUCT == value_l) {
			g_response = usbdesc_get_product();
			g_response_len = sizeof(STRING_PRODUCT);
		} else if (USB_STRING_SERIAL == value_l) {
			g_response = usbdesc_get_serial();
			g_response_len = sizeof(STRING_SERIAL);

#if (MS_OS_DESCRIPTOR_ENABLE)
		} else if (USB_STRING_MS_OS == value_l) {
			g_response = usbdesc_get_OS_descriptor();
			g_response_len = sizeof(STRING_MSFT);
#endif

		} else {
			g_stall = 1;
		}
		break;

	default:
		g_stall = 1;
		break;

	}

	if (control_request.wLength < g_response_len) {
		g_response_len = control_request.wLength;
	}

	return;
}

//standard interface request handle
void usb_handle_std_intf_req() {
	u8 value_h = (control_request.wValue >> 8) & 0xff;
#if(USB_MIC_ENABLE || USB_SPEAKER_ENABLE || USB_MOUSE_ENABLE || USB_KEYBOARD_ENABLE || USB_SOMATIC_ENABLE)
	u8 index_l = (control_request.wIndex) & 0xff;
#endif
	switch (value_h) {
	case HID_DTYPE_HID:// HID Descriptor
#if(0)
		if (index_l == USB_INTF_AUDIO_HID) {
			//audio hid
			g_response = usbdesc_get_audio();
			g_response_len = sizeof(USB_HID_Descriptor_HID_Audio_t);
		}
#endif		
#if(USB_MOUSE_ENABLE )
		if (index_l == USB_INTF_MOUSE) //index_l is the interface number
		{
			//mouse
			g_response = usbdesc_get_mouse();
			g_response_len = sizeof(USB_HID_Descriptor_HID_Mouse_t);
		}
#endif
#if(USB_KEYBOARD_ENABLE)
		if (index_l == USB_INTF_KEYBOARD) {
			//keyboard
			g_response = usbdesc_get_keyboard();
			g_response_len = sizeof(USB_HID_Descriptor_HID_Keyboard_t);
		}
#endif
#if(USB_SOMATIC_ENABLE )
		if (index_l == USB_INTF_SOMATIC) //index_l is the interface number
		{
			//SOMATIC
			g_response = usbdesc_get_somatic();
			g_response_len = sizeof(USB_HID_Descriptor_HID_Somatic_t);
		}
#endif
		break;
	case HID_DTYPE_Report://Report Descriptor
#if (0)
		if (index_l == USB_INTF_AUDIO_HID) {
			//audio hid
			g_response = usbaud_get_report_desc();
			g_response_len = usbaud_get_report_desc_size();
		}
#endif		
#if(USB_MOUSE_ENABLE)
		if (index_l == USB_INTF_MOUSE) {
			//mouse
			g_response = (u8*) usbmouse_get_report_desc();
			g_response_len = usbmouse_get_report_desc_size();
		}
#endif
#if(USB_KEYBOARD_ENABLE)
		if (index_l == USB_INTF_KEYBOARD) {
			//keyboard
			g_response = (u8*) usbkb_get_report_desc();
			g_response_len = usbkb_get_report_desc_size();
		}
#endif
#if(USB_SOMATIC_ENABLE)
		if (index_l == USB_INTF_SOMATIC) {
			//somatic sensor
			g_response = (u8*) usbsomatic_get_report_desc();
			g_response_len = usbsomatic_get_report_desc_size();
		}
#endif
		break;
	case 0x23:// Phisical Descriptor
		// TODO
		break;

	default:// other condition
		break;
	}

	if (control_request.wLength < g_response_len) { 
		g_response_len = control_request.wLength;
	}

	return;
}

void usb_handle_out_class_intf_req(int data_request) {
	u8 property = control_request.bRequest;
	u8 value_l = (control_request.wValue) & 0xff;
	u8 value_h = (control_request.wValue >> 8) & 0xff;
#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	u8 Entity = (control_request.wIndex >> 8) & 0xff;
#endif

	switch (property) {

	case HID_REQ_SetReport:
		switch (value_h) {
		case HID_REPORT_ITEM_In:
			break;
		case HID_REPORT_ITEM_Out:
			// usb_hid_set_report_ouput();
			break;
		case HID_REPORT_ITEM_Feature:
			if (data_request) {
				host_keyboard_status = usbhw_read_ctrl_ep_data();
			}
#if(USB_SET_REPORT_FEATURE_SUPPORT)			
		{
			usb_set_report_t rpt;
			rpt.report_id = value_l;
			rpt.len = control_request.wIndex;
			ev_emit_event_syn(EV_USB_SET_REPORT, (void*)(&rpt));	// send in report id
		}
#endif
			break;
		case HID_REPORT_CUSTOM:
#if (USB_CUSTOM_HID_REPORT)
		{	//Paring, EMI-TX, EMI-RX
			if (data_request) {
				int i=0;
				usbhw_reset_ctrl_ep_ptr (); //address
				for(i=0;i<8;i++)
					host_cmd[i] = usbhw_read_ctrl_ep_data();
			}
			break;
		}
#endif
		default:
			g_stall = 1;
			break;
		}
		break;

	case HID_REQ_SetIdle:
		if (data_request) {
			g_rate = usbhw_read_ctrl_ep_data();
		}
		g_rate = value_h;
		break;

	case HID_REQ_SetProtocol:
		if (data_request) {
			usb_mouse_report_proto = usbhw_read_ctrl_ep_data();
		}
		usb_mouse_report_proto = value_l;
		break;


#if (USB_CDC_ENABLE)
    case CDC_REQ_SetControlLineState:
	case CDC_REQ_SetLineEncoding:
        CDC_Device_ProcessControlRequest(control_request.bRequest, control_request.wValue, control_request.wIndex, control_request.wLength);
        break;
#endif
	default:
		g_stall = 1;
		break;
	}

#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	if(0 == g_stall){		// already handled
		return;
	}
	g_stall = 0;
	switch(Entity){
		case USB_SPEAKER_FEATURE_UNIT_ID:
			usbaud_handle_set_speaker_cmd(value_h);
			break;
		case USB_MIC_FEATURE_UNIT_ID:
			usbaud_handle_set_mic_cmd(value_h);
			break;
		default:
			g_stall = 1;
			break;
	}
#endif
}

#if (USB_CDC_ENABLE)
extern void CDC_Device_ProcessControlRequest(u8 bRequest, u16 wValue, u16 wIndex, u16 wLength);
#endif
void usb_handle_in_class_intf_req() {
	u8 property = control_request.bRequest;
#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	u8 value_h = (control_request.wValue >> 8);
	u8 Entity = (control_request.wIndex >> 8);
#endif
	switch (property) {
		case 0x00:
			usbhw_write_ctrl_ep_data(0x00);
			break;
		case HID_REQ_GetReport:
#if(USB_SOMATIC_ENABLE)
			if(usbsomatic_hid_report_type((control_request.wValue & 0xff))){
			}
			else
#elif (USB_CUSTOM_HID_REPORT)
			if( control_request.wValue==0x0305 ) {
				usbhw_write_ctrl_ep_data (0x04);
				usbhw_write_ctrl_ep_data (0x58);
				usbhw_write_ctrl_ep_data (0x00);
				usbhw_write_ctrl_ep_data (host_cmd_paring_ok ? 0xa1 : 0x00);  //For binding OK
				usbhw_write_ctrl_ep_data (0x00);
				usbhw_write_ctrl_ep_data (0x00);
				usbhw_write_ctrl_ep_data (0x08);
				usbhw_write_ctrl_ep_data (0x00);
			}
			else
#endif			
			{	//  donot know what is this
	//			usbhw_write_ctrl_ep_data(0x81);
	//			usbhw_write_ctrl_ep_data(0x02);
	//			usbhw_write_ctrl_ep_data(0x55);
	//			usbhw_write_ctrl_ep_data(0x55);
			}
			break;
		case HID_REQ_GetIdle:
			usbhw_write_ctrl_ep_data(g_rate);
			break;
		case HID_REQ_GetProtocol:
			usbhw_write_ctrl_ep_data(usb_mouse_report_proto);
			break;
#if (USB_CDC_ENABLE)
        case CDC_REQ_GetLineEncoding:

		    CDC_Device_ProcessControlRequest(control_request.bRequest, control_request.wValue, control_request.wIndex, control_request.wLength);
		    break;
#endif
		default:
			g_stall = 1;
			break;
	}
#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	if(0 == g_stall){		// already handled
		return;
	}
	g_stall = 0;
	switch(Entity){
		case USB_SPEAKER_FEATURE_UNIT_ID:
			if(usbaud_handle_get_speaker_cmd(property, value_h)){
				g_stall = 1;
			}
			break;
		case USB_MIC_FEATURE_UNIT_ID:
			if(usbaud_handle_get_mic_cmd(property, value_h)){
				g_stall = 1;
			}
			break;
		default:
			g_stall = 1;
			break;
	}
#endif
	
}

void usb_handle_in_class_endp_req() {
	u8 property = control_request.bRequest;
	u8 ep_ctrl = control_request.wValue >> 8;
#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	u8 addr = (control_request.wIndex >> 8);
#endif
	if(ep_ctrl == AUDIO_EPCONTROL_SamplingFreq){
		switch(property){
		case AUDIO_REQ_GetCurrent:
			usbhw_write_ctrl_ep_data(MIC_SAMPLE_RATE & 0xff);
			usbhw_write_ctrl_ep_data(MIC_SAMPLE_RATE >> 8);
			usbhw_write_ctrl_ep_data(MIC_SAMPLE_RATE >> 16);
			break;
		default:
			break;
		}
	}
	
}

void usb_handle_out_class_endp_req(int data_request) {
	return;
#if 0	
	u8 property = control_request.bRequest;
	u8 ep_ctrl = control_request.wValue & 0xff;
#if (USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	u8 addr = (control_request.wIndex >> 8);
#endif
#endif
}


void usb_handle_set_intf() {
#if (USB_SPEAKER_ENABLE || USB_MIC_ENABLE)
	u8 value_l = (control_request.wValue) & 0xff;
	u8 intf_index = (control_request.wIndex) & 0x07;
	assert(intf_index < USB_INTF_MAX);
	usb_alt_intf[intf_index] = value_l;

#if (USB_MIC_ENABLE)
	if(USB_INTF_MIC == intf_index && value_l){
		usbhw_reset_ep_ptr(USB_EDP_MIC);
		reg_usb_ep_ptr(USB_EDP_MIC) = USB_MIC_CHANNELS_LEN;
		reg_usb_ep_ctrl(USB_EDP_MIC) = (MIC_CHANNLE_COUNT == 2 ? 0x81 : 0xc1);
	}
#endif

#endif
	return;
}

#if (USB_SPEAKER_ENABLE || USB_MIC_ENABLE)
void usb_handle_get_intf() {
	u8 intf_index = (control_request.wIndex) & 0x07;
	assert(intf_index < USB_INTF_MAX);

	usbhw_write_ctrl_ep_data(usb_alt_intf[intf_index]);

	return;
}
#endif

void usb_handle_request(u8 data_request) {
	u8 bmRequestType = control_request.bmRequestType;
	u8 bRequest = control_request.bRequest;

#ifdef WIN32
	printf("\r\nusb_sim:s:");
#endif

	usbhw_reset_ctrl_ep_ptr();
	switch (bmRequestType) {
	case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_DEVICE):
		if (REQ_GetDescriptor == bRequest) {
			if (USB_IRQ_SETUP_REQ == data_request) {
				usb_prepare_desc_data();
			}
			usb_send_response();
		} 
		break;

	case (REQDIR_DEVICETOHOST | REQTYPE_STANDARD | REQREC_INTERFACE):
		if (REQ_GetDescriptor == bRequest) {
			if (USB_IRQ_SETUP_REQ == data_request) {
				usb_handle_std_intf_req();
			}
			usb_send_response();
		}
#if (USB_SPEAKER_ENABLE || USB_MIC_ENABLE)
		else if (REQ_GetInterface == bRequest) {
			usb_handle_get_intf();
		}
#endif
		break;
#if (MS_OS_DESCRIPTOR_ENABLE)
	case (REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQREC_DEVICE):
	case (REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQREC_INTERFACE):
		 if ((bRequest ==  MS_VENDORCODE)) {//Retrieve an OS Feature Descriptor
			u8 index_l = control_request.wIndex&0xff;
			if (USB_IRQ_SETUP_REQ == data_request) {
				//usb_indexl==0x04 for Extended compat ID
				//usb_indexl==0x05 for Extended properties
				if(index_l==0x04 )
				{
					g_response = usbdesc_get_compatID(&g_response_len);
				}
				else if(index_l==0x05)
				{
					g_response = usbdesc_get_OSFeature(&g_response_len);
				}
				else
					g_stall = 1;
				if (control_request.wLength < g_response_len) {
					g_response_len = control_request.wLength;
				}
			}

			usb_send_response();
		}
		break;
#endif
	case (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_INTERFACE):
		usb_handle_out_class_intf_req(data_request);
		break;
	case (REQDIR_HOSTTODEVICE | REQTYPE_CLASS | REQREC_ENDPOINT):
		usb_handle_out_class_endp_req(data_request);
		break;
	case (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE):
		usb_handle_in_class_intf_req();
		break;
	case (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_ENDPOINT):
		usb_handle_in_class_endp_req();
		break;

	case (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_INTERFACE):
		if (REQ_SetInterface == bRequest) {
			usb_handle_set_intf();
		}
		break;
		
	default:
		g_stall = 1;
		break;
	}

	return;
}

void usb_handle_ctl_ep_setup() {
	usbhw_reset_ctrl_ep_ptr();
	control_request.bmRequestType = usbhw_read_ctrl_ep_data();
	control_request.bRequest = usbhw_read_ctrl_ep_data();
	control_request.wValue = usbhw_read_ctrl_ep_u16();
	control_request.wIndex = usbhw_read_ctrl_ep_u16();
	control_request.wLength = usbhw_read_ctrl_ep_u16();
	g_stall = 0;
	usb_handle_request(USB_IRQ_SETUP_REQ);
	if (g_stall)
		usbhw_write_ctrl_ep_ctrl(FLD_EP_DAT_STALL);
	else
		usbhw_write_ctrl_ep_ctrl(FLD_EP_DAT_ACK);
}

void usb_handle_ctl_ep_data(void) {
	usbhw_reset_ctrl_ep_ptr();
	g_stall = 0;
	usb_handle_request(USB_IRQ_DATA_REQ);
	if (g_stall)
		usbhw_write_ctrl_ep_ctrl(FLD_EP_DAT_STALL);
	else
		usbhw_write_ctrl_ep_ctrl(FLD_EP_DAT_ACK);
}

void usb_handle_ctl_ep_status() {
	if (g_stall)
		usbhw_write_ctrl_ep_ctrl(FLD_EP_STA_STALL);
	else
		usbhw_write_ctrl_ep_ctrl(FLD_EP_STA_ACK);
}

u8 usb_has_suspend_irq = 0;
u8  usb_just_wakeup_from_suspend = 1;
extern u8 rf_channel;
int usb_suspend_check(void){
	static u8 usb_suspend_allow = 0;
	static u8 usb_suspend_time_init = 0;
	
	static u32 usb_power_start_time = 0;
	static u32 usb_suspend_start_time = 0;

	if (!usb_suspend_time_init){
		usb_power_start_time = clock_time();
		usb_suspend_time_init = 1;
	}
	if((!usb_suspend_allow) && clock_time_exceed(usb_power_start_time, USB_TIME_BEFORE_ALLOW_SUSPEND)){
		usb_suspend_allow = 1;
	}
	if(usb_has_suspend_irq && usb_suspend_allow){
		
		sys_enter_host_suspend_mode();

		if(usb_just_wakeup_from_suspend){
			usb_suspend_start_time = clock_time();
			rf_set_rx_mode(1);
			usb_just_wakeup_from_suspend = 0;
		}
		if(clock_time_exceed(usb_suspend_start_time, (PM_USB_WAKEUP_TIME * 1000))){		//  10ms
			usb_just_wakeup_from_suspend = 1;
			rf_set_tx_mode(1);
			return 1;
		}
	}else{
		sys_exit_host_suspend_mode();
	}
	return 0;

}

void usb_resume_host(void)
{
#if (MCU_CORE_TYPE == MCU_CORE_3520)
#else
	reg_wakeup_en = FLD_WAKEUP_SRC_USB_RESM;
	reg_wakeup_en = 0;
#endif
	sleep_us(6000);
}

#define USB_BULK_TRANSFER_ENABLE    1
#if(USB_BULK_TRANSFER_ENABLE)
u16 bulkin_target_addr;
u16 bulkin_data_len = 0;
u8 *bulkin_write_ptr = 0;

u16 bulkout_target_addr;
u16 bulkout_data_len = 0;
u16 bulkout_max_pkt_len = 0;
u8  bulkout_cmd_start = 1;
u8 *bulkout_write_ptr = 0;

#define USB_BULK_MAX_PKT_SIZE     64


u8 usb_bulk_data_out() {

    u8 cmd = 0, i;
    usbhw_reset_ep_ptr(USB_EDP_PRINTER_OUT);

    bulkout_max_pkt_len = USB_BULK_MAX_PKT_SIZE;
    if(bulkout_cmd_start){
        cmd = usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
        // ¡À¡ê3??¨²¨®2?t¦Ì??¨¢D¡äD-¨°¨¦¨°???, 0x02, write,  0x03, read
        if(0x02 == cmd){                // skip fixed byte 0x02
            bulkout_target_addr = (usbhw_read_ep_data(USB_EDP_PRINTER_OUT) << 8);    // big endian in this case
            bulkout_target_addr += usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            bulkout_data_len = usbhw_read_ep_data(USB_EDP_PRINTER_OUT) << 8;
            bulkout_data_len += usbhw_read_ep_data(USB_EDP_PRINTER_OUT);

//            if(bulkout_data_len > TL_USB_PACKET_BUF_SIZE){                    // mod to more precise condition
//                g_stall = 1;
//                return 0;
//            }
            // skip 3 duplicate data
            usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            
            bulkout_write_ptr = (u8 *)(REG_BASE_ADDR + bulkout_target_addr);
            bulkout_max_pkt_len = (USB_BULK_MAX_PKT_SIZE - 8);
        }
        else if(0x03 == cmd){
            bulkin_target_addr = (usbhw_read_ep_data(USB_EDP_PRINTER_OUT) << 8);    // big endian in this case
            bulkin_target_addr += usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            bulkin_data_len = usbhw_read_ep_data(USB_EDP_PRINTER_OUT) << 8;
            bulkin_data_len += usbhw_read_ep_data(USB_EDP_PRINTER_OUT);

//            if(bulkin_data_len > TL_USB_PACKET_BUF_SIZE){                    // mod to more precise condition
//                g_stall = 1;
//                return 0;
//            }
            // skip 3 duplicate data
            usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            usbhw_read_ep_data(USB_EDP_PRINTER_OUT);
            bulkin_write_ptr = (u8 *)(REG_BASE_ADDR + bulkin_target_addr);
            return cmd;
        }else{
            return cmd;
        }
    }
    if(bulkout_data_len < bulkout_max_pkt_len){        // no more data
        bulkout_cmd_start = 1;                            // reset 
        i = bulkout_data_len;
        bulkout_data_len = 0;
    }else{
        bulkout_cmd_start = 0;
        i = bulkout_max_pkt_len;
        bulkout_data_len -= bulkout_max_pkt_len;
        if(0 == bulkout_data_len){                        //  all sent
            bulkout_cmd_start = 1;
        }
    }
    while(i -- ){
//        *bulkout_write_ptr = usbhw_read_ep_data(USB_EDP_PRINTER_OUT);    // !!!  fix me  !!!
        ++bulkout_write_ptr;
    }
    return cmd;

}
u16 usb_bulk_data_in() {
    u16 len = bulkin_data_len;
    if(len > USB_BULK_MAX_PKT_SIZE){
        len = USB_BULK_MAX_PKT_SIZE;
    }
    if(len > 0){
        usbhw_reset_ep_ptr(USB_EDP_PRINTER_IN);
        u32 i;
        for(i = 0; i < len; ++i){
            usbhw_write_ep_data(USB_EDP_PRINTER_IN, *bulkin_write_ptr);
            ++bulkin_write_ptr;
        }
    }
    bulkin_data_len -= len;
    return len;
}
#endif


volatile u8 t_usbCnt;
void usb_handle_irq(void) {
	u32 irq = usbhw_get_ctrl_ep_irq();
	if (irq & FLD_CTRL_EP_IRQ_SETUP) {
		usbhw_clr_ctrl_ep_irq(FLD_CTRL_EP_IRQ_SETUP);
		usb_handle_ctl_ep_setup();
	}
	if (irq & FLD_CTRL_EP_IRQ_DATA) {
		usbhw_clr_ctrl_ep_irq(FLD_CTRL_EP_IRQ_DATA);
		usb_handle_ctl_ep_data();
	}
	if (irq & FLD_CTRL_EP_IRQ_STA) {
		usbhw_clr_ctrl_ep_irq(FLD_CTRL_EP_IRQ_STA);
		usb_handle_ctl_ep_status();
	}
	if (reg_irq_src & FLD_IRQ_USB_RST_EN){		//USB reset
		usb_mouse_report_proto = 1;
		reg_irq_src3 = BIT(1);					//Clear USB reset flag
	}
	irq = reg_usb_irq;							// data irq
#if(USB_SOMATIC_ENABLE)		
	if(irq & BIT((USB_EDP_SOMATIC_OUT & 0x07))){
		reg_usb_irq = BIT((USB_EDP_SOMATIC_OUT & 0x07));		// clear ime
		usbhw_reset_ep_ptr(USB_EDP_SOMATIC_OUT);

		ev_emit_event_syn(EV_USB_OUT_DATA, (void*)irq);
		
		usbhw_data_ep_ack(USB_EDP_SOMATIC_OUT);
	}
#endif		
#if(USB_BULK_TRANSFER_ENABLE)
    u8 cmd = 0;
    u8 l;
#if (USB_CDC_ENABLE)
    g_stall = 0;
    if(irq & BIT((USB_EDP_CDC_OUT & 0x07))){
    	t_usbCnt++;
        reg_usb_irq = BIT((USB_EDP_CDC_OUT & 0x07));        // clear ime
        extern void usbcdc_recvData();
        usbcdc_recvData();
        usbhw_data_ep_ack(USB_EDP_CDC_OUT);
    }

	if(irq & BIT((USB_EDP_CDC_IN & 0x07))){
        reg_usb_irq = BIT((USB_EDP_CDC_IN & 0x07));        // clear ime
        extern u8 usbcdc_sendBulkData();
        l = usbcdc_sendBulkData();
		if (l > 0) {
            usbhw_data_ep_ack(USB_EDP_CDC_OUT);
		}
    }
        
#endif
#endif
	if(IRQ_USB_PWDN_ENABLE && (reg_irq_src & FLD_IRQ_USB_PWDN_EN)){
		usb_has_suspend_irq = 1;
	}else{
		usb_has_suspend_irq = 0;
	}

#if(USB_KEYBOARD_ENABLE && FLOW_NO_OS)
	extern void usbkb_release_check();
	usbkb_release_check();
#endif

#if(USB_MOUSE_ENABLE && FLOW_NO_OS)
	extern void usbmouse_report_frame();
	extern void usbmouse_release_check();
	usbmouse_report_frame();
	usbmouse_release_check();
#endif

}

void usb_init_interrupt() {
#if(USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	usbhw_enable_manual_interrupt(FLD_CTRL_EP_AUTO_STD | FLD_CTRL_EP_AUTO_DESC | FLD_CTRL_EP_AUTO_INTF);
#else
	usbhw_enable_manual_interrupt(FLD_CTRL_EP_AUTO_STD | FLD_CTRL_EP_AUTO_DESC);
#endif
#if(USB_SOMATIC_ENABLE)		
	BM_CLR(reg_usb_mask, BIT(USB_EDP_SOMATIC_OUT & 0x07));
	usbhw_data_ep_ack(USB_EDP_SOMATIC_OUT);
#endif

#if(USB_BULK_TRANSFER_ENABLE)

#if (USB_CDC_ENABLE)
    BM_CLR(reg_usb_mask, BIT(USB_EDP_CDC_IN & 0x07) | BIT(USB_EDP_CDC_OUT & 0x07));
    usbhw_data_ep_ack(USB_EDP_CDC_OUT);
#endif

#endif
}

void usb_init() {
#if USB_PRINTER_ENABLE	
	usbhw_set_printer_threshold(64);
#endif
#if(USB_MIC_ENABLE || USB_SPEAKER_ENABLE)
	usbaud_init();
#endif	
#if(USB_MOUSE_ENABLE && !FLOW_NO_OS)
    extern void usbmouse_init();
    usbmouse_init();
#endif	
#if(USB_KEYBOARD_ENABLE && !FLOW_NO_OS)
    extern void usbkb_init();
    usbkb_init();
#endif	
#if(USB_SOMATIC_ENABLE)
    extern void usbsomatic_init();
    usbsomatic_init();
#endif	
#if(USB_CDC_ENABLE)
    extern void usbcdc_init();
    usbcdc_init();
#endif
	usb_init_interrupt();
//#if FLOW_NO_OS
//#else
	ev_on_poll(EV_POLL_USB_IRQ, usb_handle_irq);
//#endif
}

unsigned short USB_CRC16 (unsigned char *pD, int len)
{

    static unsigned short poly[2]={0, 0xa001};              //0x8005 <==> 0xa001
    unsigned short crc = 0xffff;
    unsigned char ds;
    int i,j;

    for(j=len; j>0; j--)
    {
        unsigned char ds = *pD++;
        for(i=0; i<8; i++)
        {
            crc = (crc >> 1) ^ poly[(crc ^ ds ) & 1];
            ds = ds >> 1;
        }
    }

     return crc;
}

#endif
