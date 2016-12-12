#include "../config/user_config.h"
#include "usbaud.h"
#include "../mcu/register.h"
#include "../drivers/usbhw.h"
#include "../drivers/usbhw_i.h"
#include "../drivers/usb.h"
#include "../usbstd/audioClassCommon.h"

/*************************************************
 * g_audio_hid_chg:
 * 		0x00: no event
 * 		0x01: speaker volume change
 * 		0x02: speaker mute change
 * 		0x11: microphone volume change
 * 		0x12: microphone mute change
 *************************************************/

typedef struct {
	u16 vol_cur;
	u16	vol_step;
	u8 	mute;
}speaker_setting_t;
static speaker_setting_t speaker_setting;

typedef struct {
	u16 vol_cur;
	u8 	mute;
}mic_setting_t;
static mic_setting_t mic_setting;

void usbaud_set_audio_mode(int iso_en, int mono_en) {
    assert(USB_EDP_MIC < 8);
	SET_FLD(reg_usb_ep_ctrl(USB_EDP_MIC), FLD_USB_EP_EOF_ISO | FLD_USB_EP_MONO);
}
#if(0)	//  use for volumn control, mute, next, prev track,  move to mouse hid
void usbaud_hid_report(u8 cmd, u8 vol){
	if (usbhw_is_ep_busy(USB_EDP_AUDIO))
		return;
	reg_usb_ep_ptr(USB_EDP_AUDIO) = 0;
	
	// please refer to keyboard_report_desc
	reg_usb_ep_dat(USB_EDP_AUDIO) = USB_HID_AUDIO;
	reg_usb_ep_dat(USB_EDP_AUDIO) = cmd;
	reg_usb_ep_dat(USB_EDP_AUDIO) = vol;
	
	reg_usb_ep_ctrl(USB_EDP_AUDIO) = FLD_EP_DAT_ACK;		// ACK
}

u8 usbaud_handle_report(u8 c) {
	if (USB_REPORT_NO_EVENT == c) {
		return USB_REPORT_NO_EVENT;
	}
    assert(USB_EDP_AUDIO < 8);
	if(reg_usb_ep_ctrl(USB_EDP_AUDIO) & FLD_USB_EP_BUSY)
		return c;

	if(USB_REPORT_RELEASE == c){
		usbaud_hid_report(0, 0);
		return USB_REPORT_NO_EVENT;
	}else{
		usbaud_hid_report((c < 0x10) ? (1 << c) : 0
			,(c < 0x10) ? 0 : (1 << (c & 0x0f)));
		return USB_REPORT_RELEASE;
	}
}
#endif

static u16 usbaud_cal_speaker_step(u16 vol){
	if(vol < SPEAKER_VOL_MIN) 
		return 0;
	return ((vol - SPEAKER_VOL_MIN)	* (AUDIO_VOLUME_STEP_MAX - 1)) / (SPEAKER_VOL_MAX - SPEAKER_VOL_MIN);
}

void usbaud_set_speaker_vol(u16 vol){
	speaker_setting.vol_cur = vol;
	speaker_setting.vol_step = usbaud_cal_speaker_step(vol);
}
	
void usbaud_set_mic_vol(u16 vol){
	mic_setting.vol_cur = vol;
}
		
// return -1 on fail,  0 on success
int usbaud_handle_set_speaker_cmd(int type) {
	if(type == AUDIO_FEATURE_MUTE){
		speaker_setting.mute = usbhw_read_ctrl_ep_data();
	}else if(type == AUDIO_FEATURE_VOLUME){
		u16 val = usbhw_read_ctrl_ep_u16();
		usbaud_set_speaker_vol(val);
	}else{
		return -1;
	}
	return 0;
}
// return -1 on fail,  0 on success
int usbaud_handle_set_mic_cmd(int type) {
	if(type == AUDIO_FEATURE_MUTE){
		mic_setting.mute = usbhw_read_ctrl_ep_data();
	}else if(type == AUDIO_FEATURE_VOLUME){
		u16 val = usbhw_read_ctrl_ep_u16();
		usbaud_set_mic_vol(val);
	}else{
	}
	return 0;
}

// return -1 on fail,  0 on success
int usbaud_handle_get_speaker_cmd(int req, int type) {
	if(type == AUDIO_FEATURE_MUTE){
		usbhw_write_ctrl_ep_data(speaker_setting.mute);
	}else if(type == AUDIO_FEATURE_VOLUME){
		switch (req) {
			case AUDIO_REQ_GetCurrent:
				usbhw_write_ctrl_ep_u16(speaker_setting.vol_cur);
				break;
			case AUDIO_REQ_GetMinimum:
				usbhw_write_ctrl_ep_u16(SPEAKER_VOL_MIN);
				break;
			case AUDIO_REQ_GetMaximum:
				usbhw_write_ctrl_ep_u16(SPEAKER_VOL_MAX);
				break;
			case AUDIO_REQ_GetResolution:
				usbhw_write_ctrl_ep_u16(SPEAKER_VOL_RES);
				break;
			default:
				return -1;
		}
	}else{
		return -1;
	}
	return 0;
}

// return -1 on fail,  0 on success
int usbaud_handle_get_mic_cmd(int req, int type) {
	if(type == AUDIO_FEATURE_MUTE){
		usbhw_write_ctrl_ep_data(mic_setting.mute);
	}else if(type == AUDIO_FEATURE_VOLUME){
		switch (req) {
			case AUDIO_REQ_GetCurrent:
				usbhw_write_ctrl_ep_u16(mic_setting.vol_cur);
				break;
			case AUDIO_REQ_GetMinimum:
				usbhw_write_ctrl_ep_u16(MIC_VOL_MIN);
				break;
			case AUDIO_REQ_GetMaximum:
				usbhw_write_ctrl_ep_u16(MIC_VOL_MAX);
				break;
			case AUDIO_REQ_GetResolution:
				usbhw_write_ctrl_ep_u16(MIC_VOL_RES);
				break;
			default:
				return -1;
		}
	}else{
		return -1;
	}
	return 0;
}
void usbaud_init(void) {
	if (USB_MIC_ENABLE && 1 == MIC_CHANNLE_COUNT) {
		usbaud_set_audio_mode(1, 1);
	}
#if (USB_SPEAKER_ENABLE)
	usbaud_set_speaker_vol(SPEAKER_VOL_DEF);
#endif
#if (USB_MIC_ENABLE)
	mic_setting.vol_cur = MIC_VOL_DEF;
#endif
}

