
#pragma once

#include "../common/types.h"
#include "../common/bit.h"
#include "../common/utility.h"
#include "../mcu/compiler.h"
#include "../mcu/register.h"

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

	GPIO_ANA1	= GPIO_GP15,	// alias
	GPIO_ANA2	= GPIO_GP16,	// alias
	GPIO_ANA4	= GPIO_GP17,	// alias
	GPIO_ANA5	= GPIO_GP18,	// alias
	GPIO_ANA6	= GPIO_GP19,	// alias
	GPIO_ANA7	= GPIO_GP20,	// alias
	GPIO_ANA8	= GPIO_GP21,	// alias

	GPIO_MAX_COUNT = 28,

	GPIO_FUNC_MASK = BIT(31),
	GPIO_MSDO  	= GPIO_FUNC_MASK | BIT(0),
	GPIO_MSDI  	= GPIO_FUNC_MASK | BIT(1),
	GPIO_MCLK  	= GPIO_FUNC_MASK | BIT(2),
	GPIO_MCSN  	= GPIO_FUNC_MASK | BIT(3),
	GPIO_SWS   	= GPIO_FUNC_MASK | BIT(4),
	GPIO_SWM   	= GPIO_FUNC_MASK | BIT(5),
	GPIO_PWM0  	= GPIO_FUNC_MASK | BIT(6),
	GPIO_PWM1  	= GPIO_FUNC_MASK | BIT(7),
	GPIO_CN	   	= GPIO_FUNC_MASK | BIT(8),
	GPIO_CK	   	= GPIO_FUNC_MASK | BIT(9),
	GPIO_DO	   	= GPIO_FUNC_MASK | BIT(10),
	GPIO_DI	   	= GPIO_FUNC_MASK | BIT(11),
	GPIO_MSC   	= GPIO_FUNC_MASK | BIT(12),
	GPIO_MIO   	= GPIO_FUNC_MASK | BIT(13),
	GPIO_MV    	= GPIO_FUNC_MASK | BIT(14),
	GPIO_ME    	= GPIO_FUNC_MASK | BIT(15),
	GPIO_R0    	= GPIO_FUNC_MASK | BIT(16),
	GPIO_R1    	= GPIO_FUNC_MASK | BIT(17),
	GPIO_T0    	= GPIO_FUNC_MASK | BIT(18),
	GPIO_T1    	= GPIO_FUNC_MASK | BIT(19),
	GPIO_TE    	= GPIO_FUNC_MASK | BIT(20),
	GPIO_MC    	= GPIO_FUNC_MASK | BIT(21),
	GPIO_DM    	= GPIO_FUNC_MASK | BIT(22),
	GPIO_DP    	= GPIO_FUNC_MASK | BIT(23),

	GPIO_ANA3	= GPIO_PWM1,	// alias
	GPIO_ANA9	= GPIO_T0,		// alias
	GPIO_ANA10	= GPIO_T1,		// alias
	GPIO_ANA11	= GPIO_R0,		// alias
	GPIO_ANA12	= GPIO_R1,		// alias

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
	if(gpio_is_function_pin(pin)){ 
		if(polarity){
			BM_SET(reg_gpio_f_pol, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}else{
			BM_CLR(reg_gpio_f_pol, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
		}
		BM_SET(reg_gpio_f_2risc0, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		if(polarity){
			BM_SET(reg_gpio_g_pol, pin);
		}else{
			BM_CLR(reg_gpio_g_pol, pin);
		}
		BM_SET(reg_gpio_g_2risc0, pin);
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
		BM_CLR(reg_gpio_f_2risc0, BM_CLR_MASK_V(pin,GPIO_FUNC_MASK));
	}else{
		BM_CLR(reg_gpio_g_2risc0, pin);
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

// These macros only used in this file
#define GPIO_VALUE(type,n)		(GPIO##n##_##type?(1<<n):0)
#define GPIO_REG_VALUE(type)		\
	( GPIO_VALUE(type, 0) | GPIO_VALUE(type, 1) | GPIO_VALUE(type, 2) | GPIO_VALUE(type, 3)			\
	| GPIO_VALUE(type, 4) | GPIO_VALUE(type, 5) | GPIO_VALUE(type, 6) | GPIO_VALUE(type, 7)			\
	| GPIO_VALUE(type, 8) | GPIO_VALUE(type, 9) | GPIO_VALUE(type, 10) | GPIO_VALUE(type, 11)		\
	| GPIO_VALUE(type, 12) | GPIO_VALUE(type, 13) | GPIO_VALUE(type, 14) | GPIO_VALUE(type, 15)		\
	| GPIO_VALUE(type, 16) | GPIO_VALUE(type, 17) | GPIO_VALUE(type, 18) | GPIO_VALUE(type, 19)		\
	| GPIO_VALUE(type, 20) | GPIO_VALUE(type, 21) | GPIO_VALUE(type, 22) | GPIO_VALUE(type, 23)		\
	| GPIO_VALUE(type, 24) | GPIO_VALUE(type, 25) | GPIO_VALUE(type, 26) | GPIO_VALUE(type, 27))		

#define GPIO_FUNC_VALUE(type, func)		(func##_##type?(GPIO_##func):0)
#define GPIO_FUNC_REG_VALUE(type)		\
	( GPIO_FUNC_VALUE(type, MSDO) | GPIO_FUNC_VALUE(type, MSDI) | GPIO_FUNC_VALUE(type, MCLK) | GPIO_FUNC_VALUE(type, MCSN)	\
	| GPIO_FUNC_VALUE(type, SWS) | GPIO_FUNC_VALUE(type, SWM) | GPIO_FUNC_VALUE(type, PWM0) | GPIO_FUNC_VALUE(type, PWM1)	\
	| GPIO_FUNC_VALUE(type, CN) | GPIO_FUNC_VALUE(type, CK) | GPIO_FUNC_VALUE(type, DO) | GPIO_FUNC_VALUE(type, DI)			\
	| GPIO_FUNC_VALUE(type, MSC) | GPIO_FUNC_VALUE(type, MIO) | GPIO_FUNC_VALUE(type, MV) | GPIO_FUNC_VALUE(type, ME)		\
	| GPIO_FUNC_VALUE(type, R0) | GPIO_FUNC_VALUE(type, R1) | GPIO_FUNC_VALUE(type, T0) | GPIO_FUNC_VALUE(type, T1)			\
	| GPIO_FUNC_VALUE(type, TE) | GPIO_FUNC_VALUE(type, MC) | GPIO_FUNC_VALUE(type, DM) | GPIO_FUNC_VALUE(type, DP))			

static inline void gpio_init(void){
	reg_gpio_f_oe = (u32)GPIO_FUNC_REG_VALUE(OUTPUT_ENABLE) & ~GPIO_FUNC_MASK;
	reg_gpio_f_datao = (u32)GPIO_FUNC_REG_VALUE(DATA_OUT) & ~GPIO_FUNC_MASK;
 
	// to avoid codes blow
	reg_gpio_f_nrm = (((MSDO_FUNC == AS_GPIO) ? BIT(0) : 0)				
		| ((PWM0_FUNC == AS_I2C && PWM1_FUNC == AS_I2C) ? BIT(1) : 0)	
		| ((PWM0_FUNC == AS_GPIO) ? BIT(2) : 0)							
		| ((PWM1_FUNC == AS_GPIO) ? BIT(3) : 0) 						
		| ((SWS_FUNC == AS_GPIO) ? BIT(4) : 0) 				// or else swire			
		| ((SWM_FUNC == AS_GPIO) ? BIT(5) : 0)				// or else swire	
		| ((SWS_FUNC == AS_UART && SWM_FUNC == AS_UART) ? BIT(6) : 0)	
		| ((CN_FUNC == AS_GPIO) ? BIT(7) : 0)							
		| ((CK_FUNC == AS_GPIO) ? BIT(8) : 0)							
		| ((DO_FUNC == AS_GPIO) ? BIT(9) : 0)							
		| ((DI_FUNC == AS_GPIO) ? BIT(10) : 0)							
		| ((MSC_FUNC == AS_GPIO) ? BIT(11) : 0)							
		| ((MIO_FUNC == AS_GPIO) ? BIT(12) : 0)							
		| ((MV_FUNC == AS_GPIO) ? BIT(13) : 0)							
		| ((ME_FUNC == AS_GPIO) ? BIT(14) : 0)							
		| ((R0_FUNC == AS_GPIO && R1_FUNC == AS_GPIO && T0_FUNC == AS_GPIO && T1_FUNC == AS_GPIO) ? BIT(15) : 0)
		| ((TE_FUNC == AS_GPIO) ? BIT(16) : 0)							
		| ((TE_FUNC == AS_DMIC) ? BIT(17) : 0)																	//  else 0,  TE  == ethernet					
		| ((R0_FUNC == AS_SDM && R1_FUNC == AS_SDM && T0_FUNC == AS_SDM && T1_FUNC == AS_SDM) ? BIT(18) : 0)	//  else 0,  R0,R1,T0,T1  == ethernet
		| ((MSC_FUNC == AS_I2S && MIO_FUNC == AS_I2S && MV_FUNC == AS_I2S && ME_FUNC == AS_I2S && MC_FUNC == AS_I2S) ? BIT(19) : 0)	// else 0, MSC,MIO,MV,ME,MC == ethernet
		| ((DP_FUNC == AS_GPIO && DM_FUNC == AS_GPIO) ? BIT(20) : 0));											// else 0, DP, DM == usb

	if(CK_FUNC == AS_GPIO || DO_FUNC == AS_GPIO){
		BM_SET(reg_spi_sp, FLD_CK_DO_GPIO_MODE);	// doc is wrong
	}

	reg_gpio_f_ie = (u32)GPIO_FUNC_REG_VALUE(INPUT_ENABLE) & ~GPIO_FUNC_MASK;
	reg_gpio_f_ds = (u32)GPIO_FUNC_REG_VALUE(DATA_STRENGTH) & ~GPIO_FUNC_MASK;

	reg_gpio_g_datao = (u32)GPIO_REG_VALUE(DATA_OUT);
	reg_gpio_g_oe = (u32)GPIO_REG_VALUE(OUTPUT_ENABLE);
	reg_gpio_g_ie = (u32)GPIO_REG_VALUE(INPUT_ENABLE);
	reg_gpio_g_ds = (u32)GPIO_REG_VALUE(DATA_STRENGTH);

	STATIC_ASSERT(MSDO_FUNC == MCLK_FUNC && MSDO_FUNC == MSDI_FUNC && MSDO_FUNC == MCSN_FUNC);
	STATIC_ASSERT((PWM0_FUNC == AS_I2C && PWM1_FUNC == AS_I2C) || (PWM0_FUNC != AS_I2C && PWM1_FUNC != AS_I2C));
	STATIC_ASSERT((SWS_FUNC == AS_UART && SWM_FUNC == AS_UART) || (SWS_FUNC != AS_UART && SWM_FUNC != AS_UART));
	//STATIC_ASSERT((CN_FUNC == AS_SPI && CK_FUNC == AS_SPI  && DO_FUNC == AS_SPI && DI_FUNC == AS_SPI)
	//	|| (CN_FUNC != AS_SPI && CK_FUNC != AS_SPI  && DO_FUNC != AS_SPI && DI_FUNC != AS_SPI));
	STATIC_ASSERT(R0_FUNC == R1_FUNC &&  R1_FUNC == T0_FUNC && T0_FUNC == T1_FUNC);		//   must same as AS_GPIO / AS_SDM / AS_ETH_MAC
//	STATIC_ASSERT(MSC_FUNC == MIO_FUNC && MIO_FUNC == MV_FUNC && MV_FUNC == ME_FUNC && ME_FUNC == MC_FUNC);	 //   must same as AS_GPIO / AS_I2S / AS_ETH_MAC
	STATIC_ASSERT(DP_FUNC == DM_FUNC);													//   must same as AS_GPIO / AS_USB
	
}

#define MSPI_AS_GPIO	BM_SET(reg_gpio_f_nrm, FLD_MSDO_FUNC)
#define MSPI_AS_SPI		BM_CLR(reg_gpio_f_nrm, FLD_MSDO_FUNC)

static inline void gpio_set_func(u32 pin, u32 func){
	switch(pin){
	case GPIO_MCLK:
	case GPIO_MSDO:
	case GPIO_MSDI:
	case GPIO_MCSN:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_MSDO_FUNC);
		}else{				// spi
			BM_CLR(reg_gpio_f_nrm, FLD_MSDO_FUNC);
		}
		break;
	case GPIO_PWM0:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_PWM0_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_I2C_FUNC);
		}else if(AS_I2C == func){
			BM_SET(reg_gpio_f_nrm, FLD_I2C_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_PWM0_GPIO_FUNC);
		}else{				// PWM
			BM_CLR(reg_gpio_f_nrm, FLD_PWM0_GPIO_FUNC | FLD_I2C_FUNC);
		}
		break;
	case GPIO_PWM1:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_PWM1_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_I2C_FUNC);
		}else if(AS_I2C == func){
			BM_SET(reg_gpio_f_nrm, FLD_I2C_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_PWM1_GPIO_FUNC);
		}else{				// PWM
			BM_CLR(reg_gpio_f_nrm, FLD_PWM1_GPIO_FUNC | FLD_I2C_FUNC);
		}
		break;
	case GPIO_SWS:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_SWS_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_UART_FUNC);
		}else if(AS_UART == func){
			BM_SET(reg_gpio_f_nrm, FLD_UART_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_SWS_GPIO_FUNC);
		}else{				// SWS
			BM_CLR(reg_gpio_f_nrm, FLD_SWS_GPIO_FUNC | FLD_UART_FUNC);
		}
		break;
	case GPIO_SWM:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_SWM_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_UART_FUNC);
		}else if(AS_UART == func){
			BM_SET(reg_gpio_f_nrm, FLD_UART_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_SWM_GPIO_FUNC);
		}else{				// SWM
			BM_CLR(reg_gpio_f_nrm, FLD_SWM_GPIO_FUNC | FLD_UART_FUNC);
		}
		break;
	case GPIO_CN:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_CN_GPIO_FUNC);
		}else{	// SPI
			BM_CLR(reg_gpio_f_nrm, FLD_CN_GPIO_FUNC);
		}
		break;
	case GPIO_CK:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_CK_GPIO_FUNC);
			BM_SET(reg_spi_sp, FLD_CK_DO_GPIO_MODE);	// doc is wrong
		}else{	// SPI
			BM_CLR(reg_gpio_f_nrm, FLD_CK_GPIO_FUNC);
		}
		break;
	case GPIO_DO:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_DO_GPIO_FUNC);
			BM_SET(reg_spi_sp, FLD_CK_DO_GPIO_MODE);	// doc is wrong
		}else{	// SPI
			BM_CLR(reg_gpio_f_nrm, FLD_DO_GPIO_FUNC);
		}
		break;
	case GPIO_DI:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_DI_GPIO_FUNC);
		}else{	// SPI
			BM_CLR(reg_gpio_f_nrm, FLD_DI_GPIO_FUNC);
		}
		break;
	case GPIO_MSC:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_MSC_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC);
		}else if(AS_I2S == func){	// I2S
			BM_SET(reg_gpio_f_nrm, FLD_I2S_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_MSC_GPIO_FUNC);
		}else{		// ethernet
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC | FLD_MSC_GPIO_FUNC);
		}
		break;
	case GPIO_MIO:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_MIO_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC);
		}else if(AS_I2S == func){	// I2S
			BM_SET(reg_gpio_f_nrm, FLD_I2S_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_MIO_GPIO_FUNC);
		}else{		// ethernet
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC | FLD_MIO_GPIO_FUNC);
		}
		break;
	case GPIO_MV:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_MV_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC);
		}else if(AS_I2S == func){	// I2S
			BM_SET(reg_gpio_f_nrm, FLD_I2S_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_MV_GPIO_FUNC);
		}else{		// ethernet
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC | FLD_MV_GPIO_FUNC);
		}
		break;
	case GPIO_ME:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_ME_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC);
		}else if(AS_I2S == func || AS_DMIC == func){	// I2S / dmic
			BM_SET(reg_gpio_f_nrm, FLD_I2S_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_ME_GPIO_FUNC);
		}else{		// ethernet
			BM_CLR(reg_gpio_f_nrm, FLD_I2S_FUNC | FLD_ME_GPIO_FUNC);
		}
		break;
	case GPIO_R0:
	case GPIO_R1:
	case GPIO_T0:
	case GPIO_T1:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_R0_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_R0_SDM_FUNC);
		}else if(AS_SDM == func){
			BM_SET(reg_gpio_f_nrm, FLD_R0_SDM_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_R0_GPIO_FUNC);
		}else{	// ethernet
			BM_CLR(reg_gpio_f_nrm, FLD_R0_SDM_FUNC | FLD_R0_GPIO_FUNC);
		}
		break;
	case GPIO_TE:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_TE_GPIO_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_TE_DMIC_FUNC);
		}else if(AS_DMIC == func){	// I2S
			BM_SET(reg_gpio_f_nrm, FLD_TE_DMIC_FUNC);
			BM_CLR(reg_gpio_f_nrm, FLD_TE_GPIO_FUNC);
		}else{		// ethernet
			BM_CLR(reg_gpio_f_nrm, FLD_TE_GPIO_FUNC | FLD_TE_DMIC_FUNC);
		}
		break;
	case GPIO_DP:
	case GPIO_DM:
		if(AS_GPIO == func){
			BM_SET(reg_gpio_f_nrm, FLD_DP_GPIO_FUNC);
		}else{		// USB
			BM_CLR(reg_gpio_f_nrm, FLD_DP_GPIO_FUNC);
		}
		break;
	}

}
	



