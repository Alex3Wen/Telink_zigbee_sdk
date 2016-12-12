#pragma once

#include "../common/types.h"
#include "../common/static_assert.h"
#include "../common/bit.h"
#include "../usbstd/HIDReportData.h"
#include "../usbstd/HIDClassCommon.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
	extern "C" {
#endif

#define SOMATIC_REPORT_DATA_LEN     (sizeof(somatic_sensor_data_t))

int usbsomatic_hid_report(u8 *data, u8 len);
//void usbsomatic_proc(somatic_sensor_data_t *data);
/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
	}
#endif

