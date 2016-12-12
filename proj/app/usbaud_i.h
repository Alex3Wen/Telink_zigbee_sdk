
#pragma once

#include "../config/user_config.h"
#include "usbaud.h"
#include "../mcu/register.h"
#include "../drivers/usbhw.h"
#include "../drivers/usbhw_i.h"
#include "../usbstd/audioClassCommon.h"

static const USB_Descriptor_HIDReport_Datatype_t usbaud_report_desc[] = {
	HID_RI_USAGE_PAGE(8, 0x0c), /* Consumer Page */
	HID_RI_USAGE(8, 0x01)		, /* Consumer Controls */
    HID_RI_COLLECTION(8, 0x01)		, /* Application */

    HID_RI_REPORT_ID(8, 0x01)		, /*Report ID*/

    HID_RI_LOGICAL_MINIMUM(8, 0x00)		,
    HID_RI_LOGICAL_MAXIMUM(8, 0x01),

    HID_RI_USAGE(8, 0xcd),  /* Play/Pause (toggle) */
	HID_RI_USAGE(8, 0xb5)		, /* Next Track */
	HID_RI_USAGE(8, 0xb6)		, /* Previous Track */
	HID_RI_USAGE(8, 0xb7)		, /* Stop */

    HID_RI_REPORT_SIZE(8, 0x01)		,
    HID_RI_REPORT_COUNT(8, 0x04),
    HID_RI_INPUT(8, HID_IOF_VARIABLE),
    HID_RI_LOGICAL_MINIMUM(8, 0x00),
    HID_RI_LOGICAL_MAXIMUM(8, 0x01),
    
    HID_RI_USAGE(8, 0xb0),  /* Play */
    HID_RI_USAGE(8, 0xb1)		, /* Pause */
    HID_RI_USAGE(8, 0xb3)		, /* Fast Forward */
    HID_RI_USAGE(8, 0xb4)		, /* Rewind */

    HID_RI_REPORT_SIZE(8, 0x01)		,
    HID_RI_REPORT_COUNT(8, 0x04),
    HID_RI_INPUT(8, HID_IOF_NO_PREFERRED_STATE | HID_IOF_VARIABLE),
    HID_RI_LOGICAL_MINIMUM(8, 0x00),
    HID_RI_LOGICAL_MAXIMUM(8, 0x01),
    HID_RI_USAGE(8, 0xe9),
    HID_RI_USAGE(8, 0xea),
    HID_RI_USAGE(8, 0xe2),
    HID_RI_REPORT_SIZE(8, 0x01),
    HID_RI_REPORT_COUNT(8, 0x03),
    HID_RI_INPUT(8, HID_IOF_NO_PREFERRED_STATE | HID_IOF_VARIABLE),
    HID_RI_REPORT_SIZE(8, 0x05),
    HID_RI_REPORT_COUNT(8, 0x01),
    HID_RI_INPUT(8, HID_IOF_CONSTANT),
    HID_RI_END_COLLECTION(0),
	HID_RI_USAGE_PAGE(16, 0xffa0),
    HID_RI_USAGE(8, 0x01),
    HID_RI_COLLECTION(8, 0x01),  /* Application */

    HID_RI_REPORT_ID(8, 0x02)		, /*Report ID*/

    HID_RI_USAGE(8, 0x01)		,
    HID_RI_LOGICAL_MINIMUM(8, 0x00),
	HID_RI_LOGICAL_MAXIMUM(16, 0x00ff),
    HID_RI_REPORT_SIZE(8, 0x08),
    HID_RI_REPORT_COUNT(8, 0x02),
    HID_RI_OUTPUT(8, HID_IOF_DATA),
    HID_RI_USAGE(8, 0x02),  /* mouse? */

    HID_RI_REPORT_SIZE(8, 0x08)		,
    HID_RI_REPORT_COUNT(8, 0x02),
    HID_RI_INPUT(8, HID_IOF_DATA),
    HID_RI_END_COLLECTION(0),  };

static inline u8* usbaud_get_report_desc(void) {
	return (u8*) (usbaud_report_desc);
}

static inline u16 usbaud_get_report_desc_size(void) {
	return sizeof(usbaud_report_desc);
}


