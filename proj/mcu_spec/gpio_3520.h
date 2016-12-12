
#pragma once

#include "../common/types.h"
#include "../common/bit.h"
#include "../common/utility.h"
#include "../mcu/compiler.h"
#include "../mcu/register.h"
#include "gpio_default_3520.h"

#define		REG_ADR_GPIO_DO(id)		REG_ADDR8((((id)>>8) | ADR_GPIO_DO))
#define		REG_ADR_GPIO_DI(id)		REG_ADDR8((((id)>>8) | ADR_GPIO_DI))
#define		REG_ADR_GPIO_OEN(id)	REG_ADDR8((((id)>>8) | ADR_GPIO_OEN))
#define		REG_ADR_GPIO_IE(id)		REG_ADDR8((((id)>>8) | ADR_GPIO_IE))
#define		REG_ADR_GPIO_DS(id)		REG_ADDR8((((id)>>8) | ADR_GPIO_DS))
#define		REG_ADR_GPIO_MODE(id)	REG_ADDR8((((id)>>8) | ADR_GPIO_MODE))

#define		REG_ADR_GPIO_IRQ(id)		REG_ADDR8((0xb0 + (((id)>>11)&3)))
#define		REG_ADR_GPIO_POLARITY(id)	REG_ADDR8((0xa8 + (((id)>>11)&3)))

enum{
	GPIO_PA0	= 0x8000 | BIT(0),
	GPIO_PA1	= 0x8000 | BIT(1),
	GPIO_PA2	= 0x8000 | BIT(2),
	GPIO_PA3	= 0x8000 | BIT(3),
	GPIO_PA4	= 0x8000 | BIT(4),
	GPIO_PA5	= 0x8000 | BIT(5),
	GPIO_PA6	= 0x8000 | BIT(6),
	GPIO_PA7	= 0x8000 | BIT(7),

	GPIO_PB0	= 0x8800 | BIT(0),
	GPIO_PB1	= 0x8800 | BIT(1),
	GPIO_PB2	= 0x8800 | BIT(2),
	GPIO_PB3	= 0x8800 | BIT(3),
	GPIO_PB4	= 0x8800 | BIT(4),
	GPIO_PB5	= 0x8800 | BIT(5),
	GPIO_PB6	= 0x8800 | BIT(6),
	GPIO_PB7	= 0x8800 | BIT(7),

	GPIO_PC0	= 0x9000 | BIT(0),
	GPIO_PC1	= 0x9000 | BIT(1),
	GPIO_PC2	= 0x9000 | BIT(2),
	GPIO_PC3	= 0x9000 | BIT(3),
	GPIO_PC4	= 0x9000 | BIT(4),
	GPIO_PC5	= 0x9000 | BIT(5),
	GPIO_PC6	= 0x9000 | BIT(6),
	GPIO_PC7	= 0x9000 | BIT(7),

	GPIO_PD0	= 0x9800 | BIT(0),
	GPIO_PD1	= 0x9800 | BIT(1),
	GPIO_PD2	= 0x9800 | BIT(2),
	GPIO_PD3	= 0x9800 | BIT(3),
	GPIO_PD4	= 0x9800 | BIT(4),
	GPIO_PD5	= 0x9800 | BIT(5),
	GPIO_PD6	= 0x9800 | BIT(6),
	GPIO_PD7	= 0x9800 | BIT(7),

	GPIO_PE0	= 0xa000 | BIT(0),
	GPIO_PE1	= 0xa000 | BIT(1),
	GPIO_PE2	= 0xa000 | BIT(2),
	GPIO_PE3	= 0xa000 | BIT(3),
	GPIO_PE4	= 0xa000 | BIT(4),
	GPIO_PE5	= 0xa000 | BIT(5),
	GPIO_PE6	= 0xa000 | BIT(6),
	GPIO_PE7	= 0xa000 | BIT(7),
	
	GPIO_FUNC_MASK = BIT(31),
	GPIO_MAX_COUNT = 32,
};


static inline int gpio_is_output_en(u32 pin){
	return !BM_IS_SET(REG_ADR_GPIO_OEN(pin), pin & 0xff);
}

static inline int gpio_is_input_en(u32 pin){
	return BM_IS_SET(REG_ADR_GPIO_IE(pin), pin & 0xff);
}

static inline void gpio_set_output_en(u32 pin, u32 value){
	u8	mbit = pin & 0xff;
	if(!value){
		BM_SET(REG_ADR_GPIO_OEN(pin), mbit);
	}else{
		BM_CLR(REG_ADR_GPIO_OEN(pin), mbit);
	}
}

static inline void gpio_set_input_en(u32 pin, u32 value){
	u8	mbit = pin & 0xff;
	if(value){
		BM_SET(REG_ADR_GPIO_IE(pin), mbit);
	}else{
		BM_CLR(REG_ADR_GPIO_IE(pin), mbit);
	}
}

