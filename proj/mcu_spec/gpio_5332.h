
#pragma once

#include "../common/types.h"
#include "../common/bit.h"
#include "../common/utility.h"
#include "../mcu/compiler.h"
#include "../mcu/register.h"
#include "gpio_default_5332.h"

enum{
	GPIO_GP0	= BIT(0),
	GPIO_GP1	= BIT(1),
	GPIO_GP2	= BIT(2),
	GPIO_GP3	= BIT(3),
	GPIO_GP4	= BIT(4),
	GPIO_GP5	= BIT(5),
	GPIO_GP6	= BIT(6),
	GPIO_GP7	= BIT(7),

	GPIO_GP8	= BIT(8),
	GPIO_GP9	= BIT(9),
	GPIO_GP10	= BIT(10),
	GPIO_GP11	= BIT(11),
	GPIO_GP12	= BIT(12),
	GPIO_GP13	= BIT(13),
	GPIO_GP14	= BIT(14),
	GPIO_GP15	= BIT(15),
	GPIO_GP16	= BIT(16),
	GPIO_GP17	= BIT(17),
	GPIO_GP18	= BIT(18),
	GPIO_GP19	= BIT(19),
	GPIO_GP20	= BIT(20),
	GPIO_GP21	= BIT(21),
	GPIO_GP22	= BIT(22),
	GPIO_GP23	= BIT(23),
	GPIO_GP24	= BIT(24),
	GPIO_GP25	= BIT(25),
	GPIO_GP26	= BIT(26),
	GPIO_GP27	= BIT(27),
	GPIO_GP28	= BIT(28),
	GPIO_GP29	= BIT(29),

	GPIO_MAX_COUNT = 30,

	GPIO_FUNC_MASK = BIT(31),
	GPIO_MSDO  	= GPIO_FUNC_MASK | BIT(0),
	GPIO_MSDI  	= GPIO_FUNC_MASK | BIT(1),
	GPIO_MCLK  	= GPIO_FUNC_MASK | BIT(2),
	GPIO_MCSN  	= GPIO_FUNC_MASK | BIT(3),
	GPIO_DO 	= GPIO_FUNC_MASK | BIT(4),
	GPIO_DI 	= GPIO_FUNC_MASK | BIT(5),
	GPIO_CK 	= GPIO_FUNC_MASK | BIT(6),
	GPIO_CN 	= GPIO_FUNC_MASK | BIT(7),

	GPIO_PWM0	= GPIO_FUNC_MASK | BIT(8),
	GPIO_PWM1	= GPIO_FUNC_MASK | BIT(9),
	GPIO_PWM2	= GPIO_FUNC_MASK | BIT(10),
	GPIO_SWS	= GPIO_FUNC_MASK | BIT(11),
	GPIO_SWM	= GPIO_FUNC_MASK | BIT(12),
	GPIO_DM 	= GPIO_FUNC_MASK | BIT(13),
	GPIO_DP 	= GPIO_FUNC_MASK | BIT(14),
	
	GPIO_RX		= GPIO_GP22,
	GPIO_TX		= GPIO_GP23,
	GPIO_PWM3	= GPIO_GP24,
	GPIO_PWM4	= GPIO_GP25,

	GPIO_ANA0	= GPIO_GP11,
	GPIO_ANA1	= GPIO_GP12,
	GPIO_ANA2	= GPIO_GP13,
	GPIO_ANA3	= GPIO_GP14,
	GPIO_ANA4	= GPIO_GP16,
	GPIO_ANA5	= GPIO_GP17,
	GPIO_ANA6	= GPIO_GP18,
	GPIO_ANA7	= GPIO_GP19,

};

static inline int gpio_is_function_pin(u32 pin){
	return pin & GPIO_FUNC_MASK;
}

