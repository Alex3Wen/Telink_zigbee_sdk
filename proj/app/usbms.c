
#if 0
#if (USB_MASS_STORAGE_ENABLE)
void usb_prepare_configuration_data(void) {
	*g_response = USB_DEVICE_CONFIG_NUM;
	g_response_len = sizeof(u8);

	if (control_request.wLength < g_response_len) {
		g_response_len = control_request.wLength;
	}

	return;
}
void usb_handle_set_configuration(void) {
/*
1、配置描述符变动
2、重新定义端点? USB_ENDPOINT_MS_IN ...
3、重新定义中断? usb_init_interrupt 
......
*/
	return;
}
#endif
#if 0
#if (USB_MASS_STORAGE_ENABLE)
		else if (REQ_GetConfiguration == request_cmd) {
			if (USB_IRQ_SETUP_REQ == data_request) {
				usb_prepare_configuration_data();// debug note: 可以吗 usb_init_interrupt -->usbhw_disable_interrupt 没有 get_cfg
			}
			usb_send_response();
		}
#endif
#if (USB_MASS_STORAGE_ENABLE)
	case (REQDIR_HOSTTODEVICE | REQTYPE_STANDARD | REQREC_DEVICE):
		if (REQ_SetConfiguration == request_cmd) {
			usb_handle_set_configuration();
		}
		break;
#endif
#endif
#endif