static inline void gpio_set_data_strength(u32 pin, u32 value){
	u8	mbit = pin & 0xff;
	if(value){
		BM_SET(REG_ADR_GPIO_DS(pin), mbit);
	}else{
		BM_CLR(REG_ADR_GPIO_DS(pin), mbit);
	}
}

static inline void gpio_set_interrupt(u32 pin, u32 polarity){
	u8	mbit = pin & 0xff;
	BM_SET(REG_ADR_GPIO_IRQ(pin), mbit);
	if(!polarity){
		BM_SET(REG_ADR_GPIO_POLARITY(pin), mbit);
	}else{
		BM_CLR(REG_ADR_GPIO_POLARITY(pin), mbit);
	}
}

static inline void gpio_set_interrupt_pol(u32 pin, u32 polarity){
	u8	mbit = pin & 0xff;
	if(polarity){
		BM_SET(REG_ADR_GPIO_POLARITY(pin), mbit);
	}else{
		BM_CLR(REG_ADR_GPIO_POLARITY(pin), mbit);
	}
}

static inline void gpio_clr_interrupt(u32 pin){
	u8	mbit = pin & 0xff;
	BM_CLR(REG_ADR_GPIO_IRQ(pin), mbit);
}

static inline void gpio_write(u32 pin, u32 value){

	u8	mbit = pin & 0xff;
	if(value){
		BM_SET(REG_ADR_GPIO_DO(pin), mbit);
	}else{
		BM_CLR(REG_ADR_GPIO_DO(pin), mbit);
	}
}

static inline u32 gpio_read(u32 pin){
	return BM_IS_SET(REG_ADR_GPIO_DI(pin), pin & 0xff);
}

//enable interrupt wheel interrupt and wakeup
static inline void gpio_enable_irq_wakeup_pin(u32 pins, u32 levels){

}

