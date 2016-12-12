
#pragma once

enum{
	SYS_WAKEUP_FROM_OPR,
	SYS_WAKEUP_FROM_TIMER,
};

enum{
	SYS_SUSPEND_NOTIFY_SUSPEND,
	SYS_SUSPEND_NOTIFY_DEEPSLEEP,
};

enum{
	SYS_INIT_TYPE_POWERON,
	SYS_INIT_TYPE_DEEPSLEEP,
};

typedef struct {
	u8 init_type;
#if(APPLICATION_DONGLE)
	u8 host_suspend_mode;		// enter host_suspend_mode when the host ask me to suspend
#else	
	u8 sending_wakeup_key;		// enter host_suspend_mode when the host ask me to suspend
	u8 wakeup_chn;
	u8 active;
	u32 sending_wakeup_key_start_time;
#endif
}sys_stat_ctrl_t;

extern sys_stat_ctrl_t sys_stat_ctrl;
extern u32			dbg_tick[8];
void sys_init(void);
void sys_enter_host_suspend_mode();
void sys_exit_host_suspend_mode();

