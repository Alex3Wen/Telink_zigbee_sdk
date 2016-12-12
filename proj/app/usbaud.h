#pragma once

#include "../common/types.h"
#include "../common/assert.h"
#include "../usbstd/HIDReportData.h"
#include "../usbstd/HIDClassCommon.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

// telink usb report ctrl command. used mixed with USB_REPORT_NO_EVENT
enum {
	USB_AUD_PLAY_PAUSE		= 0,
	USB_AUD_NEXT_TRACK		= 1,
	USB_AUD_PREV_TRACK		= 2,
	USB_AUD_STOP			= 3,
	USB_AUD_PLAY			= 4,
	USB_AUD_PAUSE			= 5,
	USB_AUD_FAST_FWD		= 6,
	USB_AUD_REWIND			= 7,
	USB_AUD_VOL_INC			= 0x10,
	USB_AUD_VOL_DEC			= 0x11,
	USB_AUD_VOL_MUTE 		= 0x12,
};

#define AUDIO_VOLUME_STEP_MAX  11

#define MIC_VOL_MIN			0x0000     /* Volume Minimum Value */
#define MIC_VOL_MAX			0x1f00     /* Volume Maximum Value */
#define	MIC_VOL_RES			0x0004     /* Volume Resolution */
#define MIC_VOL_DEF			0x1800     /* Volume default */

#define	SPEAKER_VOL_MIN		0x0000     /* Volume Minimum Value */
#define	SPEAKER_VOL_MAX		0x8000     /* Volume Maximum Value */
#define SPEAKER_VOL_RES		0x0004     /* Volume Resolution */
#define SPEAKER_VOL_DEF		0x8000     /* Volume default */

int usbaud_handle_set_speaker_cmd(int type);
int usbaud_handle_set_mic_cmd(int type);
int usbaud_handle_get_speaker_cmd(int req, int type);
int usbaud_handle_get_mic_cmd(int req, int type);
void usbaud_init(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