static inline void gpio_init(void){
	reg_pa_io =
		(PA0_IE<<8) 	| (PA1_IE<<9)	| (PA2_IE<<10)	| (PA3_IE<<11) |
		(PA4_IE<<12)	| (PA5_IE<<13)	| (PA6_IE<<14)	| (PA7_IE<<15) |
		(PA0_OEN<<16)	| (PA1_OEN<<17) | (PA2_OEN<<18)	| (PA3_OEN<<19) |
		(PA4_OEN<<20)	| (PA5_OEN<<21) | (PA6_OEN<<22)	| (PA7_OEN<<23) |
		(PA0_DO<<24)	| (PA1_DO<<25)	| (PA2_DO<<26)	| (PA3_DO<<27) |
		(PA4_DO<<28)	| (PA5_DO<<29)	| (PA6_DO<<30)	| (PA7_DO<<31) ;
	reg_pa_mode =
		(PA0_DS<<8)		| (PA1_DS<<9)	| (PA2_DS<<10)	| (PA3_DS<<11) |
		(PA4_DS<<12)	| (PA5_DS<<13)	| (PA6_DS<<14)	| (PA7_DS<<15) |
		(PA0_MODE<<16)	| (PA1_MODE<<17)| (PA2_MODE<<18)| (PA3_MODE<<19) |
		(PA4_MODE<<20)	| (PA5_MODE<<21)| (PA6_MODE<<22)| (PA7_MODE<<23);

	reg_pb_io =
		(PB0_IE<<8) 	| (PB1_IE<<9)	| (PB2_IE<<10)	| (PB3_IE<<11) |
		(PB4_IE<<12)	| (PB5_IE<<13)	| (PB6_IE<<14)	| (PB7_IE<<15) |
		(PB0_OEN<<16)	| (PB1_OEN<<17) | (PB2_OEN<<18)	| (PB3_OEN<<19) |
		(PB4_OEN<<20)	| (PB5_OEN<<21) | (PB6_OEN<<22)	| (PB7_OEN<<23) |
		(PB0_DO<<24)	| (PB1_DO<<25)	| (PB2_DO<<26)	| (PB3_DO<<27) |
		(PB4_DO<<28)	| (PB5_DO<<29)	| (PB6_DO<<30)	| (PB7_DO<<31) ;
	reg_pb_mode =
		(PB0_DS<<8)		| (PB1_DS<<9)	| (PB2_DS<<10)	| (PB3_DS<<11) |
		(PB4_DS<<12)	| (PB5_DS<<13)	| (PB6_DS<<14)	| (PB7_DS<<15) |
		(PB0_MODE<<16)	| (PB1_MODE<<17)| (PB2_MODE<<18)| (PB3_MODE<<19) |
		(PB4_MODE<<20)	| (PB5_MODE<<21)| (PB6_MODE<<22)| (PB7_MODE<<23);

	reg_pc_io =
		(PC0_IE<<8) 	| (PC1_IE<<9)	| (PC2_IE<<10)	| (PC3_IE<<11) |
		(PC4_IE<<12)	| (PC5_IE<<13)	| (PC6_IE<<14)	| (PC7_IE<<15) |
		(PC0_OEN<<16)	| (PC1_OEN<<17) | (PC2_OEN<<18)	| (PC3_OEN<<19) |
		(PC4_OEN<<20)	| (PC5_OEN<<21) | (PC6_OEN<<22)	| (PC7_OEN<<23) |
		(PC0_DO<<24)	| (PC1_DO<<25)	| (PC2_DO<<26)	| (PC3_DO<<27) |
		(PC4_DO<<28)	| (PC5_DO<<29)	| (PC6_DO<<30)	| (PC7_DO<<31) ;
	reg_pc_mode =
		(PC0_DS<<8)		| (PC1_DS<<9)	| (PC2_DS<<10)	| (PC3_DS<<11) |
		(PC4_DS<<12)	| (PC5_DS<<13)	| (PC6_DS<<14)	| (PC7_DS<<15) |
		(PC0_MODE<<16)	| (PC1_MODE<<17)| (PC2_MODE<<18)| (PC3_MODE<<19) |
		(PC4_MODE<<20)	| (PC5_MODE<<21)| (PC6_MODE<<22)| (PC7_MODE<<23);

	reg_pd_io =
		(PD0_IE<<8) 	| (PD1_IE<<9)	| (PD2_IE<<10)	| (PD3_IE<<11) |
		(PD4_IE<<12)	| (PD5_IE<<13)	| (PD6_IE<<14)	| (PD7_IE<<15) |
		(PD0_OEN<<16)	| (PD1_OEN<<17) | (PD2_OEN<<18)	| (PD3_OEN<<19) |
		(PD4_OEN<<20)	| (PD5_OEN<<21) | (PD6_OEN<<22)	| (PD7_OEN<<23) |
		(PD0_DO<<24)	| (PD1_DO<<25)	| (PD2_DO<<26)	| (PD3_DO<<27) |
		(PD4_DO<<28)	| (PD5_DO<<29)	| (PD6_DO<<30)	| (PD7_DO<<31) ;
	reg_pd_mode =
		(PD0_DS<<8)		| (PD1_DS<<9)	| (PD2_DS<<10)	| (PD3_DS<<11) |
		(PD4_DS<<12)	| (PD5_DS<<13)	| (PD6_DS<<14)	| (PD7_DS<<15) |
		(PD0_MODE<<16)	| (PD1_MODE<<17)| (PD2_MODE<<18)| (PD3_MODE<<19) |
		(PD4_MODE<<20)	| (PD5_MODE<<21)| (PD6_MODE<<22)| (PD7_MODE<<23);

	reg_pe_io =
		(PE0_IE<<8) 	| (PE1_IE<<9)	| (PE2_IE<<10)	| (PE3_IE<<11) |
		(PE4_IE<<12)	| (PE5_IE<<13)	| (PE6_IE<<14)	| (PE7_IE<<15) |
		(PE0_OEN<<16)	| (PE1_OEN<<17) | (PE2_OEN<<18)	| (PE3_OEN<<19) |
		(PE4_OEN<<20)	| (PE5_OEN<<21) | (PE6_OEN<<22)	| (PE7_OEN<<23) |
		(PE0_DO<<24)	| (PE1_DO<<25)	| (PE2_DO<<26)	| (PE3_DO<<27) |
		(PE4_DO<<28)	| (PE5_DO<<29)	| (PE6_DO<<30)	| (PE7_DO<<31) ;
	reg_pe_mode =
		(PE0_DS<<8)		| (PE1_DS<<9)	| (PE2_DS<<10)	| (PE3_DS<<11) |
		(PE4_DS<<12)	| (PE5_DS<<13)	| (PE6_DS<<14)	| (PE7_DS<<15) |
		(PE0_MODE<<16)	| (PE1_MODE<<17)| (PE2_MODE<<18)| (PE3_MODE<<19) |
		(PE4_MODE<<20)	| (PE5_MODE<<21)| (PE6_MODE<<22)| (PE7_MODE<<23);


}

static inline void gpio_set_func(u32 pin, u32 func){
	u32 reg_adr = REG_ADR_GPIO_MODE(pin);
	u8	mbit = pin & 0xff;
	if(func == AS_GPIO){
		BM_SET(reg_adr, BM_CLR_MASK_V(reg_adr, mbit));
	}else{
		BM_CLR(reg_adr, BM_CLR_MASK_V(reg_adr, mbit));
	}
}
	

