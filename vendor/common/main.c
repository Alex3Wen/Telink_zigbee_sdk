
#include "../../proj/tl_common.h"

#if(!__PROJECT_PM_TEST__)

#include "../../proj/unit_test/ut.h"
#include "../../proj/os/ev.h"
#include "../../proj/os/sys.h"
#include "../../proj/drivers/spi.h"
#include "../../proj/drivers/syshw.h"
#include "../../proj/drivers/ethernet.h"
#include "../../proj/mcu/audhw.h"
#include "../../proj/simu/reg_simu.h"
#include "../../proj/simu/eth_simu.h"
#include "../../proj/simu/mouse_simu.h"
#include "../../proj/mcu/watchdog_i.h"
#include "../../proj/os/ev_timer.h"
#include "../../proj/simu/socket_api.h"
extern void user_init();

extern void zb_sched_loop_iteration();
extern void init_random(void);

int main(void){
#ifdef WIN32
//    reg_simu_init();
//    rega_simu_init();
#endif
//    usb_simu_init();
//    eth_simu_init();
//    rf_simu_init();
#ifdef WIN32
    ut_unit_test();
	init_random();
	win32_param_init();
#endif
    clock_init();
    sys_init();
    irq_init();
#if(MODULE_ETH_ENABLE)
    eth_init();
#endif


    user_init();

    irq_enable();

    while(1){
      #ifndef __PROJECT_PHY_TEST__) 
    	zb_sched_loop_iteration();
      #endif
      
#if(MODULE_WATCHDOG_ENABLE)
        wd_clear();
#endif
        ev_main(); 
     
    }
    return 0;
}

#endif

