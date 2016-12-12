
#pragma once

#include "usbsomatic.h"
#include "../drivers/usbhw.h"
#include "../drivers/usbhw_i.h"

#if(USB_SOMATIC_ENABLE)
//  just test
static const USB_Descriptor_HIDReport_Datatype_t somatic_report_desc[] = {
    HID_RI_USAGE_PAGE(8, 0x0c),             //global, usage page (follow 1 bytes) consumer page
    HID_RI_USAGE(8, 0x3c),                  //motion wakeup
    HID_RI_COLLECTION(8, 0x01),             //main, collection
    HID_RI_REPORT_ID(8, USB_HID_SOMATIC),   //Report ID
        
    HID_RI_REPORT_SIZE(8, 0x08),            //global, report size 16 bits
    HID_RI_REPORT_COUNT(8, 0x01),           //global, report count 2
    HID_RI_LOGICAL_MINIMUM(8, 0x00),        //global, min  0x00
    HID_RI_LOGICAL_MAXIMUM(8, 0xff),     //global, max  0xff

    
    HID_RI_END_COLLECTION(0),               //main, end collection
};

static inline u8* usbsomatic_get_report_desc(void) {
	return (u8*) (somatic_report_desc);
}

static inline u16 usbsomatic_get_report_desc_size(void) {
	return sizeof(somatic_report_desc);
}
#endif
