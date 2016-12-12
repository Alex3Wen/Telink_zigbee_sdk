#pragma once

#include "../mcu/compiler.h"
#include "../common/bit.h"
#include "../common/types.h"

#if defined(__cplusplus)
	extern "C" {
#endif

#ifndef WIN32
#define REG_BASE_ADDR			0x800000
#else
extern u8 reg_simu_buffer[];
#define REG_BASE_ADDR			(&reg_simu_buffer[0])
#endif

#define REG_ADDR8(a)			(*(volatile u8*) (REG_BASE_ADDR + a))
#define REG_ADDR16(a)			(*(volatile u16*)(REG_BASE_ADDR + a))
#define REG_ADDR32(a)			(*(volatile u32*)(REG_BASE_ADDR + a))

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
enum {
	FLD_RF_TX_INTR = 0,
	FLD_RF_RX_INTR = 0,
};

/****************************************************
  secondary spi regs struct: begin  addr : 0x08
 *****************************************************/
#define reg_spi_data			REG_ADDR8(0x08)
#define reg_spi_ctrl			REG_ADDR8(0x09)
enum{
	FLD_SPI_CS = 				BIT(0),
	FLD_SPI_MASTER_MODE_EN = 	BIT(1),
	FLD_SPI_DATA_OUT_DIS = 		BIT(2),
	FLD_SPI_RD = 				BIT(3),
	FLD_SPI_ADDR_AUTO =			BIT(4),
	FLD_SPI_BUSY = 				BIT(6),
};
#define reg_spi_sp				REG_ADDR8(0x0a)
enum{
	FLD_MASTER_SPI_CLK = 		BIT_RNG(0,6),
	FLD_CK_DO_GPIO_MODE = 		BIT(7),
};

#define reg_spi_inv_clk			REG_ADDR8(0x0b)

/****************************************************
 master spi regs struct: begin  addr : 0x0c
 *****************************************************/
#define reg_master_spi_data		REG_ADDR8(0x0c)
#define reg_master_spi_ctrl		REG_ADDR8(0x0d)

enum{
	FLD_MASTER_SPI_CS = 		BIT(0),
	FLD_MASTER_SPI_SDO = 		BIT(1),
	FLD_MASTER_SPI_CONT = 		BIT(2),
	FLD_MASTER_SPI_RD = 		BIT(3),
	FLD_MASTER_SPI_BUSY = 		BIT(4),
};

/****************************************************
 otp regs struct: begin  addr : 0x10
 *****************************************************/

#define reg_otp_addr_para		REG_ADDR16(0x10)
enum{
	FLD_OTP_PARA_ADDR = 		BIT_RNG(0,12),
	FLD_OTP_PARA_PTM = 			BIT_RNG(13,15),
};

#define reg_otp_ctrl			REG_ADDR8(0x12)
enum{
	FLD_OTP_CTRL_PCEN = 		BIT(0),
	FLD_OTP_FAST_CLK = 			BIT(1),
	FLD_OTP_OEN = 				BIT(2),
	FLD_OTP_CLK = 				BIT(3),
	FLD_OTP_PCEN_PWDN = 		BIT(4),
	FLD_OTP_WEN_PWDN = 			BIT(5),
	FLD_OTP_OEN_PWDN = 			BIT(6),
	FLD_OTP_CLK_PWDN = 			BIT(7),
};

#define reg_otp_byte_dat		REG_ADDR8(0x13)
#define reg_otp_dat				REG_ADDR32(0x14)
#define reg_otp_blk_code		REG_ADDR8(0x18)

/****************************************************
 adc regs struct: begin  addr : 0x28
 *****************************************************/
/*
#define reg_adc_setting0		REG_ADDR32(0x28)
enum{
	FLD_ADC_CHN_PGA_INP_LEFT0 = BIT_RNG(0,3),
	FLD_ADC_CHN_PGA_INP_RIGHT0=	BIT_RNG(4,7),
	FLD_ADC_CHN_PGA_INP_LEFT12 = BIT_RNG(8,11),	// reg: 0x29
	FLD_ADC_CHN_PGA_INP_RIGHT12= BIT_RNG(12,15),
	FLD_ADC_REF_CHN0 =			BIT_RNG(16,17),	// reg: 0x2a
	FLD_ADC_REF_CHN1 =			BIT_RNG(18,19),
	FLD_ADC_REF_CHN2 =			BIT_RNG(20,21),
};

#define reg_adc_setting1		REG_ADDR32(0x2c)
enum{
	FLD_ADC_AUTO_CHN0_ANA_SEL = BIT_RNG(0,4),
	FLD_ADC_DIFF_CHN0_ANA_SEL = BIT_RNG(5,7),
	FLD_ADC_AUTO_CHN1_ANA_SEL =	BIT_RNG(8,15),
	FLD_ADC_AUTO_CHN2_ANA_SEL =	BIT_RNG(16,23),
	FLD_ADC_AUTO_CHN_RESV = 	BIT_RNG(24,31),
};

#define reg_adc_samp_and_ctrl	REG_ADDR32(0x30)
enum{
	FLD_ADC_CHN0_SAMP_DIV_L = 	BIT_RNG(0,7),
	FLD_ADC_CHN0_SAMP_DIV_H =	BIT_RNG(8,15),
	FLD_ADC_CHN12_SAMP_DIV =	BIT_RNG(16,23),
	FLD_ADC_CTRL_AUTO_CHN1 = 	BIT(24),
	FLD_ADC_CTRL_AUTO_CHN2 = 	BIT(25),
	FLD_ADC_CTRL_AUD_OUTP = 	BIT(26),
	FLD_ADC_CTRL_AUTO_CHN0 =	BIT(27),
	FLD_ADC_CTRL_AUD_MODE = 	BIT_RNG(28,29),
	FLD_ADC_CTRL_DONE_SIG = 	BIT_RNG(30,31),
};
#define reg_adc_period_chn0		REG_ADDR16(0x30)
#define reg_adc_period_chn12	REG_ADDR8(0x32)

#define reg_adc_chn1_outp		REG_ADDR16(0x34)
enum{
	FLD_ADC_OUTPUT_CHN_VAL = 	BIT_RNG(0,13),
	FLD_ADC_OUTPUT_CHN_MANU_START = BIT(15),
};
#define reg_adc_chn2_outp		REG_ADDR16(0x36)
#define reg_adc_dat_byp_outp	REG_ADDR16(0x38)

#define reg_adc_chn0_input		REG_ADDR16(0x3a)

#define reg_adc_samp_clk_res	REG_ADDR16(0x3c)
enum{
	FLD_ADC_CHN0_SAMP_CYCLE = 	BIT_RNG(0,2),
	FLD_ADC_CHN0_SAMP_RESOL = 	BIT_RNG(3,5),
	FLD_ADC_CHN12_SAMP_CYCLE =	BIT_RNG(8,10),	// reg: 0x3d
};
*/
/****************************************************
 swire regs struct: begin  addr : 0x40
 *****************************************************/
#define reg_swire_data			REG_ADDR8(0x40)
#define reg_swire_ctrl1			REG_ADDR8(0x41)
enum{
	FLD_SWIRE_WR  = 			BIT(0),
	FLD_SWIRE_RD  = 			BIT(1),
	FLD_SWIRE_CMD =				BIT(2),
	FLD_SWIRE_USB_DET =			BIT(6),
	FLD_SWIRE_USB_EN =			BIT(7),
};

#define reg_swire_clk_div		REG_ADDR8(0x42)


/****************************************************
 sys regs struct: begin  addr : 0x60
 *****************************************************/
#define reg_rst0				REG_ADDR8(0x60)
#define reg_rst1				REG_ADDR8(0x61)
#define reg_rst2				REG_ADDR8(0x62)
#define reg_rst_clk0			REG_ADDR32(0x60)
enum{
	FLD_RST_MCU = 				BIT(0),
	FLD_RST_MCIC = 				BIT(1),
	FLD_RST_USB = 				BIT(2),
	FLD_RST_I2C =	 			BIT(3),
	FLD_RST_SPI = 				BIT(4),
	FLD_RST_MSPI =				BIT(5),
	FLD_RST_AIF = 				BIT(6),
	FLD_RST_ADC = 				BIT(7),
	FLD_RST_UART = 				BIT(8),
	FLD_RST_SWR_S = 			BIT(9),
	FLD_RST_PWM =				BIT(10),
	FLD_RST_LCD = 				BIT(11),
	FLD_RST_SDM = 				BIT(12),
	FLD_RST_SPWM = 				BIT(13),
	FLD_RST_TC =				BIT(14),
	FLD_RST_ALGCC =				BIT(15),
	FLD_RST_SBC =				0,
	FLD_RST_AUD =				0,
	FLD_RST_DFIFO =				0,
	FLD_RST_SOFT_MCU =			0,
	FLD_RST_SOFT_MCIC =			0,
	FLD_RST_RSV =				BIT(23),

	FLD_RST_MCU_EN	=			BIT(24),
	FLD_RST_MCIC_EN	=			BIT(25),
	FLD_RST_USB_EN	=			BIT(26),
	FLD_RST_I2C_EN	=			BIT(27),
	FLD_CLK_SBC_EN =			0,
	FLD_CLK_DIFIO_EN =			0,
	FLD_CLK_AUD_EN	=			0,
};

#define reg_clk_en				REG_ADDR16(0x64)
enum{
	FLD_CLK_MCU_EN =			BIT(0),
	FLD_CLK_USB_PHY_EN =		BIT(1),
	FLD_CLK_USB_EN =			BIT(2),
	FLD_CLK_I2C_EN =			BIT(3),
	FLD_CLK_SPI_EN = 			BIT(4),
	FLD_CLK_MSPI_EN = 			BIT(5),
	FLD_CLK_UART_EN = 			BIT(6),
	FLD_CLK_SWIRE_EN =			BIT(7),

	FLD_CLK_AIF_EN =			BIT(9),
	FLD_CLK_ADC_EN =			BIT(10),
	FLD_CLK_PWM_EN = 			BIT(11),
	FLD_CLK_LCD_EN = 			BIT(12),
	FLD_CLK_SDM_EN = 			BIT(13),
	FLD_CLK_SPWM_EN =			BIT(14),

};
#define reg_clk_en2				REG_ADDR8(0x66)
enum{
	FLD_CLK2_TC =				BIT(0),
	FLD_CLK2_ALGCC =				BIT(1),
	FLD_CLK2_DCDC =				BIT(2),
};

#define reg_pwdn_ctrl			REG_ADDR8(0x67)
enum{
	FLD_PWDN_CTRL_REBOOT = 		BIT(1),
	FLD_PWDN_CTRL_SLEEP =		BIT(0),
};

#define reg_mcu_ctrl			REG_ADDR8(0x67)
enum{
	FLD_MCU_PWDN =				BIT(0),
	FLD_POWER_ON_RST =			BIT(1),
	FLD_MCU_LOW_POWER =			BIT(2),
};

#define	CLOCK_OSC_MHZ			48000000
#define reg_clk_sel				REG_ADDR8(0x68)
enum{
	FLD_CLK_SEL_DIV = 			BIT_RNG(0,5),
	FLD_CLK_SEL_SRC =			BIT_RNG(6,7),
	FLD_CLK_SEL_RC =			0,
	FLD_CLK_SEL_PAD =			2,
	FLD_CLK_SEL_PLL =			3,
};

#define	reg_dcdc_clk			REG_ADDR8(0x69)
#define reg_clk_dcdc_sel		REG_ADDR8(0x69)
enum{
	FLD_CLK_DCDC_SEL_DIV = 			BIT_RNG(0,4),
	FLD_CLK_DCDC_SEL_SRC =			BIT_RNG(5,6),
	FLD_CLK_DCDC_EN =				BIT(7),
	FLD_CLK_DCDC_SEL_RC =			0,
	FLD_CLK_DCDC_SEL_400M =			1,
	FLD_CLK_DCDC_SEL_PAD =			2,
	FLD_CLK_DCDC_SEL_PLL =			3,
};

#define reg_clk_usb_phy_sel		REG_ADDR8(0x6a)
enum{
	FLD_CLK_USB_PHY_SEL_DIV = 			BIT_RNG(0,4),
	FLD_CLK_USB_PHY_SEL_SRC =			BIT_RNG(5,6),
	FLD_CLK_USB_PHY_SEL_EN =			BIT(7),
	FLD_CLK_USB_PHY_SEL_400M =			0,
	//FLD_CLK_USB_PHY_SEL_400M =			1,
	FLD_CLK_USB_PHY_SEL_PAD =			2,
	FLD_CLK_USB_PHY_SEL_PLL =			3,
};

#define reg_clk_adc_sel		REG_ADDR8(0x6b)
enum{
	FLD_CLK_ADC_SEL_DIV = 			BIT_RNG(0,4),
	FLD_CLK_ADC_SEL_SRC =			BIT_RNG(5,6),
	FLD_CLK_ADC_SEL_EN =			BIT(7),
	FLD_CLK_ADC_SEL_RC =			0,
	FLD_CLK_ADC_SEL_PAD =			2,
	FLD_CLK_ADC_SEL_PLL =			3,
};

#define reg_pwdn_en			REG_ADDR8(0x6c)
enum{
	FLD_PWDN_SRC_I2C = 		BIT(0),
	FLD_PWDN_SRC_SPI =		BIT(1),
	FLD_PWDN_SRC_USB =		BIT(2),

	FLD_PWDN_SRC_GPIO =		BIT(4),

	FLD_PWDN_CRYSTAL	 =	BIT(6),

};

#define reg_wakeup_en			REG_ADDR8(0x6d)
enum{
	FLD_WAKEUP_SRC_I2C = 		BIT(0),
	FLD_WAKEUP_SRC_SPI =		BIT(1),
	FLD_WAKEUP_SRC_USB =		BIT(2),

	FLD_WAKEUP_SRC_GPIO =		BIT(4),
};


#define reg_usb_resume			REG_ADDR8(0x70)
enum{
	FLD_USB_RESUME_MODE = 			BIT(0),
	FLD_USB_RESUME = 				BIT(1),
};

/****************************************************
 dev_id regs struct: begin  addr : 0x74
 *****************************************************/
#define reg_id_wr_en			REG_ADDR8(0x74)
#define reg_product_id			REG_ADDR32(0x7c)
#define reg_func_id				REG_ADDR8(0x7c)
enum{
	FLD_ID_USB_SYS_CLOCK = 		BIT(0),
	FLD_ID_MAC_CLOCK = 			BIT(1),
	FLD_ID_SBC_CLOCK = 			BIT(2),
	FLD_ID_RISC32_ENABLE = 		BIT(3),
	FLD_ID_I2S_ENABLE = 		BIT(4),
	FLD_ID_SDM_ENABLE = 		BIT(5),
	FLD_ID_RF_ENABLE = 			BIT(6),
	FLD_ID_ZB_ENABLE = 			BIT(7),
};

#define reg_ver_id				REG_ADDR8(0x7d)
#define reg_prod_id				REG_ADDR16(0x7e)

/****************************************************
 PWM regs struct: begin  addr : 0xac
 *****************************************************/
#define reg_pwm0_setting1		REG_ADDR16(0x200)
enum{
	FLD_PWM_CMP  = 				BIT_RNG(0,7),
	FLD_PWM_MAX  = 				BIT_RNG(8,15),
};
#define reg_pwm0_setting2		REG_ADDR8(0x202)
enum{
	FLD_PWM_CLK_SEL  = 			BIT_RNG(0,2),
	FLD_PWM_OUT_MODE  = 		BIT_RNG(3,4),
	FLD_PWM_WAVEFORM_MODE  =	BIT_RNG(5,6),
	FLD_PWM_POL =				BIT(7),
};

#define reg_pwm0_en				REG_ADDR8(0x203)
enum{
	FLD_PWM_OUT_INTR  =			BIT(0),
	FLD_PWM_OF_INTR  = 			BIT(1),			// overflow interrupt
	FLD_PWM_EN  =				BIT(2), 		// overflow interrupt
};

#define reg_pwm1_setting1		REG_ADDR16(0x204)
#define reg_pwm1_setting2		REG_ADDR8(0x206)
#define reg_pwm1_en				REG_ADDR8(0x207)


//////  analog controls 0xb8 ///////
//#define reg_ana_ctrl32			REG_ADDR32(0x8)	// for performance, set addr and data at a time
//#define reg_ana_addr_data		REG_ADDR16(0xb8)	// for performance, set addr and data at a time
//#define reg_ana_addr			REG_ADDR8(0xb8)
//#define reg_ana_data			REG_ADDR8(0xb9)
//#define reg_ana_ctrl			REG_ADDR8(0xba)

// 文档不正确，请使用以下定义
enum{
	FLD_ANA_BUSY  = 			BIT(0),
	FLD_ANA_RSV	=				BIT(4),
	FLD_ANA_RW  = 				BIT(5),
	FLD_ANA_START  = 			BIT(6),
	FLD_ANA_CYC  = 				BIT(7),
};
/****************************************************
 audio regs struct: begin  addr : 0x100
 *****************************************************/
#define reg_ctrl_ep_ptr			REG_ADDR8(0x100)
#define reg_ctrl_ep_dat			REG_ADDR8(0x101)
#define reg_ctrl_ep_ctrl		REG_ADDR8(0x102)

// same for all endpoints
enum{
	FLD_EP_DAT_ACK  = 			BIT(0),
	FLD_EP_DAT_STALL =			BIT(1),
	FLD_EP_STA_ACK = 			BIT(2),
	FLD_EP_STA_STALL = 			BIT(3),
};

#define reg_ctrl_ep_irq_sta		REG_ADDR8(0x103)
enum{
	FLD_CTRL_EP_IRQ_TRANS  = 	BIT_RNG(0,3),
	FLD_CTRL_EP_IRQ_SETUP  =	BIT(4),
	FLD_CTRL_EP_IRQ_DATA  =		BIT(5),
	FLD_CTRL_EP_IRQ_STA  = 		BIT(6),
	FLD_CTRL_EP_IRQ_INTF  = 	BIT(7),
};

#define reg_ctrl_ep_irq_mode	REG_ADDR8(0x104)
enum{
	FLD_CTRL_EP_AUTO_ADDR = 	BIT(0),
	FLD_CTRL_EP_AUTO_CFG =		BIT(1),
	FLD_CTRL_EP_AUTO_INTF =		BIT(2),
	FLD_CTRL_EP_AUTO_STA =		BIT(3),
	FLD_CTRL_EP_AUTO_SYN =		BIT(4),
	FLD_CTRL_EP_AUTO_DESC =		BIT(5),
	FLD_CTRL_EP_AUTO_FEAT =		BIT(6),
	FLD_CTRL_EP_AUTO_STD =		BIT(7),
};

#define reg_usb_ctrl			REG_ADDR8(0x105)
enum{
	FLD_USB_CTRL_AUTO_CLK = 	BIT(0),
	FLD_USB_CTRL_LOW_SPD = 		BIT(1),
	FLD_USB_CTRL_LOW_JITT =		BIT(2),
	FLD_USB_CTRL_TST_MODE = 	BIT(3),
};

#define reg_usb_cyc_cali		REG_ADDR16(0x106)
#define reg_usb_mdev			REG_ADDR8(0x10a)
#define reg_usb_host_conn		REG_ADDR8(0x10b)
enum{
	FLD_USB_MDEV_SELF_PWR = 	BIT(0),
	FLD_USB_MDEV_SUSP_STA = 	BIT(1),
};

#define reg_usb_sups_cyc_cali	REG_ADDR8(0x10c)
#define reg_usb_intf_alt		REG_ADDR8(0x10d)

#define reg_usb_ep8123_ptr		REG_ADDR32(0x110)
#define reg_usb_ep8_ptr			REG_ADDR8(0x110)
#define reg_usb_ep1_ptr			REG_ADDR8(0x111)
#define reg_usb_ep2_ptr			REG_ADDR8(0x112)
#define reg_usb_ep3_ptr			REG_ADDR8(0x113)
#define reg_usb_ep4567_ptr		REG_ADDR32(0x114)
#define reg_usb_ep4_ptr			REG_ADDR8(0x114)
#define reg_usb_ep5_ptr			REG_ADDR8(0x115)
#define reg_usb_ep6_ptr			REG_ADDR8(0x116)
#define reg_usb_ep7_ptr			REG_ADDR8(0x117)
#define reg_usb_ep_ptr(i)		REG_ADDR8(0x110+((i) & 0x07))

#define reg_usb_ep8123_dat		REG_ADDR32(0x118)
#define reg_usb_ep8_dat			REG_ADDR8(0x118)
#define reg_usb_ep1_dat			REG_ADDR8(0x119)
#define reg_usb_ep2_dat			REG_ADDR8(0x11a)
#define reg_usb_ep3_dat			REG_ADDR8(0x11b)
#define reg_usb_ep4567_dat		REG_ADDR32(0x11c)
#define reg_usb_ep4_dat			REG_ADDR8(0x11c)
#define reg_usb_ep5_dat			REG_ADDR8(0x11d)
#define reg_usb_ep6_dat			REG_ADDR8(0x11e)
#define reg_usb_ep7_dat			REG_ADDR8(0x11f)
#define reg_usb_ep_dat(i)		REG_ADDR8(0x118+((i) & 0x07))

#define reg_usb_ep8_ctrl		REG_ADDR8(0x120)
#define reg_usb_ep1_ctrl		REG_ADDR8(0x121)
#define reg_usb_ep2_ctrl		REG_ADDR8(0x122)
#define reg_usb_ep3_ctrl		REG_ADDR8(0x123)
#define reg_usb_ep4_ctrl		REG_ADDR8(0x124)
#define reg_usb_ep5_ctrl		REG_ADDR8(0x125)
#define reg_usb_ep6_ctrl		REG_ADDR8(0x126)
#define reg_usb_ep7_ctrl		REG_ADDR8(0x127)
#define reg_usb_ep_ctrl(i)		REG_ADDR8(0x120+((i) & 0x07))

enum{
	FLD_USB_EP_BUSY = 			BIT(0),
	FLD_USB_EP_STALL =			BIT(1),
	FLD_USB_EP_DAT0 =			BIT(2),
	FLD_USB_EP_DAT1 =			BIT(3),
	FLD_USB_EP_MONO =			BIT(6),
	FLD_USB_EP_EOF_ISO =		BIT(7),
};

#define reg_usb_ep8123_buf_addr	REG_ADDR32(0x128)
#define reg_usb_ep8_buf_addr	REG_ADDR8(0x128)
#define reg_usb_ep1_buf_addr	REG_ADDR8(0x129)
#define reg_usb_ep2_buf_addr	REG_ADDR8(0x12a)
#define reg_usb_ep3_buf_addr	REG_ADDR8(0x12b)
#define reg_usb_ep4567_buf_addr	REG_ADDR32(0x12c)
#define reg_usb_ep4_buf_addr	REG_ADDR8(0x12c)
#define reg_usb_ep5_buf_addr	REG_ADDR8(0x12d)
#define reg_usb_ep6_buf_addr	REG_ADDR8(0x12e)
#define reg_usb_ep7_buf_addr	REG_ADDR8(0x12f)
#define reg_usb_ep_buf_addr(i)	REG_ADDR8(0x128+((i) & 0x07))

#define reg_usb_ram_ctrl		REG_ADDR8(0x130)
enum{
	FLD_USB_CEN_PWR_DN =		BIT(0),
	FLD_USB_CLK_PWR_DN =		BIT(1),
	FLD_USB_WEN_PWR_DN =		BIT(3),
	FLD_USB_CEN_FUNC =			BIT(4),
};
	
#define reg_usb_iso_mode		REG_ADDR8(0x138)
#define reg_usb_irq				REG_ADDR8(0x139)
#define reg_usb_mask			REG_ADDR8(0x13a)
#define reg_usb_ep8_send_max	REG_ADDR8(0x13b)
#define reg_usb_ep8_send_thre	REG_ADDR8(0x13c)
#define reg_usb_ep8_fifo_mode	REG_ADDR8(0x13d)
enum{
	FLD_USB_ENP8_FIFO_MODE =	BIT(0),
	FLD_USB_ENP8_FULL_FLAG =	BIT(1),
};

#define	reg_cdsp_pin_cfg		REG_ADDR32(0x2cc)
/****************************************************
	ANLOG REGISTER  addr : 0x400
 *****************************************************/
#define	areg_ldodig				REG_ADDR8(0x412)
enum{
	FLD_LDODIG_TRIM	= 			BIT_RNG(0,2),
	FLD_LDOLC_TRIM	= 			BIT_RNG(3,5),
	FLD_LDOLC_PWDN	=			BIT(6),
	FLD_LDONT_PWDN	=			BIT(7),
};

#define	areg_osc400m			REG_ADDR8(0x418)
enum{
	FLD_OSC400M_TRIM	= 			BIT_RNG(0,1),
	FLD_OSC400M_PWDN	=			BIT(2),
};

#define	areg_dcdc			REG_ADDR8(0x420)
enum{
	FLD_DCDC_TRIM	= 			BIT_RNG(0,2),
	FLD_DCDC_SEL_2V	=			BIT(3),
	FLD_DCDC_RESET	=			BIT(4),
	FLD_DCDC_PWDN	=			BIT(5),
	FLD_DCDC_VPASS_2V	=			BIT(5),
};

#define	areg_saradc2			REG_ADDR16(0x42a)
enum{
	FLD_SARADC_RESET	= 		BIT(0),
	FLD_SARADC_PWDN		=		BIT(1),
};

#define	areg_pwdn				REG_ADDR8(0x432)
enum{
	FLD_UVLO_TRIM		= 		BIT_RNG(0,1),
	FLG_PWDN_BANDGAP	=		BIT(2),
	FLG_PWDN_UVLO		=		BIT(3),
};

#define	areg_channel2			REG_ADDR8(0x437)
enum{
	FLD_CHANNEL2_PWDN	= 		0xff,
};

#define	areg_channel5			REG_ADDR8(0x43b)
enum{
	FLD_CHANNEL5_PWDN	= 		0xff,
};

#define	areg_channel3			REG_ADDR8(0x439)
enum{
	FLD_CHANNEL3_PWDN	= 		0x03,
};

#define reg_channel0			REG_ADDR8(0x434)
#define reg_channel1			REG_ADDR8(0x435)
#define reg_channel2			REG_ADDR8(0x437)
#define reg_channel3			REG_ADDR8(0x439)
#define reg_channel4			REG_ADDR8(0x43a)
#define reg_channel5			REG_ADDR8(0x43b)

/****************************************************
 dma mac regs struct: begin  addr : 0x500
 *****************************************************/
#define reg_dma0_addr			REG_ADDR16(0x500)
#define reg_dma0_ctrl			REG_ADDR16(0x502)
#define reg_dma1_addr			REG_ADDR16(0x504)
#define reg_dma1_ctrl			REG_ADDR16(0x506)
#define reg_dma2_addr			REG_ADDR16(0x508)
#define reg_dma2_ctrl			REG_ADDR16(0x50a)
#define reg_dma3_addr			REG_ADDR16(0x50c)
#define reg_dma3_ctrl			REG_ADDR16(0x50e)
#define reg_dma4_addr			REG_ADDR16(0x510)
#define reg_dma4_ctrl			REG_ADDR16(0x512)
#define reg_dma5_addr			REG_ADDR16(0x514)
#define reg_dma5_ctrl			REG_ADDR16(0x516)

enum{
	FLD_DMA_BUF_SIZE =			BIT_RNG(0,7),
	FLD_DMA_WR_MEM =			BIT(8),
	FLD_DMA_PINGPONG_EN =		BIT(9),
	FLD_DMA_FIFO_EN =			BIT(10),
	FLD_DMA_AUTO_MODE =			BIT(11),
	FLD_DMA_BYTE_MODE =			BIT(12),
};

#define reg_dma_chn_en			REG_ADDR8(0x520)
#define reg_dma_chn_irq_msk		REG_ADDR8(0x521)
#define reg_dma_tx_rdy0			REG_ADDR8(0x524)
#define reg_dma_tx_rdy1			REG_ADDR8(0x525)
#define reg_dma_rx_rdy0			REG_ADDR8(0x526)
#define reg_dma_irq_src			reg_dma_rx_rdy0
#define reg_dma_rx_rdy1			REG_ADDR8(0x527)
enum{
	FLD_DMA_ETH_RX =			BIT(0),		//  not sure ???
	FLD_DMA_ETH_TX =			BIT(1),
	FLD_DMA_RF_RX =				BIT(2),		//  not sure ???
	FLD_DMA_RF_TX =				BIT(3),
};

//  The default channel assignment
#define reg_dma_eth_rx_addr		reg_dma0_addr
#define reg_dma_eth_rx_ctrl		reg_dma0_ctrl
#define reg_dma_eth_tx_addr		reg_dma1_addr

#define reg_dma_rf_rx_addr		reg_dma2_addr
#define reg_dma_rf_rx_ctrl		reg_dma2_ctrl
#define reg_dma_rf_tx_addr		reg_dma3_addr
#define reg_dma_rf_tx_ctrl		reg_dma3_ctrl

/****************************************************
 audio regs struct: begin  addr : 0x560
 *****************************************************/
#define reg_aud_ctrl			REG_ADDR8(0x560)
enum{
	FLD_AUD_MODE_SEL =			BIT(0),
	FLD_AUD_I2S_PLAY_EN = 		BIT(1),
	FLD_AUD_SDM_EN = 			BIT(2),
	FLD_AUD_ISO_EN = 			BIT(3),
	FLD_AUD_I2S_REC_EN = 		BIT(4),
	FLD_AUD_I2S_INTF_EN = 		BIT(5),
	FLD_AUD_GRP_EN = 			BIT(6),
	FLD_AUD_HPF_EN = 			BIT(7),
};

#define reg_aud_mid_grp			REG_ADDR8(0x561)
#define reg_aud_vol_ctrl		REG_ADDR8(0x562)
#define reg_pwm_ctrl			REG_ADDR8(0x563)
#define reg_ascl_tune			REG_ADDR32(0x564)
#define reg_i2s_fct				REG_ADDR8(0x565)
#define reg_ascl_step			REG_ADDR16(0x566)

/****************************************************
 gpio regs struct: begin  0x580
 *****************************************************/
enum{
	ADR_GPIO_DI		= 			0,
	ADR_GPIO_IE		= 			1,
	ADR_GPIO_OEN	= 			2,
	ADR_GPIO_DO		=			3,

	ADR_GPIO_DS		= 			5,
	ADR_GPIO_MODE	= 			6,
	ADR_GPIO		= 			0x80,
};

#define reg_pa_io					REG_ADDR32(0x80)
#define reg_pa_mode					REG_ADDR32(0x84)
#define reg_pb_io					REG_ADDR32(0x88)
#define reg_pb_mode					REG_ADDR32(0x8c)
#define reg_pc_io					REG_ADDR32(0x90)
#define reg_pc_mode					REG_ADDR32(0x94)
#define reg_pd_io					REG_ADDR32(0x98)
#define reg_pd_mode					REG_ADDR32(0x9c)
#define reg_pe_io					REG_ADDR32(0xa0)
#define reg_pe_mode					REG_ADDR32(0xa4)

#define reg_gpio_polarity			REG_ADDR32(0xa8)
#define	reg_gpio_pe_polarity		REG_ADDR8(0xac)
#define reg_gpio_irq_wakeup_en		REG_ADDR32(0xb0)
#define	reg_gpio_pe_wakeup_en		REG_ADDR8(0xb4)

#define	reg_gpio_sel0				REG_ADDR8(0xb5)
#define	reg_gpio_sel1				REG_ADDR8(0xb6)
#define	reg_gpio_sel2				REG_ADDR8(0xb7)
enum{
	FLD_GPIO_WAKEUP_SRC24_26 =	BIT_RNG(0,2),
	FLD_GPIO_WAKEUP_EN =		BIT(30),
	FLD_GPIO_IRQ_EN =			BIT(31),
};


/****************************************************
 timer regs struct: begin  0x620
 *****************************************************/
#define reg_tmr_ctrl			REG_ADDR32(0x620)
#define reg_tmr_ctrl16			REG_ADDR16(0x620)		// 因为0x622 不要写
enum{
	FLD_TMR0_EN =				BIT(0),
	FLD_TMR0_MODE =				BIT_RNG(1,2),
	FLD_TMR1_EN = 				BIT(3),
	FLD_TMR1_MODE =				BIT_RNG(4,5),
	FLD_TMR2_EN =				BIT(6),
	FLD_TMR2_MODE = 			BIT_RNG(7,8),
	FLD_TMR_WD_CAPT = 			BIT_RNG(9,22),
	FLD_TMR_WD_EN =				BIT(23),
	FLD_TMR0_STA =				BIT(24),
	FLD_TMR1_STA =				BIT(25),
	FLD_TMR2_STA =				BIT(26),
	FLD_CLR_WD =				BIT(27),
};
#define WATCHDOG_TIMEOUT_COEFF	18		//  check register definiton, 0x622

#define reg_tmr_sta				REG_ADDR8(0x623)
enum{
	FLD_TMR_STA_TMR0 =			BIT(0),
	FLD_TMR_STA_TMR1 =			BIT(1),
	FLD_TMR_STA_TMR2 =			BIT(2),
	FLD_TMR_STA_WD =			BIT(3),
};

#define reg_tmr0_capt			REG_ADDR32(0x624)
#define reg_tmr1_capt			REG_ADDR32(0x628)
#define reg_tmr2_capt			REG_ADDR32(0x62c)
#define reg_tmr_capt(i)			REG_ADDR32(0x624 + ((i) << 2))
#define reg_tmr0_tick			REG_ADDR32(0x630)
#define reg_tmr1_tick			REG_ADDR32(0x634)
#define reg_tmr2_tick			REG_ADDR32(0x638)
#define reg_tmr_tick(i)			REG_ADDR32(0x630 + ((i) << 2))

#define	reg_rnd_number			REG_ADDR32(0x630)
/****************************************************
 interrupt regs struct: begin  0x640
 *****************************************************/
#define reg_irq_mask			REG_ADDR32(0x640)
#define reg_irq_pri				REG_ADDR32(0x644)
#define reg_irq_src				REG_ADDR32(0x648)
#define reg_irq_src3			REG_ADDR8(0x64a)
#define reg_irq_en				REG_ADDR8(0x643)
enum{
	FLD_IRQ_TMR0_EN =			BIT(0),
	FLD_IRQ_TMR1_EN =			BIT(1),
	FLD_IRQ_TMR2_EN =			BIT(2),
	FLD_IRQ_USB_PWDN_EN =		BIT(3),
	FLD_IRQ_DMA_EN =			BIT(4),
	FLD_IRQ_DAM_FIFO_EN =		BIT(5),
	FLD_IRQ_SBC_MAC_EN =		BIT(6),
	FLD_IRQ_HOST_CMD_EN =		BIT(7),

	FLD_IRQ_EP0_SETUP_EN =		BIT(8),
	FLD_IRQ_EP0_DAT_EN =		BIT(9),
	FLD_IRQ_EP0_STA_EN =		BIT(10),
	FLD_IRQ_SET_INTF_EN =		BIT(11),
	FLD_IRQ_IRQ4_EN =			BIT(12),
	FLD_IRQ_ZB_RT_EN =			BIT(13),
	FLD_IRQ_SW_EN =				BIT(14),
	FLD_IRQ_AN_EN =				BIT(15),

	FLD_IRQ_USB_250US_EN =		BIT(16),
	FLD_IRQ_USB_RST_EN =		BIT(17),
	FLD_IRQ_GPIO_EN =			BIT(18),
	FLD_IRQ_PM_EN =				BIT(19),
	FLD_IRQ_OCI1_EN =			BIT(20),
	FLD_IRQ_OCI0_EN =			BIT(21),
	FLD_IRQ_GPIO_RISC0_EN =		BIT(22),
	FLD_IRQ_GPIO_RISC2_EN = 	BIT(23),

	FLD_IRQ_EN =				BIT_RNG(24,31),
};


/****************************************************
 dfifo regs define:  begin  0xb00
 *****************************************************/
#define reg_dfifo0_buf			REG_ADDR32(0xb00)
#define reg_dfifo1_buf			REG_ADDR32(0xb04)
#define reg_dfifo2_buf			REG_ADDR32(0xb08)
enum{
	FLD_DFIFO_BUF_ADDR =		BIT_RNG(0,15),
	FLD_DFIFO_BUF_SIZE =		BIT_RNG(16,23),
};
#define reg_dfifo_buf_thres		REG_ADDR32(0xb0c)
enum{
	FLD_DFIFO0_LO_THRE =		BIT_RNG(0,7),
	FLD_DFIFO0_HI_THRE =		BIT_RNG(8,15),
	FLD_DFIFO1_HI_THRE =		BIT_RNG(16,23),
	FLD_DFIFO2_HI_THRE =		BIT_RNG(24,31),
};

#define reg_dfifo_ctrl			REG_ADDR32(0xb10)
enum{
	FLD_DFIFO0_AUD_IN_EN =		BIT(0),
	FLD_DFIFO1_AUD_IN_EN =		BIT(1),
	FLD_DFIFO2_AUD_IN_EN =		BIT(2),
	FLD_DFIFO0_AUD_OUT_EN =		BIT(3),
	FLD_DFIFO0_LO_INTR_EN =		BIT(4),
	FLD_DFIFO0_HI_INTR_EN =		BIT(5),
	FLD_DFIFO1_HI_INTR_EN = 	BIT(6),
	FLD_DFIFO2_HI_INTR_EN = 	BIT(7),

	FLD_DFIFO_AIN_MIC0_DAT_RS = BIT(8),
	FLD_DFIFO_AIN_MIC1_DAT_RS = BIT(9),
	FLD_DFIFO_AIN_AUD_INP = 	BIT_RNG(10,11),
	FLD_DFIFO_AIN_MONO_INP =	BIT(12),
	FLD_DFIFO_AIN_BYPASS_INP =	BIT(13),

	FLD_DFIFO_CIC_DN_SAMP =		BIT_RNG(16,23),
};

#define reg_dfifo_source		REG_ADDR8(0xb11)
enum{
	FLD_DFIFO0_SOURCE_SYNC0 =	BIT(0),
	FLD_DFIFO1_SOURCE_SYNC1 =	BIT(1),
	FLD_DFIFO2_SOURCE_DMIC =	BIT_RNG(2,3),
	FLD_DFIFO0_SOURCE_MONO =	BIT(4),
	FLD_DFIFO0_SOURCE_BYPASS =	BIT(5),
};

#define reg_dfifo_scale			REG_ADDR8(0xb12)
enum{
	FLD_DFIFO2_DEC_CIC =		BIT_RNG(0,3),
	FLD_DFIFO0_DEC_SCALE =		BIT_RNG(4,7),
};

#define reg_dfifo_sta			REG_ADDR8(0xb13)
enum{
	FLD_DFIFO0_LO_INTR =		BIT(0),
	FLD_DFIFO0_HI_INTR =		BIT(1),
	FLD_DFIFO1_HI_INTR =		BIT(2),
	FLD_DFIFO2_HI_INTR =		BIT(3),
	FLD_DFIFO0_LO_STA =			BIT(4),
	FLD_DFIFO0_HI_STA =			BIT(5),
	FLD_DFIFO1_HI_STA = 		BIT(6),
	FLD_DFIFO2_HI_STA = 		BIT(7),
};

#define reg_dfifo0_rw_ptr		REG_ADDR16(0xb14)
#define reg_dfifo1_rw_ptr		REG_ADDR16(0xb18)
#define reg_dfifo2_rw_ptr		REG_ADDR16(0xb1c)
enum{
	FLD_DFIFO_RD_PTR =			BIT_RNG(0,15),
	FLD_DFIFO_WR_PTR =			BIT_RNG(16,23),
};

#define reg_dfifo0_dat_num		REG_ADDR16(0xb20)
#define reg_dfifo1_dat_num		REG_ADDR16(0xb24)
#define reg_dfifo2_dat_num		REG_ADDR16(0xb28)

#define reg_dfifo_manu_aud_scl	REG_ADDR8(0xb2c)
#define reg_dfifo_aud_scl_dat	REG_ADDR32(0xb30)

#define reg_500k_conf			REG_ADDR32(0xe08)
enum{
	FLD_500K_CONF_CNT =			BIT_RNG(0,21),
	FLD_500K_CONF_DONE = 		BIT(22),
	FLD_500K_CONF_CAL_EN =		BIT(24),
	FLD_500K_CONF_CAL_LEN = 	BIT_RNG(28,31),
};
#define reg_500k_ctrl_cal		REG_ADDR8(0xe0b)
enum{
	FLD_500K_CAL_EN =			BIT(0),
	FLD_500K_PRECISION = 		BIT_RNG(4,7),
};
#define reg_500k_cap			REG_ADDR8(0xe0c)
#define reg_osc_ctrl			REG_ADDR8(0xe0d)
enum{
	FLD_OSC_MODE_32K_32M =		BIT(0),
	FLD_OSC_CAL_EN =			BIT(1),
	FLD_OSC_CAL_LEN = 			BIT(2),
	FLD_OSC_DEBUG =				BIT(3),
	FLD_OSC_32K_CAP_MAN_EN = 	BIT(4),
	FLD_OSC_32M_CAP_MAN_EN =	BIT(5),
};
#define reg_32m_cap_man			REG_ADDR8(0xe10)
#define reg_osc_st0				REG_ADDR8(0xe12)
#define reg_tcc_ctrl			REG_ADDR8(0xe16)
enum{
	FLD_TCC_ADJ_IN =			BIT_RNG(0,3),
	FLD_TCC_FREE_RUN =			BIT(4),
	FLD_TCC_TRK_OSC_EN =		BIT(5),
};
#define reg_tcc_st				REG_ADDR8(0xe17)
enum{
	FLD_TCC_ADJ_CD =			BIT_RNG(0,3),
	FLD_TCC_CAL_DONE =			BIT(4),
};

#if defined(__cplusplus)
}
#endif

