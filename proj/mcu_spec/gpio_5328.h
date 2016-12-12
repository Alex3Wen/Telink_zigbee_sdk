
#pragma once

#include "../common/types.h"
#include "../common/bit.h"
#include "../common/utility.h"
#include "../mcu/compiler.h"
#include "../mcu/register.h"
#include "gpio_default_5328.h"

enum{
	GPIO_MSDO  	= BIT(0),
	GPIO_MSDI  	= BIT(1),
	GPIO_MCLK  	= BIT(2),
	GPIO_MCSN  	= BIT(3),
	GPIO_DO 	= BIT(4),
	GPIO_DI 	= BIT(5),
	GPIO_CK 	= BIT(6),
	GPIO_CN 	= BIT(7),

	GPIO_PWM0	= BIT(8),
	GPIO_PWM1	= BIT(9),
	GPIO_PWM2	= BIT(10),
	GPIO_SWS	= BIT(11),
	GPIO_SWM	= BIT(12),

	GPIO_GP0	= BIT(13),
	GPIO_GP1	= BIT(14),
	GPIO_GP2	= BIT(15),
	GPIO_GP3	= BIT(16),
	GPIO_GP4	= BIT(17),
	GPIO_GP5	= BIT(18),
	GPIO_GP6	= BIT(19),
	GPIO_GP7	= BIT(20),

	GPIO_DM 	= BIT(21),
	GPIO_DP 	= BIT(22),
	
	GPIO_MAX_COUNT = 23,
	GPIO_FUNC_MASK = 0,

};

static inline int gpio_is_input_en(u32 pin){
	return (reg_gpio_f_ie & pin);
}

static inline void gpio_set_output_en(u32 pin, u32 value){
	if(value){
		BM_SET(reg_gpio_f_oe, pin);
	}else{
		BM_CLR(reg_gpio_f_oe, pin);
	}
}

static inline void gpio_set_input_en(u32 pin, u32 value){
	if(value){
		BM_SET(reg_gpio_f_ie, pin);
	}else{
		BM_CLR(reg_gpio_f_ie, pin);
	}
}

static inline void gpio_set_data_strength(u32 pin, u32 value){
	if(value){
		BM_SET(reg_gpio_f_ds, pin);
	}else{
		BM_CLR(reg_gpio_f_ds, pin);
	}
}

static inline void gpio_set_interrupt(u32 pin, u32 polarity){
	if(polarity){
		BM_SET(reg_gpio_f_pol, pin);
	}else{
		BM_CLR(reg_gpio_f_pol, pin);
	}
	BM_SET(reg_gpio_f_2risc0, pin);
}

static inline void gpio_set_interrupt_pol(u32 pin, u32 polarity){
	if(polarity){
		BM_SET(reg_gpio_f_pol, pin);
	}else{
		BM_CLR(reg_gpio_f_pol, pin);
	}
}

static inline void gpio_clr_interrupt(u32 pin){
	BM_CLR(reg_gpio_f_2risc0, pin);
}

static inline void gpio_write(u32 pin, u32 value){
	if(value){
		BM_SET(reg_gpio_f_datao, pin);
#ifdef WIN32
		BM_SET(reg_gpio_f_datai, pin);
#endif
	}else{
		BM_CLR(reg_gpio_f_datao, pin);
#ifdef WIN32
		BM_CLR(reg_gpio_f_datai, pin);
#endif
	}
}

static inline u32 gpio_read(u32 pin){
	return BM_IS_SET(reg_gpio_f_datai, pin);
}

static inline void gpio_enable_irq_pin(u32 pins, u32 levels){
	reg_gpio_f_2risc0 = pins;
	reg_gpio_f_pol = levels;
}

//enable interrupt wheel interrupt and wakeup
static inline void gpio_enable_irq_wakeup_pin(u32 pins, u32 levels){
	u32 flag_dm_pullup = DM_50K_PULLUP ? FLD_GPIO_DM_PULLUP : 0;
	reg_gpio_f_wakeup_en = pins | FLD_GPIO_WAKEUP_EN | flag_dm_pullup;
	reg_gpio_f_2risc2 = pins;
	reg_gpio_f_pol = levels ? ~pins : pins;
}

static inline void gpio_enable_wakeup_pin(u32 pins, u32 levels, int en){
	u32 flag_dm_pullup = DM_50K_PULLUP ? FLD_GPIO_DM_PULLUP : 0;
	if (levels) {
		reg_gpio_f_pol &= ~pins;
	}
	else {
		reg_gpio_f_pol |= pins;
	}

	if (en) {
		reg_gpio_f_wakeup_en |= pins | flag_dm_pullup;
	}
	else {
		reg_gpio_f_wakeup_en &= ~pins;
	}
}

// These macros only used in this file
#define GPIO_VALUE(type,n)				(GPIO##n##_##type?(GPIO_GP##n):0)
#define GPIO_FUNC_VALUE(type, func)		(func##_##type?(GPIO_##func):0)

#define GPIO_FUNC_REG_VALUE(type)		\
	( GPIO_VALUE(type, 0) | GPIO_VALUE(type, 1) | GPIO_VALUE(type, 2) | GPIO_VALUE(type, 3)			\
	| GPIO_VALUE(type, 4) | GPIO_VALUE(type, 5) | GPIO_VALUE(type, 6) | GPIO_VALUE(type, 7)			\
	| GPIO_FUNC_VALUE(type, MSDO) | GPIO_FUNC_VALUE(type, MSDI) | GPIO_FUNC_VALUE(type, MCLK) | GPIO_FUNC_VALUE(type, MCSN)	\
	| GPIO_FUNC_VALUE(type, DO) | GPIO_FUNC_VALUE(type, DI) | GPIO_FUNC_VALUE(type, CN) | GPIO_FUNC_VALUE(type, CK)			\
	| GPIO_FUNC_VALUE(type, PWM0) | GPIO_FUNC_VALUE(type, PWM1) | GPIO_FUNC_VALUE(type, PWM2) | GPIO_FUNC_VALUE(type, SWS)	\
	| GPIO_FUNC_VALUE(type, SWM) | GPIO_FUNC_VALUE(type, DM) | GPIO_FUNC_VALUE(type, DP))			

static inline void gpio_init(void){
	reg_gpio_f_wakeup_en = DM_50K_PULLUP ? FLD_GPIO_DM_PULLUP : 0;

	reg_gpio_f_oe = (u32)GPIO_FUNC_REG_VALUE(OUTPUT_ENABLE);
	reg_gpio_f_datao = (u32)GPIO_FUNC_REG_VALUE(DATA_OUT);
	reg_gpio_f_ie = (u32)GPIO_FUNC_REG_VALUE(INPUT_ENABLE);
	reg_gpio_f_ds = (u32)GPIO_FUNC_REG_VALUE(DATA_STRENGTH);

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


	STATIC_ASSERT(MSDO_FUNC == MCLK_FUNC && MSDO_FUNC == MSDI_FUNC && MSDO_FUNC == MCSN_FUNC);
	STATIC_ASSERT(DP_FUNC == DM_FUNC);													//   must same as AS_GPIO / AS_USB
	
}

static inline void gpio_mspi_float(void){
 	gpio_write (MOUSE_DIRECTION_PIN0, 0);	
 	gpio_write (MOUSE_DIRECTION_PIN1, 0);
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
			SET_FLD_V(reg_gpio_f_nrm, FLD_DP_FUNC, 0);
		}
		else{
			SET_FLD_V(reg_gpio_f_nrm, FLD_DP_FUNC, 0);
		}		
	}
}
	

