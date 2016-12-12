
#include "../tl_common.h"

#if MODULE_AUDIO_ENABLE
#define CLK_SBC_ENABLE		1
#define CLK_AUD_ENABLE		1
#define CLK_DFIFO_ENABLE	1
#define CLK_USB_ENABLE		1
#endif

#if (MODULE_USB_ENABLE)
#define CLK_AUD_ENABLE		1
#endif

#ifndef CLK_SBC_ENABLE
#define CLK_SBC_ENABLE		1
#endif
#ifndef CLK_AUD_ENABLE
#define CLK_AUD_ENABLE		1
#endif
#ifndef CLK_DFIFO_ENABLE
#define CLK_DFIFO_ENABLE	1
#endif
#ifndef CLK_USB_ENABLE
#define CLK_USB_ENABLE		(APPLICATION_DONGLE)
#endif

enum{
    CLK_EN_TYPE = (CLK_SBC_ENABLE ? FLD_CLK_SBC_EN:0) | (CLK_AUD_ENABLE ? FLD_CLK_AUD_EN : 0)    | (CLK_DFIFO_ENABLE ? FLD_CLK_DIFIO_EN : 0),
};

#if (MCU_CORE_TYPE == MCU_CORE_3520)

_attribute_ram_code_ void clock_init(){

	reg_clk_en = 0x7ff9 | (CLK_USB_ENABLE ? FLD_CLK_USB_EN | FLD_CLK_USB_PHY_EN: 0);
#if(CLOCK_SYS_TYPE == CLOCK_TYPE_PLL)
	reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, (CLOCK_PLL_CLOCK / CLOCK_SYS_CLOCK_1S), FLD_CLK_SEL_SRC, FLD_CLK_SEL_PLL);
#elif(CLOCK_SYS_TYPE == CLOCK_TYPE_OSC)
	reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, (CLOCK_OSC_MHZ / CLOCK_SYS_CLOCK_1S), FLD_CLK_SEL_SRC, FLD_CLK_SEL_RC);
#endif

	reg_tmr_ctrl = MASK_VAL(FLD_TMR0_EN, 1
		, FLD_TMR_WD_CAPT, (MODULE_WATCHDOG_ENABLE ? (WATCHDOG_INIT_TIMEOUT * CLOCK_SYS_CLOCK_1MS >> WATCHDOG_TIMEOUT_COEFF):0)
		, FLD_TMR_WD_EN, (MODULE_WATCHDOG_ENABLE?1:0));

}

#else

_attribute_ram_code_ void clock_init(){
#if (MCU_CORE_TYPE == MCU_CORE_5320)
    reg_rst_clk0 = 0xff000000 | (CLK_USB_ENABLE ? FLD_CLK_USB_EN: 0);
#else
    reg_rst_clk0 = 0x7f000000 | (CLK_USB_ENABLE ? FLD_CLK_USB_EN: 0);
#endif	
#if(MODULE_WATCHDOG_ENABLE && (MCU_CORE_TYPE == MCU_CORE_5320) && (CHIP_REVISION < CHIP_REVISION_A5))
	#if(CLOCK_SYS_TYPE == CLOCK_TYPE_PLL)
		STATIC_ASSERT(false);
	#endif
#endif

#if(CLOCK_SYS_TYPE == CLOCK_TYPE_PLL)
	reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, (CLOCK_PLL_CLOCK / CLOCK_SYS_CLOCK_1S), FLD_CLK_SEL_SRC, CLOCK_SEL_HS_DIV);
#elif(CLOCK_SYS_TYPE == CLOCK_TYPE_PAD)
	// note:  must  open clk src from analog !!!
	
	#if(CLOCK_SYS_CLOCK_HZ == 32000000)
		STATIC_ASSERT(CLK_FHS_MZ == 32);
		reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, 1, FLD_CLK_SEL_SRC, CLOCK_SEL_32M_PAD);
	#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
		STATIC_ASSERT(CLK_FHS_MZ == 16);
		reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, 1, FLD_CLK_SEL_SRC, CLOCK_SEL_16M_PAD);
	#else
		#error clock not set properly
	#endif
	
#elif(CLOCK_SYS_TYPE == CLOCK_TYPE_OSC)

	//STATIC_ASSERT(CLK_FHS_MZ == 32);
	#if(CLOCK_SYS_CLOCK_HZ == 32000000)
		reg_fhs_sel = 0;
		reg_clk_sel = 0;	// must be zero
	#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
		reg_fhs_sel = FHS_SEL_32M_OSC;
		reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, 2, FLD_CLK_SEL_SRC, CLOCK_SEL_HS_DIV);
	#elif(CLOCK_SYS_CLOCK_HZ == 8000000)
		reg_fhs_sel = FHS_SEL_32M_OSC;
		reg_clk_sel = MASK_VAL(FLD_CLK_SEL_DIV, 4, FLD_CLK_SEL_SRC, CLOCK_SEL_HS_DIV);
	#else
		#error clock not set properly
	#endif
	
#else
	#error clock not set properly
#endif

	reg_clk_en = 0xff | CLK_EN_TYPE;
	reg_tmr_ctrl = MASK_VAL(FLD_TMR0_EN, 1
		, FLD_TMR_WD_CAPT, (MODULE_WATCHDOG_ENABLE ? (WATCHDOG_INIT_TIMEOUT * CLOCK_SYS_CLOCK_1MS >> WATCHDOG_TIMEOUT_COEFF):0)
		, FLD_TMR_WD_EN, (MODULE_WATCHDOG_ENABLE?1:0));
	
}

#endif

_attribute_ram_code_ void sleep_us (u32 us)
{
	u32 t = clock_time();
	while(!clock_time_exceed(t, us)){
	}
}
_attribute_ram_code_ void sleep_tick (u32 delay_ticks)
{
    u32 t = clock_time();
    while(1){
        if((u32)(clock_time() - t) > delay_ticks)
            break;
    }
}