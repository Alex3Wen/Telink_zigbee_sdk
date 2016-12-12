
#pragma once

/////////////////////////////////////////////////////////////////////////
//	PM PULL UP/DOWN CONTROL
/////////////////////////////////////////////////////////////////////////
#if(MCU_CORE_TYPE == MCU_CORE_5320)
enum{
	WAKEUP_SRC_GPIO0 =	BIT(0),
	WAKEUP_SRC_GPIO1 =	BIT(1),
	WAKEUP_SRC_GPIO2 =	BIT(2),
	WAKEUP_SRC_GPIO3 =	BIT(3),
	WAKEUP_SRC_ANA1 = 	BIT(4),
	WAKEUP_SRC_ANA2 =	BIT(5),
	WAKEUP_SRC_ANA3 =	BIT(6),
	WAKEUP_SRC_ANA4 =	BIT(7),
	WAKEUP_SRC_ANA5 =	BIT(8),
	WAKEUP_SRC_ANA6 =	BIT(9),
	WAKEUP_SRC_ANA7 =	BIT(10),
	WAKEUP_SRC_ANA8 =	BIT(11),
	WAKEUP_SRC_ANA9 =	BIT(12),
	WAKEUP_SRC_ANA10 =	BIT(13),
	WAKEUP_SRC_ANA11 =	BIT(14),
	WAKEUP_SRC_ANA12 =	BIT(15),
};

#define DEEPSLEEP_FUNC_PIN_CONVERT(pin)	((pin & WAKEUP_SRC_ANA3 ? GPIO_PWM1 : 0)											\
	| (pin & WAKEUP_SRC_ANA9 ? GPIO_T0 : 0) | (pin & WAKEUP_SRC_ANA10 ? GPIO_T1: 0)											\
	| (pin & WAKEUP_SRC_ANA11 ? GPIO_R0 : 0) | (pin & WAKEUP_SRC_ANA12 ? GPIO_R1: 0))

#define DEEPSLEEP_PIN_CONVERT(pin)	((pin & WAKEUP_SRC_GPIO0 ? GPIO_GP0 : 0) | (pin & WAKEUP_SRC_GPIO1 ? GPIO_GP1 : 0)		\
	| (pin & WAKEUP_SRC_GPIO2 ? GPIO_GP2 : 0) | (pin & WAKEUP_SRC_GPIO3 ? GPIO_GP3 : 0)										\
	| (pin & WAKEUP_SRC_ANA1 ? GPIO_ANA1 : 0) | (pin & WAKEUP_SRC_ANA2 ? GPIO_ANA2 : 0)										\
	| (pin & WAKEUP_SRC_ANA4 ? GPIO_ANA4 : 0) | (pin & WAKEUP_SRC_ANA5 ? GPIO_ANA5 : 0) 									\
	| (pin & WAKEUP_SRC_ANA6 ? GPIO_ANA6 : 0) | (pin & WAKEUP_SRC_ANA7 ? GPIO_ANA7 : 0) 									\
	| (pin & WAKEUP_SRC_ANA8 ? GPIO_ANA8 : 0))

#else

#if(MCU_CORE_TYPE == MCU_CORE_5332)

enum{	// for 8568
	WAKEUP_SRC_GPIO2	= BIT(0),
	WAKEUP_SRC_GPIO3	= BIT(1),
	WAKEUP_SRC_GPIO4	= BIT(2),
	WAKEUP_SRC_GPIO5	= BIT(3),
	WAKEUP_SRC_GPIO6	= BIT(4),
	WAKEUP_SRC_PWM0   	= BIT(5),
	WAKEUP_SRC_PWM1   	= BIT(6),
	WAKEUP_SRC_PWM2		= BIT(7),
	WAKEUP_SRC_GPIO16	= BIT(8),
	WAKEUP_SRC_GPIO17	= BIT(9),
	WAKEUP_SRC_GPIO18	= BIT(10),
	WAKEUP_SRC_GPIO19	= BIT(11),
	WAKEUP_SRC_GPIO22	= BIT(12),
	WAKEUP_SRC_GPIO23	= BIT(13),
	WAKEUP_SRC_GPIO24	= BIT(14),
	WAKEUP_SRC_GPIO25	= BIT(15),
	WAKEUP_SRC_I2C		= BIT(16),
	WAKEUP_SRC_SPI		= BIT(17),
	WAKEUP_SRC_USB		= BIT(19),
};

