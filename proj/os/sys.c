
#include "../tl_common.h"
#include "sys.h"
#include "../os/ev.h"
#include "../drivers/syshw.h"
#include "../drivers/usb.h"
#include "../drivers/mouse.h"
#include "../drivers/keyboard.h"
#include "../app/device_app.h"
#include "../drivers/somatic_sensor.h"
#include "../ext_drv/did.h"
#include "../../proj_lib/rf_drv.h"
#include "../../proj_lib/pm.h"
#if(MODULE_OFN_ENABLE)
#include "../ext_drv/ofn_vd5377.h"
#endif
#if(MODULE_BATT_ENABLE)
#include "../drivers/battery.h"
#endif
#if (MODULE_BUFM_ENABLE)
#include "../common/bufm.h"
#endif
#include "../os/timer.h"
//#include "../../rf/rf_hw.h"

sys_stat_ctrl_t sys_stat_ctrl;

#if(MODULE_PM_ENABLE)

int sys_check_deepsleep_wakeup_pin(void){
#if(MCU_CORE_TYPE == MCU_CORE_5320)
    // sleep wakeup pin can also wakeup  from sleep.  !!! DEEPSLEEP_PIN_CONVERT   convert  wakeup pin to Normal GPIO definition
    if(PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_IS_SET(reg_gpio_g_datai, DEEPSLEEP_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
    if(0 == PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_IS_CLR(reg_gpio_g_datai, DEEPSLEEP_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
#endif
    // sleep wakeup pin can also wakeup  from sleep.  !!! DEEPSLEEP_PIN_CONVERT   convert  wakeup pin to Normal GPIO definition
    if(PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_IS_SET(reg_gpio_f_datai, DEEPSLEEP_FUNC_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
    if(0 == PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_IS_CLR(reg_gpio_f_datai, DEEPSLEEP_FUNC_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
    return 0;        
}

int sys_check_gpio_wakeup_pin(void){
    // check suspend wakeup pin first.  If wakeup pin is valid, then do not enter suspend !!
#if(MCU_CORE_TYPE == MCU_CORE_5320)
    if(PM_SUSPEND_WAKEUP_GPIO_LEVEL && PM_SUSPEND_WAKEUP_GPIO_PIN && BM_IS_SET(reg_gpio_g_datai, PM_SUSPEND_WAKEUP_GPIO_PIN)){
        return 1;
    }
    if(0 == PM_SUSPEND_WAKEUP_GPIO_LEVEL && PM_SUSPEND_WAKEUP_GPIO_PIN && BM_IS_CLR(reg_gpio_g_datai, PM_SUSPEND_WAKEUP_GPIO_PIN)){
        return 1;
    }
#endif    
    if(PM_SUSPEND_WAKEUP_FUNC_LEVEL && PM_SUSPEND_WAKEUP_FUNC_PIN && BM_IS_SET(reg_gpio_f_datai, PM_SUSPEND_WAKEUP_FUNC_PIN)){
        return 1;
    }
    if(0 == PM_SUSPEND_WAKEUP_FUNC_LEVEL && PM_SUSPEND_WAKEUP_FUNC_PIN && BM_IS_CLR(reg_gpio_f_datai, PM_SUSPEND_WAKEUP_FUNC_PIN)){
        return 1;
    }
    return 0;
    
}

// to avoid unwanted wakeup.  before sleep, we set gpio to non-wakeup state
int sys_invert_gpio_wakeup_pin(void){
    // check suspend wakeup pin first.  If wakeup pin is valid, then do not enter suspend !!
#if(MCU_CORE_TYPE == MCU_CORE_5320)
    if(PM_SUSPEND_WAKEUP_GPIO_LEVEL && PM_SUSPEND_WAKEUP_GPIO_PIN && BM_CLR(reg_gpio_g_datai, PM_SUSPEND_WAKEUP_GPIO_PIN)){
        return 1;
    }
    if(0 == PM_SUSPEND_WAKEUP_GPIO_LEVEL && PM_SUSPEND_WAKEUP_GPIO_PIN && BM_SET(reg_gpio_g_datai, PM_SUSPEND_WAKEUP_GPIO_PIN)){
        return 1;
    }
#endif    
    if(PM_SUSPEND_WAKEUP_FUNC_LEVEL && PM_SUSPEND_WAKEUP_FUNC_PIN && BM_CLR(reg_gpio_f_datai, PM_SUSPEND_WAKEUP_FUNC_PIN)){
        return 1;
    }
    if(0 == PM_SUSPEND_WAKEUP_FUNC_LEVEL && PM_SUSPEND_WAKEUP_FUNC_PIN && BM_SET(reg_gpio_f_datai, PM_SUSPEND_WAKEUP_FUNC_PIN)){
        return 1;
    }
#if(MCU_CORE_TYPE == MCU_CORE_5320)
    // sleep wakeup pin can also wakeup  from sleep.  !!! DEEPSLEEP_PIN_CONVERT   convert  wakeup pin to Normal GPIO definition
    if(PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_CLR(reg_gpio_g_datai, DEEPSLEEP_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
    if(0 == PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_SET(reg_gpio_g_datai, DEEPSLEEP_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
#endif
    // sleep wakeup pin can also wakeup  from sleep.  !!! DEEPSLEEP_PIN_CONVERT   convert  wakeup pin to Normal GPIO definition
    if(PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_CLR(reg_gpio_f_datai, DEEPSLEEP_FUNC_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
    if(0 == PM_DEEPSLEEP_WAKEUP_LEVEL && PM_DEEPSLEEP_WAKEUP_PIN && BM_SET(reg_gpio_f_datai, DEEPSLEEP_FUNC_PIN_CONVERT(PM_DEEPSLEEP_WAKEUP_PIN))){
        return 1;
    }
    return 0;
    
}
#endif

#if(APPLICATION_DONGLE)
void sys_enter_host_suspend_mode(){
    if(!sys_stat_ctrl.host_suspend_mode){
        sys_stat_ctrl.host_suspend_mode = 1;

        //rf_channel = RF_CHANNEL_IN_USB_SUSPEND;

    }
}

void sys_exit_host_suspend_mode(){
    if(sys_stat_ctrl.host_suspend_mode){
        sys_stat_ctrl.host_suspend_mode = 0;
        usb_just_wakeup_from_suspend = 1; 

        cpu_reboot();     // fix halt when USB suspend-wakeup from USB
        
    }
}
#endif

#if(MODULE_OFN_ENABLE)
extern void ofn_power_down(void);
#endif
extern int usb_suspend_check(void);

u32 sys_active_event_time = 0;
void sys_on_suspend(void* data){
    
#if(MODULE_PM_ENABLE)
//    if(sys_check_gpio_wakeup_pin()){    //  do not set suspend wakeup pin, for simplicity and safety
//        return;
//    }

//    ev_emit_event_syn(EV_SUSPEND_NOTIFY, (void*)(SYS_SUSPEND_NOTIFY_SUSPEND));

    u8 r = irq_disable();            // must
    u32 old_time = clock_time();    // important, to rectify the clock
 
#if(APPLICATION_DONGLE)
    // must wakeup from usb source, otherwise noin time reponse to host on wakeup
    cpu_sleep_wakeup(0, PM_ACTIVE_SUSPEND_WAKEUP_TIME, WAKEUP_SRC_USB, 0);
#else    
    cpu_sleep_wakeup(0, PM_ACTIVE_SUSPEND_WAKEUP_TIME , 0, 0);    //    do not set wakeup from pin, for simplicity and safety
#endif

//    sleep_us(100*1000);
    // important, to rectify the clock ,  and around 180 us overhead, that the ev_timer may work properly
    reg_tmr0_tick = old_time + (PM_ACTIVE_SUSPEND_WAKEUP_TIME * CLOCK_SYS_CLOCK_1MS + 100 * CLOCK_SYS_CLOCK_1US);

    clock_init();    //    sys_wakeup_analog may overide clock setting

    // check to sleep
    if(PM_DEEPSLEEP_WAKEUP_PIN){
        if(clock_time_exceed(sys_active_event_time, (PM_ENTER_DEEPSLEEP_TIME * 1000))){        // suspend time out
            ev_emit_event_syn(EV_SUSPEND_NOTIFY, (void*)(SYS_SUSPEND_NOTIFY_DEEPSLEEP));    // to notify going sleep
            analog_write(rega_deepsleep_rf_chn, rf_channel);    //    save rf channel
            analog_write(rega_pkt_seq_no, rf_mac.send_pkt_seq_no);
            if(APPLICATION_DONGLE || (PM_DEEPSLEEP_NOT_CONNECTED_WAKEUP_PIN == PM_DEEPSLEEP_WAKEUP_PIN)  || (!PM_DEEPSLEEP_NOT_CONNECTED_WAKEUP_PIN)
                || (did_is_peer_id_valid() && rf_mac.conn_sta >= RF_CONN_STATE_CONNECTING)){                
                cpu_sleep_wakeup(1, 0, PM_DEEPSLEEP_WAKEUP_PIN, PM_DEEPSLEEP_WAKEUP_LEVEL);
            }else{
                cpu_sleep_wakeup(1, 0, PM_DEEPSLEEP_NOT_CONNECTED_WAKEUP_PIN, PM_DEEPSLEEP_WAKEUP_LEVEL);
            }
            clock_init();    //    sys_wakeup_analog may overide clock setting
        }
    }
    rf_drv_init(1);
#if(MODULE_DMIC_ENABLE)
    SET_FLD(reg_dmic_step, FLD_DMIC_CLK_EN);    // must
    rf_mac.first_pkt_from_suspend = 1;
    rf_mac.suspend_wakeup_time = clock_time();
#endif    
    irq_restore(r);
//    ev_emit_event(EV_WAKEUP_NOTIFY, 0); 

#endif
    
}

#if(!APPLICATION_DONGLE)
extern u8 air_mouse_enable;
extern u32 mic_enalbed;
#endif

u32			dbg_tick[8];
u32			dbg_idle;
u32			dbg_last[8];
u32			dbg_cnt;
void sys_idle_handler(void){
#if(MODULE_PM_ENABLE)
	if (dbg_idle<8) {
		dbg_last[dbg_idle] = clock_time() - dbg_tick[0];
	}
	dbg_idle++;
#if(APPLICATION_DONGLE)
	if(usb_suspend_check())
#else

	if(rf_allow_suspend() 
	#if(MODULE_OFN_ENABLE)
		&& (!ofn_vd5377_ready())
	#endif		
		&& !air_mouse_enable && !mic_enalbed 
		)
#endif

	{
		dbg_cnt = dbg_idle;
		dbg_tick[4] = clock_time() - dbg_tick[0];
		dbg_tick[5] = dbg_tick[1] - dbg_tick[0];
		dbg_tick[6] = dbg_tick[2] - dbg_tick[0];
		dbg_tick[7] = dbg_tick[3] - dbg_tick[0];
		sys_on_suspend(0);
		sys_stat_ctrl.active = 0;
		dbg_tick[0] = clock_time ();
		dbg_idle = 0;
	}
#endif
}

#if(!APPLICATION_DONGLE)	
void sys_key_handle(void* data){
	kb_data_t * kb_data = (kb_data_t*)(data);
	if(kb_data->cnt > 0){
	}
}
#endif

void sys_init(void){
	cpu_wakeup_init();

	clock_init();

	//  check whether wakeup form deep from 
#if (MCU_CORE_TYPE != MCU_CORE_3520)
	sys_stat_ctrl.init_type = analog_read(rega_deepsleep_flag);
#endif
    syshw_init();
    irq_init();
#if (MODULE_BUFM_ENABLE)
    bufm_init();
#endif

#if (EV_POST_TASK_ENABLE)
    ev_taskInit();
#endif

#ifndef WIN32
    did_init();
#endif

#if (MODULE_USB_ENABLE)
    usb_init();
#endif
#ifndef WIN32
#if (MODULE_RF_ENABLE)
    //rfhw_init();
#endif
#endif
#if(MODULE_MOUSE_ENABLE)
	mouse_init();
#endif 
#if (MODULE_SOMATIC_ENABLE)
	somatic_sensor_init();
#endif
#if (MODULE_KEYBOARD_ENABLE)
    kb_init();
#endif

    //device_app_init();

#if(MODULE_BATT_ENABLE)
    extern void batt_init(void);
    batt_init();
#endif

#if(MODULE_LED_ENABLE)
    extern void led_init(void);
    led_init();
#endif

	reg_usb_ep8_fifo_mode = 0x09;

	/* Initialize hardware timer */
	hwTmr_init(TIMER_IDX_1, TIMER_MODE_SCLK);

    ev_on_poll(EV_POLL_IDLE, sys_idle_handler); //    1 mili second

#if((!APPLICATION_DONGLE) && MODULE_KEYBOARD_ENABLE)	
	static ev_event_t key_ev = {sys_key_handle, 0};
	ev_on_event(EV_KEY_PRESS, &key_ev);
#endif

	sys_active_event_time = clock_time();
}

