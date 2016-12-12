
#include "../tl_common.h"

void gpio_user_irq_handler(void);
void timer_irq1_handler(void);
void timer_irq2_handler(void);
void pwm_timer_irq(void);
void usb_suspend_irq_handler(void);
void eth_rx_irq_handler(void);
void rf_rx_irq_handler(void);
void rf_tx_irq_handler(void);

// called by irq in cstartup.s
_attribute_ram_code_ void irq_handler(void)
{
//	irq_disable();
#if (__DEBUG__)			// Debug only,  to indicate in irq_handler
	irq_set_in_handler();
#endif

	u32 src = reg_irq_src;
#if(MODULE_ETH_ENABLE)
	u8  eth_irq = reg_mac_irq_sta;
#endif
	u8  src_rf = reg_rf_rx_status;


	if(IRQ_TIMER1_ENABLE && (src & FLD_IRQ_TMR1_EN)){
		timer_irq1_handler();	
		reg_irq_src = FLD_IRQ_TMR1_EN;
	}


    if(IRQ_TIMER2_ENABLE && (src & FLD_IRQ_TMR2_EN)){
		timer_irq2_handler();
		reg_irq_src = FLD_IRQ_TMR2_EN;
	}

    if(IRQ_PWM_TIMER && (src & FLD_IRQ_TMR2_EN)){
    	pwm_timer_irq();
		reg_irq_src = FLD_IRQ_TMR2_EN;
	}

    if(IRQ_GPIO_ENABLE && (src & FLD_IRQ_GPIO_RISC0_EN)){
    #ifndef WIN32
        gpio_user_irq_handler();
    #endif
        reg_irq_src = FLD_IRQ_GPIO_RISC0_EN;
    }

    #if 0
    if (IRQ_GPIO_ENABLE && (src & FLD_IRQ_GPIO_EN)){
    #ifndef WIN32
        gpio_user_irq_handler();
    #endif
        reg_irq_src = FLD_IRQ_GPIO_EN;
    }
    #endif

#if(MODULE_ETH_ENABLE)
    if(IRQ_MAC_ENABLE && (eth_irq & FLD_MAC_STA_RX_DONE)){
        eth_rx_irq_handler();
    }
    // important.  因为我们没有用到 tx 中断，只用了 rx 中断。
    // 但是 tx 中断在发送的时候会被置1，如果这里不清的话
    // 中断调用程序会不断的调用，造成程序不可用。
    reg_mac_irq_sta = 0xff;
#endif    
    if(IRQ_RF_RTX_ENABLE && (src_rf & FLD_RF_RX_INTR)){
#if(__LOG_RT_ENABLE__)
        if(1){
            LOG_TICK(TR_T_RX_IRQ, rf_rx_irq_handler());
        }else
#endif
        rf_rx_irq_handler();
    }

    if(IRQ_RF_RTX_ENABLE && (src_rf & FLD_RF_TX_INTR)){
#if(__LOG_RT_ENABLE__)
        if(1){
            LOG_TICK(TR_T_TX_IRQ, rf_tx_irq_handler());
        }else
#endif
        rf_tx_irq_handler();
    }
//    irq_clr_src();     // write clear
//    irq_enable();
#if (__DEBUG__)
    irq_set_out_handler();
#endif

}