#else
enum{
	// for 86xx & 8566
	WAKEUP_SRC_PWM0  =	BIT(0),
	WAKEUP_SRC_PWM1  =	BIT(1),
	WAKEUP_SRC_PWM2  =	BIT(2),
	WAKEUP_SRC_GPIO4 =  BIT(3),
	WAKEUP_SRC_MSDO  =	BIT(4),
	WAKEUP_SRC_MSDI  =	BIT(5),
	WAKEUP_SRC_MCSN  =	BIT(6),
	WAKEUP_SRC_MCLK  =	BIT(7),
	WAKEUP_SRC_GPIO0 =	BIT(8),
	WAKEUP_SRC_GPIO1 =	BIT(9),
	WAKEUP_SRC_GPIO2 =	BIT(10),
	WAKEUP_SRC_GPIO3 =	BIT(11),
	WAKEUP_SRC_CN    =	BIT(12),
	WAKEUP_SRC_DI    =	BIT(13),
	WAKEUP_SRC_DO	 =	BIT(14),
	WAKEUP_SRC_CK    =	BIT(15),

	WAKEUP_SRC_I2C   =	BIT(16),
	WAKEUP_SRC_SPI   =	BIT(17),
	WAKEUP_SRC_USB   =	BIT(19),
};
#endif

#define DEEPSLEEP_FUNC_PIN_CONVERT(pin)	(0)

#endif

#define SUSPEND_MODE	0
#define DEEPSLEEP_MODE	1

#define WAKEUP_LEVEL_L 	0
#define WAKEUP_LEVEL_H 	1


/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
enum {
	ll_ldo_set_with_bat_lt_2p0 		= 0,
	ll_ldo_set_with_bat_2p0_to_2p25 = 1,
	ll_ldo_set_with_bat_2p25_to_2p5 = 2,
	ll_ldo_set_with_bat_2p5_to_2p8	= 3,
	ll_ldo_set_with_bat_2p8_to_3p0	= 4,
	ll_ldo_set_with_bat_3p0_to_3p3	= 5,
	ll_ldo_set_with_bat_gt_3p3		= 6,
};

void ll_ldo_set (int sel);

void pm_init(void);
void cpu_low_power_mode_init ();
void cpu_low_power_mode_en (int en);
//deep-sleep mode must use this function for resume 1.8V analog register
void cpu_wakeup_init(void);
void cpu_sleep_wakeup (int deepsleep, int tick_32k, int wakeup_src, int wakeup_level);
void cpu_sleep_wait ();

#if(MCU_CORE_TYPE == MCU_CORE_5330 || MCU_CORE_TYPE == MCU_CORE_5332)

static inline void usb_dp_pullup_en (int en)
{
	unsigned char reg0a = ReadAnalogReg(0x0a);
	if (en)
		WriteAnalogReg (0x0a, reg0a & 0x7f);
	else
		WriteAnalogReg (0x0a, reg0a | 0x80);

}

#elif (MCU_CORE_TYPE == MCU_CORE_3520)

#define usb_dp_pullup_en(en)

#else

#define  usb_dp_pullup_en(en)	do {gpio_write (GPIO_DI, en);gpio_set_output_en (GPIO_DI, en);}while(0)

#endif
////////////////////////////////////////////////////////////////////////////////
#if(MCU_CORE_TYPE == MCU_CORE_5330 || MCU_CORE_TYPE == MCU_CORE_5332)
enum  ADC_CHANNALE {
	adc_ana0 = 0x01,
	adc_ana1 = 0x02,
	adc_ana2 = 0x03,
	adc_ana3 = 0x04,

	adc_avdd = 0x0c
};
enum  COMP_CHANNALE {
	comp_ana0 = 0x00,
	comp_ana1 = 0x02,
	comp_ana2 = 0x04,
	comp_ana3 = 0x06,
	comp_ana4 = 0x08,
	comp_ana5 = 0x0a,
	comp_ana6 = 0x0c,
	comp_ana7 = 0x0e,
	comp_gp2 = 0x10,
	comp_gp3 = 0x12,
	comp_gp4 = 0x14,
	comp_gp5 = 0x16,
	comp_gp6 = 0x18,
	comp_avdd = 0x1a
};

#define SCALING_SELECT_QUARTER 		0x00//25%
#define SCALING_SELECT_HALF 		0x20//50%
#define SCALING_SELECT_3QUARTER 	0x40//75%
#define SCALING_SELECT_FULL 		0x60//100%