static inline int gpio_is_output_en(u32 pin){
	if(gpio_is_function_pin(pin)){
		return (reg_gpio_f_oe & BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		return (reg_gpio_g_oe & pin);
	}
}

static inline int gpio_is_input_en(u32 pin){
	if(gpio_is_function_pin(pin)){
		return (reg_gpio_f_ie & BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		return (reg_gpio_g_ie & pin);
	}
}

static inline void gpio_set_output_en(u32 pin, u32 value){
	if(gpio_is_function_pin(pin)){
		if(value){
			BM_SET(reg_gpio_f_oe, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}else{
			BM_CLR(reg_gpio_f_oe, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}
	}else{
		if(value){
			BM_SET(reg_gpio_g_oe, pin);
		}else{
			BM_CLR(reg_gpio_g_oe, pin);
		}
	}
}

static inline void gpio_set_input_en(u32 pin, u32 value){
	if(gpio_is_function_pin(pin)){
		if(value){
			BM_SET(reg_gpio_f_ie, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}else{
			BM_CLR(reg_gpio_f_ie, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}
	}else{
		if(value){
			BM_SET(reg_gpio_g_ie, pin);
		}else{
			BM_CLR(reg_gpio_g_ie, pin);
		}
	}
}

static inline void gpio_set_data_strength(u32 pin, u32 value){
	if(gpio_is_function_pin(pin)){
		if(value){
			BM_SET(reg_gpio_f_ds, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}else{
			BM_CLR(reg_gpio_f_ds, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}
	}else{
		if(value){
			BM_SET(reg_gpio_g_ds, pin);
		}else{
			BM_CLR(reg_gpio_g_ds, pin);
		}
	}
}

static inline void gpio_set_interrupt(u32 pin, u32 polarity){
    reg_gpio_g_wakeup_en |= FLD_GPIO_WAKEUP_EN | FLD_GPIO_IRQ_EN;
	if(gpio_is_function_pin(pin)){
		if(polarity){
			BM_SET(reg_gpio_f_pol, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}else{
			BM_CLR(reg_gpio_f_pol, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}
		BM_SET(reg_gpio_f_wakeup_en, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		if(polarity){
			BM_SET(reg_gpio_g_pol, pin);
		}else{
			BM_CLR(reg_gpio_g_pol, pin);
		}
		BM_SET(reg_gpio_g_wakeup_en, pin);
	}
}

static inline void gpio_set_interrupt_pol(u32 pin, u32 polarity){
	if(gpio_is_function_pin(pin)){
		if(polarity){
			BM_SET(reg_gpio_f_pol, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}else{
			BM_CLR(reg_gpio_f_pol, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}
	}else{
		if(polarity){
			BM_SET(reg_gpio_g_pol, pin);
		}else{
			BM_CLR(reg_gpio_g_pol, pin);
		}
	}
}

static inline void gpio_clr_interrupt(u32 pin){
	if(gpio_is_function_pin(pin)){
		BM_CLR(reg_gpio_f_wakeup_en, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		BM_CLR(reg_gpio_g_wakeup_en, pin);
	}
}

static inline void gpio_write(u32 pin, u32 value){
	if(gpio_is_function_pin(pin)){
		if(value){
			BM_SET(reg_gpio_f_datao, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
#ifdef WIN32
			BM_SET(reg_gpio_f_datai, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
#endif
		}else{
			BM_CLR(reg_gpio_f_datao, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
#ifdef WIN32
			BM_CLR(reg_gpio_f_datai, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
#endif
		}
	}else{
		if(value){
			BM_SET(reg_gpio_g_datao, pin);
#ifdef WIN32
			BM_SET(reg_gpio_g_datai, pin);
#endif
		}else{
			BM_CLR(reg_gpio_g_datao, pin);
#ifdef WIN32
			BM_CLR(reg_gpio_g_datai, pin);
#endif
		}
	}
}

static inline u32 gpio_read(u32 pin){
	if(gpio_is_function_pin(pin)){
		return BM_IS_SET(reg_gpio_f_datai, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		return BM_IS_SET(reg_gpio_g_datai, pin);
	}
}

static inline void gpio_enable_irq_pin(u32 pins, u32 levels){
	if(gpio_is_function_pin(pins)){
		reg_gpio_f_2risc0 = pins;
		reg_gpio_f_pol = levels;
	}else{
		reg_gpio_g_2risc0 = pins;
		reg_gpio_g_pol = levels;
	}
}

//enable interrupt wheel interrupt and wakeup
static inline void gpio_enable_irq_wakeup_pin(u32 pins, u32 levels){
	if(gpio_is_function_pin(pins)){
		reg_gpio_g_wakeup_en = FLD_GPIO_WAKEUP_EN;
		reg_gpio_f_wakeup_en = pins;
		reg_gpio_f_2risc2 = pins;
		reg_gpio_g_2risc2 = 0;
		reg_gpio_f_pol = levels ? ~pins : pins;
	}else{
		reg_gpio_f_wakeup_en = 0;
		reg_gpio_g_wakeup_en = pins | FLD_GPIO_WAKEUP_EN;
		reg_gpio_f_2risc2 = 0;
		reg_gpio_g_2risc2 = pins;
		reg_gpio_g_pol = levels ? ~pins : pins;
	}
}

static inline void gpio_enable_wakeup_pin(u32 pins, u32 levels, int en){
	if (levels) {
		if(gpio_is_function_pin(pins)){
			reg_gpio_f_pol &= ~pins;
		}
		else {
			reg_gpio_g_pol &= ~pins;
		}
	}
	else {
		if(gpio_is_function_pin(pins)){
			reg_gpio_f_pol |= pins;
		}
		else {
			reg_gpio_g_pol |= pins;
		}
	}

	if (en) {
		if(gpio_is_function_pin(pins)){
			reg_gpio_f_wakeup_en |= pins;
			reg_gpio_g_wakeup_en = FLD_GPIO_WAKEUP_EN;
		}
		else {
			reg_gpio_g_wakeup_en |= pins | FLD_GPIO_WAKEUP_EN;
		}
	}
	else {
		if(gpio_is_function_pin(pins)){
			reg_gpio_f_wakeup_en &= ~pins;
		}
		else {
			reg_gpio_g_wakeup_en &= ~pins;
		}
	}
}

// These macros only used in this file
#define GPIO_VALUE(type,n)				(GPIO##n##_##type?(GPIO_GP##n):0)
#define GPIO_FUNC_VALUE(type, func)		(func##_##type?(GPIO_##func):0)

#define GPIO_REG_VALUE(type)		\
	( GPIO_VALUE(type, 0) | GPIO_VALUE(type, 1) | GPIO_VALUE(type, 2) | GPIO_VALUE(type, 3)			\
	| GPIO_VALUE(type, 4) | GPIO_VALUE(type, 5) | GPIO_VALUE(type, 6) | GPIO_VALUE(type, 7)			\
	| GPIO_VALUE(type, 8) | GPIO_VALUE(type, 9) | GPIO_VALUE(type, 10) | GPIO_VALUE(type, 11)		\
	| GPIO_VALUE(type, 12) | GPIO_VALUE(type, 13) | GPIO_VALUE(type, 14) | GPIO_VALUE(type, 15)		\
	| GPIO_VALUE(type, 16) | GPIO_VALUE(type, 17) | GPIO_VALUE(type, 18) | GPIO_VALUE(type, 19)		\
	| GPIO_VALUE(type, 20) | GPIO_VALUE(type, 21) | GPIO_VALUE(type, 22) | GPIO_VALUE(type, 23)		\
	| GPIO_VALUE(type, 24) | GPIO_VALUE(type, 25) | GPIO_VALUE(type, 26) | GPIO_VALUE(type, 27))

#define GPIO_FUNC_REG_VALUE(type)		\
	( GPIO_VALUE(type, 0) | GPIO_VALUE(type, 1) | GPIO_VALUE(type, 2) | GPIO_VALUE(type, 3)			\
	| GPIO_VALUE(type, 4) | GPIO_VALUE(type, 5) | GPIO_VALUE(type, 6) | GPIO_VALUE(type, 7)			\
	| GPIO_FUNC_VALUE(type, MSDO) | GPIO_FUNC_VALUE(type, MSDI) | GPIO_FUNC_VALUE(type, MCLK) | GPIO_FUNC_VALUE(type, MCSN)	\
	| GPIO_FUNC_VALUE(type, DO) | GPIO_FUNC_VALUE(type, DI) | GPIO_FUNC_VALUE(type, CN) | GPIO_FUNC_VALUE(type, CK)			\
	| GPIO_FUNC_VALUE(type, PWM0) | GPIO_FUNC_VALUE(type, PWM1) | GPIO_FUNC_VALUE(type, PWM2) | GPIO_FUNC_VALUE(type, SWS)	\
	| GPIO_FUNC_VALUE(type, SWM) | GPIO_FUNC_VALUE(type, DM) | GPIO_FUNC_VALUE(type, DP))			

static inline void gpio_init(void){
	if (DP_FUNC == AS_GPIO) {
		SET_FLD_V(reg_swire_ctrl1, FLD_SWIRE_USB_EN, 0);
	}
	reg_gpio_f_oe = (u32)GPIO_FUNC_REG_VALUE(OUTPUT_ENABLE);
	reg_gpio_f_datao = (u32)GPIO_FUNC_REG_VALUE(DATA_OUT);
	reg_gpio_f_ie = (u32)GPIO_FUNC_REG_VALUE(INPUT_ENABLE);
	reg_gpio_f_ds = (u32)GPIO_FUNC_REG_VALUE(DATA_STRENGTH);

	reg_gpio_g_datao = (u32)GPIO_REG_VALUE(DATA_OUT);
	reg_gpio_g_oe = (u32)GPIO_REG_VALUE(OUTPUT_ENABLE);
	reg_gpio_g_ie = (u32)GPIO_REG_VALUE(INPUT_ENABLE);
	reg_gpio_g_ds = (u32)GPIO_REG_VALUE(DATA_STRENGTH);

 	// to avoid codes blow
	reg_gpio_f_nrm = (((MSDO_FUNC == AS_GPIO) ? FLD_MSDO_FUNC : 0)				
		| ((CN_FUNC == AS_GPIO) ? FLD_CN_FUNC : 0)							
		| ((CK_FUNC == AS_GPIO) ? FLD_CK_FUNC : 0)							
		| ((DO_FUNC == AS_GPIO) ? FLD_DO_GPIO_FUNC : 0)							
		| ((DI_FUNC == AS_GPIO) ? FLD_DI_FUNC : 0)		
		
		| ((PWM0_FUNC == AS_GPIO) ? MASK_VAL(FLD_PWM0_FUNC,1) : 0)
		| ((PWM0_FUNC == AS_I2C) ?  MASK_VAL(FLD_PWM0_FUNC,2) : 0)
		| ((PWM0_FUNC == AS_SDM) ? MASK_VAL(FLD_PWM0_FUNC,3) : 0)
		| ((PWM1_FUNC == AS_GPIO) ? MASK_VAL(FLD_PWM1_FUNC,1) : 0)
		| ((PWM1_FUNC == AS_I2C) ?	MASK_VAL(FLD_PWM1_FUNC,2) : 0)
		| ((PWM1_FUNC == AS_SDM) ? MASK_VAL(FLD_PWM1_FUNC,3) : 0)
		
		| ((PWM2_FUNC == AS_GPIO) ? FLD_PWM2_FUNC : 0)

		| ((SWS_FUNC == AS_GPIO) ? MASK_VAL(FLD_SWS_FUNC,1) : 0)
		| ((SWS_FUNC == AS_UART) ? MASK_VAL(FLD_SWS_FUNC,2) : 0)
		| ((SWS_FUNC == AS_SDM) ?  MASK_VAL(FLD_SWS_FUNC,3) : 0)
		| ((SWS_FUNC == AS_PWM) ?  MASK_VAL(FLD_SWS_FUNC,4) : 0)

		| ((SWM_FUNC == AS_GPIO) ? MASK_VAL(FLD_SWM_FUNC,1) : 0)
		| ((SWM_FUNC == AS_UART) ? MASK_VAL(FLD_SWM_FUNC,2) : 0)
		| ((SWM_FUNC == AS_SDM) ?  MASK_VAL(FLD_SWM_FUNC,3) : 0)
		| ((SWM_FUNC == AS_PWM) ?  MASK_VAL(FLD_SWM_FUNC,4) : 0)

		| ((DO_FUNC == AS_PWM) ? FLD_DO_PWM_FUNC : 0)
	
		| ((DP_FUNC == AS_GPIO && DM_FUNC == AS_GPIO) ? FLD_DP_FUNC : 0));

	analog_write (0x08, PULL_WAKEUP_SRC_GPIO2 |
						(PULL_WAKEUP_SRC_GPIO3<<2) |
						(PULL_WAKEUP_SRC_GPIO4<<4) |
						(PULL_WAKEUP_SRC_GPIO5<<6));

	analog_write (0x09,  PULL_WAKEUP_SRC_GPIO6 |
						(PULL_WAKEUP_SRC_PWM0<<2) |
						(PULL_WAKEUP_SRC_PWM1<<4) |
						(PULL_WAKEUP_SRC_PWM2<<6));

	analog_write (0x0c,  PULL_WAKEUP_SRC_GPIO16 |
						(PULL_WAKEUP_SRC_GPIO17<<2) |
						(PULL_WAKEUP_SRC_GPIO18<<4) |
						(PULL_WAKEUP_SRC_GPIO19<<6));

	analog_write (0x0d,  PULL_WAKEUP_SRC_GPIO22 |
						(PULL_WAKEUP_SRC_GPIO23<<2) |
						(PULL_WAKEUP_SRC_GPIO24<<4) |
						(PULL_WAKEUP_SRC_GPIO25<<6));

	analog_write (0x04,  (analog_read(0x04) & 0x3f) | (PULL_GLOBAL << 6));
	STATIC_ASSERT(MSDO_FUNC == MCLK_FUNC && MSDO_FUNC == MSDI_FUNC && MSDO_FUNC == MCSN_FUNC);
	STATIC_ASSERT(DP_FUNC == DM_FUNC);													//   must same as AS_GPIO / AS_USB
	
}

#define MSPI_AS_GPIO	BM_SET(reg_gpio_f_nrm, FLD_MSDO_FUNC)
#define MSPI_AS_SPI		BM_CLR(reg_gpio_f_nrm, FLD_MSDO_FUNC)

static inline void gpio_set_func(u32 pin, u32 func){
	switch(pin){
	case GPIO_MSDO:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_MSDO_FUNC);
		}else{
			BM_CLR(reg_gpio_f_nrm, FLD_MSDO_FUNC);
		}
		break;
	case GPIO_CN:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_CN_FUNC);
		}else{
			BM_CLR(reg_gpio_f_nrm, FLD_CN_FUNC);
		}
		break;
	case GPIO_CK:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_CK_FUNC);
		}else{
			BM_CLR(reg_gpio_f_nrm, FLD_CK_FUNC);
		}
		break;
	case GPIO_DO:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_DO_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_DO_PWM_FUNC);
		}else if(AS_PWM == func){
			BM_SET(reg_gpio_f_nrm, FLD_DO_PWM_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_DO_GPIO_FUNC);
		}else{
			BM_CLR(reg_gpio_f_nrm, FLD_DO_GPIO_FUNC | FLD_DO_PWM_FUNC);
		}
		break;
	case GPIO_DI:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_DI_FUNC);
		}else{
			BM_CLR(reg_gpio_f_nrm, FLD_DI_FUNC);
		}
		break;
	case GPIO_PWM0:
		if(AS_PWM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM0_FUNC, 0);
		}
		else if(AS_GPIO == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM0_FUNC, 1);
		}
		else if(AS_I2C == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM0_FUNC, 2);
		}
		else if(AS_SDM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM0_FUNC, 3);
		}
		break;
	case GPIO_PWM1:
		if(AS_PWM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM1_FUNC, 0);
		}
		else if(AS_GPIO == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM1_FUNC, 1);
		}
		else if(AS_I2C == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM1_FUNC, 2);
		}
		else if(AS_SDM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM1_FUNC, 3);
		}
		break;
	case GPIO_PWM2:
		if(AS_PWM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM2_FUNC, 0);
		}
		else{
			SET_FLD_V(reg_gpio_f_nrm, FLD_PWM2_FUNC, 1);
		}
		break;
	case GPIO_SWS:
		if(AS_SWS == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWS_FUNC, 0);
		}
		else if(AS_GPIO == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWS_FUNC, 1);
		}		
		else if(AS_UART == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWS_FUNC, 2);
		}		
		else if(AS_SDM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWS_FUNC, 3);
		}		
		else if(AS_PWM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWS_FUNC, 4);
		}
		break;
	case GPIO_SWM:
		if(AS_SWM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWM_FUNC, 0);
		}
		else if(AS_GPIO == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWM_FUNC, 1);
		}		
		else if(AS_UART == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWM_FUNC, 2);
		}		
		else if(AS_SDM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWM_FUNC, 3);
		}		
		else if(AS_PWM == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_SWM_FUNC, 4);
		}
		break;
	case GPIO_DP:
		if(AS_GPIO == func){
			SET_FLD_V(reg_gpio_f_nrm, FLD_DP_FUNC, 1);
			SET_FLD_V(reg_swire_ctrl1, FLD_SWIRE_USB_EN, 0);
		}
		else{
			SET_FLD_V(reg_gpio_f_nrm, FLD_DP_FUNC, 0);
		}		
	}
}
	

