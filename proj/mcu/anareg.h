
#pragma once

#if(MCU_CORE_TYPE == MCU_CORE_5320)
#include "../mcu_spec/anareg_5320.h"
#elif(MCU_CORE_TYPE == MCU_CORE_5328)
#include "../mcu_spec/anareg_5328.h"
#elif(MCU_CORE_TYPE == MCU_CORE_5332  || MCU_CORE_TYPE == MCU_CORE_5330)
#include "../mcu_spec/anareg_5332.h"
#endif


