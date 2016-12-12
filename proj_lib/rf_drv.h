
#pragma once

#if(MCU_CORE_TYPE == MCU_CORE_5320)
#include "rf_drv_5320.h"
#elif(MCU_CORE_TYPE == MCU_CORE_5328)
#include "rf_drv_5328.h"
#elif(MCU_CORE_TYPE == MCU_CORE_5332)
#include "rf_drv_5332.h"
#elif(MCU_CORE_TYPE == MCU_CORE_5330)
#include "rf_drv_5330.h"
#endif