#define REF_VOLTAGE_SEL_0			0x00//float
#define REF_VOLTAGE_SEL_1			0x01//989mv
#define REF_VOLTAGE_SEL_2			0x02//937mv
#define REF_VOLTAGE_SEL_3			0x03//730mv
#define REF_VOLTAGE_SEL_4			0x04//832mv
#define REF_VOLTAGE_SEL_5			0x05//ana3
#define REF_VOLTAGE_SEL_6			0x06//887mv
#define REF_VOLTAGE_SEL_7			0x07//avddh


#define		V1P0			0
#define		V1P1			1
#define		V1P25			2
#define		V1P4			3

#ifndef		VBAT_LOW_LEVLE
#define		VBAT_LOW_LEVLE		V1P0
#endif

#ifndef		VBAT_CHANNEL
#if BATTERY_DETECTION_WITH_LDO_SET
#define		VBAT_CHANNEL		comp_avdd
#else
#define		VBAT_CHANNEL		comp_ana0
#endif
#endif

#define		V1P0_REF			REF_VOLTAGE_SEL_1
#define		V1P0_SCALE			SCALING_SELECT_FULL
#define		V1P0_AHALF			0

#define		V1P1_REF			REF_VOLTAGE_SEL_4
#define		V1P1_SCALE			SCALING_SELECT_3QUARTER
#define		V1P1_AHALF			0

#define		V1P25_REF			REF_VOLTAGE_SEL_4
#define		V1P25_SCALE			SCALING_SELECT_FULL
#define		V1P25_AHALF			1

#define		V1P4_REF			REF_VOLTAGE_SEL_2
#define		V1P4_SCALE			SCALING_SELECT_FULL
#define		V1P4_AHALF			1

#define		V1P45_REF			REF_VOLTAGE_SEL_3
#define		V1P45_SCALE			SCALING_SELECT_HALF
#define		V1P45_AHALF			0

#define 	V2P0_REF			REF_VOLTAGE_SEL_1
#define 	V2P0_SCALE			SCALING_SELECT_3QUARTER
#define 	V2P0_AHALF			1

#define 	V2P2_REF			REF_VOLTAGE_SEL_3
#define 	V2P2_SCALE			SCALING_SELECT_HALF
#define 	V2P2_AHALF			1

#define 	V2P5_REF			REF_VOLTAGE_SEL_4
#define 	V2P5_SCALE			SCALING_SELECT_HALF
#define 	V2P5_AHALF			1

#define 	V2P8_REF			REF_VOLTAGE_SEL_2
#define 	V2P8_SCALE			SCALING_SELECT_HALF
#define 	V2P8_AHALF			1

#define 	V3P0_REF			REF_VOLTAGE_SEL_1
#define 	V3P0_SCALE			SCALING_SELECT_HALF
#define 	V3P0_AHALF			1


#define		VBAT_LOW_SCALE		(VBAT_LOW_LEVLE==V1P0 ? V1P0_SCALE | V1P0_AHALF : V1P1_SCALE | V1P1_AHALF)
#define		VBAT_LOW_REF		(VBAT_LOW_LEVLE==V1P0 ? V1P0_REF : V1P1_REF)

int battery_detection_with_ldo (u8 chn, int set);
int battery_direct_detection (u8 chn, int set);

static inline	int battery_low () {
	analog_write(0x02, VBAT_LOW_REF | 0xe0);
	analog_write(0x03, VBAT_LOW_SCALE | VBAT_CHANNEL);
	WaitUs (50);
	return analog_read(0x23) & 0x01;
}

#elif(MCU_CORE_TYPE == MCU_CORE_5328)

#ifndef		VBAT_CHANNEL

#if BATTERY_DETECTION_WITH_LDO_SET
#define		VBAT_CHANNEL		adc_avdd
#else
#define		VBAT_CHANNEL		adc_ana0
#endif

#endif

enum  ADC_CHANNALE {
	adc_ana0 = 0x01,
	adc_ana1 = 0x02,
	adc_ana2 = 0x03,
	adc_ana3 = 0x04,

	adc_avdd = 0x0c
};
int battery_detection_with_ldo (u8 chn, int set);

#define battery_direct_detection(chn,set)	battery_detection_with_ldo (chn, set)

static inline	int battery_low () {
	return !battery_detection_with_ldo ( VBAT_CHANNEL, 0 );
}

#else

int battery_detection_with_ldo (u8 chn, int set);
static inline	int battery_low () {
	//analog_write(0x02, VBAT_LOW_REF | 0xe0);
	//analog_write(0x03, VBAT_LOW_SCALE | VBAT_CHANNEL);
	WaitUs (50);
	return analog_read(0x23) & 0x01;
}

#endif

static inline void osc_cap_adjust( u8 cap){
	WriteAnalogReg( 0x81, cap );
}

