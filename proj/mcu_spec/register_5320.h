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

#define REG_ADDR8(a)            (*(volatile u8*) (REG_BASE_ADDR + (a)))
#define REG_ADDR16(a)            (*(volatile u16*)(REG_BASE_ADDR + (a)))
#define REG_ADDR32(a)            (*(volatile u32*)(REG_BASE_ADDR + (a)))

/****************************************************
  secondary i2c regs struct: begin  addr : 0x00
 *****************************************************/
#define reg_i2c_sp				REG_ADDR8(0)
#define reg_i2c_id				REG_ADDR8(1)
#define reg_i2c_mst				REG_ADDR8(2)
#define reg_i2c_sct1			REG_ADDR8(3)
#define reg_i2c_ad				REG_ADDR8(4)
#define reg_i2c_dw				REG_ADDR8(5)
#define reg_i2c_dr				REG_ADDR8(6)
#define reg_i2c_sct2			REG_ADDR8(7)

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
	FLD_SPI_BUSY = 				BIT(6),		// diff from doc,  bit 6 working
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

/****************************************************
 sys regs struct: begin  addr : 0x60
 *****************************************************/
#define reg_rst0                REG_ADDR8(0x60)
#define reg_rst0_16             REG_ADDR16(0x60)
#define reg_rst1                REG_ADDR8(0x61)
#define reg_rst2                REG_ADDR8(0x62)
#define reg_rst_clk0            REG_ADDR32(0x60)
enum{
	FLD_RST_SPI = 				BIT(0),
	FLD_RST_I2C = 				BIT(1),
	FLD_RST_USB = 				BIT(2),
	FLD_RST_USB_PHY = 			BIT(3),
	FLD_RST_MCU = 				BIT(4),
	FLD_RST_MAC =				BIT(5),
	FLD_RST_AIF = 				BIT(6),
	FLD_RST_BB = 				BIT(7),
	FLD_RST_GPIO = 				BIT(8),
	FLD_RST_ALGM = 				BIT(9),
	FLD_RST_DMA =				BIT(10),
	FLD_RST_UART = 				BIT(11),
	FLD_RST_PWM0 = 				BIT(12),
	FLD_RST_PWM1 = 				BIT(13),
	FLD_RST_SWR_M =				BIT(14),
	FLD_RST_SWR_S =				BIT(15),
	FLD_RST_SBC =				BIT(16),
	FLD_RST_AUD =				BIT(17),
	FLD_RST_DFIFO =				BIT(18),
	FLD_RST_ADC =				BIT(19),
	FLD_RST_SOFT_MCU =			BIT(20),
	FLD_RST_MCIC = 				BIT(21),
	FLD_RST_SOFT_MCIC =			BIT(22),
	FLD_RST_RSV =				BIT(23),
	FLD_CLK_SPI_EN =			BIT(24),
	FLD_CLK_I2C_EN =			BIT(25),
	FLD_CLK_USB_EN =			BIT(26),
	FLD_CLK_USB_PHY_EN =		BIT(27),
	FLD_CLK_MCU_EN =			BIT(28),
	FLD_CLK_MAC_EN =			BIT(29),
	FLD_CLK_AIF_EN =			BIT(30),
	FLD_CLK_ZB_EN =				BIT(31),
};

#define reg_clk_en				REG_ADDR16(0x64)
#define reg_clk_en1				REG_ADDR8(0x64)
enum{
	FLD_CLK_GPIO_EN = 			BIT(0),
	FLD_CLK_ALGM_EN = 			BIT(1),
	FLD_CLK_DMA_EN = 			BIT(2),
	FLD_CLK_UART_EN = 			BIT(3),
	FLD_CLK_PWM0_EN = 			BIT(4),
	FLD_CLK_PWM1_EN = 			BIT(5),
	FLD_CLK_PLL_EN = 			BIT(6),
	FLD_CLK_SWIRE_EN = 			BIT(7),
	FLD_CLK_SBC_EN =			BIT(8),
	FLD_CLK_AUD_EN =			BIT(9),
	FLD_CLK_DIFIO_EN = 			BIT(10),
	FLD_CLK_I2S =				BIT_RNG(11,12),
	FLD_CLK_C32K =				BIT_RNG(13,15),
};
#define reg_clk_en2				REG_ADDR8(0x65)
enum{
	FLD_CLK2_SBC_EN =			BIT(0),
	FLD_CLK2_AUD_EN =			BIT(1),
	FLD_CLK2_DIFIO_EN = 		BIT(2),
	FLD_CLK2_I2S =				BIT_RNG(3,4),
	FLD_CLK2_C32K =				BIT_RNG(5,7),
};

#define reg_clk_sel				REG_ADDR8(0x66)
enum{
	FLD_CLK_SEL_DIV = 			BIT_RNG(0,4),
	FLD_CLK_SEL_SRC =			BIT_RNG(5,7),
};

#define reg_i2s_step			REG_ADDR8(0x67)
enum{
	FLD_I2S_STEP = 				BIT_RNG(0,6),
	FLD_I2S_CLK_EN =			BIT(7),
};

#define reg_i2s_mod				REG_ADDR8(0x68)

/****************************************************
	 ADC: 0x69
 *****************************************************/
#define reg_adc_step_l			REG_ADDR8(0x69)
#define reg_adc_mod_l			REG_ADDR8(0x6a)
#define reg_adc_mod				REG_ADDR16(0x6a)
enum{
	FLD_ADC_MOD = 				BIT_RNG(0,11),
	FLD_ADC_STEP_H = 			BIT_RNG(12,14),
	FLD_ADC_CLK_EN =			BIT(15),
};
#define reg_adc_mod_h			REG_ADDR8(0x6b)
enum{
	FLD_ADC_MOD_H = 			BIT_RNG(0,3),
	FLD_ADC_MOD_H_STEP =		BIT_RNG(4,6),
	FLD_ADC_MOD_H_CLK =			BIT(7),
};

#define reg_dmic_step			REG_ADDR8(0x6c)
enum{
	FLD_DMIC_STEP = 			BIT_RNG(0,6),
	FLD_DMIC_CLK_EN =			BIT(7),
};
#define reg_dmic_mod			REG_ADDR8(0x6d)


#define reg_wakeup_en			REG_ADDR8(0x6e)
enum{
	FLD_WAKEUP_SRC_I2C = 		BIT(0),
	FLD_WAKEUP_SRC_SPI =		BIT(1),
	FLD_WAKEUP_SRC_USB =		BIT(2),
	FLD_WAKEUP_SRC_GPIO =		BIT(3),
	FLD_WAKEUP_SRC_I2C_SYN =	BIT(4),
	FLD_WAKEUP_SRC_GPIO_RM =	BIT(5),
	FLD_WAKEUP_SRC_USB_RESM =	BIT(6),
	FLD_WAKEUP_SRC_RST_SYS =	BIT(7),
};

#define reg_pwdn_ctrl			REG_ADDR8(0x6f)
enum{
	FLD_PWDN_CTRL_REBOOT = 		BIT(5),
	FLD_PWDN_CTRL_SLEEP =		BIT(7),
};

#define reg_fhs_sel				REG_ADDR8(0x70)
enum{
	FLD_FHS_SELECT = 			BIT_RNG(0,1),
};
enum{
	FHS_SEL_240M_PLL = 0,
	FHS_SEL_40M_ADC = 1,
	FHS_SEL_32M_OSC = 2,
	FHS_SEL_16M_OSC = 3,
};

/****************************************************
  OTP  addr : 0x71
 *****************************************************/
#define reg_dcdc_clk			REG_ADDR8(0x71)

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
 mac regs struct: begin  addr : 0xa0
 *****************************************************/
#define reg_mac_ctrl			REG_ADDR8(0xa0)
enum{
	FLD_MAC_CTRL_TX_EN = 		BIT(0),
	FLD_MAC_CTRL_RX_EN =		BIT(1),
	FLD_MAC_CTRL_SPD_100M =		BIT(6),
	FLD_MAC_CTRL_PHY_RST =		BIT(7),
};

#define reg_mac_irq_sta			REG_ADDR8(0xa1)
enum{
	FLD_MAC_STA_TX_DONE = 		BIT(0),
	FLD_MAC_STA_RX_DONE =		BIT(1),
	FLD_MAC_STA_TX_ERR =		BIT(2),
	FLD_MAC_STA_RX_ERR =		BIT(3),
	FLD_MAC_STA_RX_CRC =		BIT(4),
};

#define reg_mii_tx_data			REG_ADDR16(0xa2)
#define reg_mii_rx_data			REG_ADDR16(0xa4)
#define reg_mii_clk				REG_ADDR8(0xa6)
enum{
	FLD_MII_PHY_ID  = 			BIT_RNG(0,4),
	FLD_MII_CLK_DIV =			BIT_RNG(5,7),
};
#define reg_mii_ctrl			REG_ADDR8(0xa7)
enum{
	FLD_MII_INTERNAL_REG  = 	BIT_RNG(0,4),
	FLD_MII_BUSY =				BIT(5),
	FLD_MII_WR =				BIT(6),
	FLD_MII_PREAM_EN =			BIT(7),
};

/****************************************************
 PWM regs struct: begin  addr : 0xac
 *****************************************************/
#define reg_pwm0_setting1		REG_ADDR16(0xa8)
enum{
	FLD_PWM_CMP  = 				BIT_RNG(0,7),
	FLD_PWM_MAX  = 				BIT_RNG(8,15),
};
#define reg_pwm0_setting2		REG_ADDR8(0xaa)
enum{
	FLD_PWM_CLK_SEL  = 			BIT_RNG(0,2),
	FLD_PWM_OUT_MODE  = 		BIT_RNG(3,4),
	FLD_PWM_WAVEFORM_MODE  =	BIT_RNG(5,6),
	FLD_PWM_POL =				BIT(7),
};

#define reg_pwm0_en				REG_ADDR8(0xab)
enum{
	FLD_PWM_OUT_INTR  =			BIT(0),
	FLD_PWM_OF_INTR  = 			BIT(1),			// overflow interrupt
	FLD_PWM_EN  =				BIT(2), 		// overflow interrupt
};

#define reg_pwm1_setting1		REG_ADDR16(0xac)
#define reg_pwm1_setting2		REG_ADDR8(0xae)
#define reg_pwm1_en				REG_ADDR8(0xaf)

/****************************************************
 swire regs struct: begin  addr : 0xb0
 *****************************************************/
#define reg_swire_data			REG_ADDR8(0xb0)
#define reg_swire_ctrl1			REG_ADDR8(0xb1)
enum{
	FLD_SWIRE_WR  = 			BIT(0),
	FLD_SWIRE_RD  = 			BIT(1),
	FLD_SWIRE_CMD =				BIT(2),
	FLD_SWIRE_USB_DET =			BIT(6),
	FLD_SWIRE_USB_EN =			BIT(7),
};

#define reg_swire_clk_div		REG_ADDR8(0xb2)

//////  analog controls 0xb8 ///////
#define reg_ana_ctrl32			REG_ADDR32(0xb8)	// for performance, set addr and data at a time
#define reg_ana_addr_data		REG_ADDR16(0xb8)	// for performance, set addr and data at a time
#define reg_ana_addr			REG_ADDR8(0xb8)
#define reg_ana_data			REG_ADDR8(0xb9)
#define reg_ana_ctrl			REG_ADDR8(0xba)

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
/****************************************************
	RF : begin  addr : 0x4e8
 *****************************************************/
#define reg_rf_tx_mode1			REG_ADDR8(0x400)
#define reg_rf_tx_mode			REG_ADDR16(0x400)
enum{
	FLD_RF_TX_DMA_EN =			BIT(0),
	FLD_RF_TX_CRC_EN =			BIT(1),
	FLD_RF_TX_BANDWIDTH =		BIT_RNG(2,3),
	FLD_RF_TX_OUTPUT = 			BIT(4),
	FLD_RF_TX_TST_OUT =			BIT(5),
	FLD_RF_TX_TST_EN =			BIT(6),
	FLD_RF_TX_TST_MODE =		BIT(7),
	FLD_RF_TX_ZB_PN_EN =		BIT(8),
	FLD_RF_TX_ZB_FEC_EN =		BIT(9),
	FLD_RF_TX_ZB_INTL_EN =		BIT(10),	// interleaving
	FLD_RF_TX_1M2M_PN_EN =		BIT(11),
	FLD_RF_TX_1M2M_FEC_EN =		BIT(12),
	FLD_RF_TX_1M2M_INTL_EN =	BIT(13), 	// interleaving
};
#define reg_rf_tx_buf_sta		REG_ADDR32(0x41c)

#define reg_rf_rx_sense_thr		REG_ADDR8(0x422)
#define reg_rf_rx_auto			REG_ADDR8(0x426)
enum{
	FLD_RF_RX_IRR_GAIN =		BIT(0),
	FLD_RF_RX_IRR_PHASE =		BIT(1),
	FLD_RF_RX_DAC_I =			BIT(2),
	FLD_RF_RX_DAC_Q =			BIT(3),
	FLD_RF_RX_LNA_GAIN =		BIT(4),
	FLD_RF_RX_MIX2_GAIN =		BIT(5),
	FLD_RF_RX_PGA_GAIN =		BIT(6),
	FLD_RF_RX_CAL_EN =			BIT(7),
};
#define reg_rf_rx_sync			REG_ADDR8(0x427)
enum{
	FLD_RF_FREQ_COMP_EN =		BIT(0),
	FLD_RF_ADC_SYNC =			BIT(1),
	FLD_RF_ADC_INP_SIGNED =		BIT(2),
	FLD_RF_SWAP_ADC_IQ =		BIT(3),
	FLD_RF_NOTCH_FREQ_SEL =		BIT(4),
	FLD_RF_NOTCH_BAND_SEL = 	BIT(5),
	FLD_RF_NOTCH_EN = 			BIT(6),
	FLD_RF_DN_CONV_FREQ_SEL =	BIT(7),
};

#define reg_rf_rx_mode			REG_ADDR8(0x428)
enum{
	FLD_RF_RX_EN =				BIT(0),
	FLD_RF_RX_MODE_1M =			BIT(1),
	FLD_RF_RX_MODE_2M =			BIT(2),
	FLD_RF_RX_LOW_IF =			BIT(3),
	FLD_RF_RX_BYPASS_DCOC =		BIT(4),
	FLD_RF_RX_MAN_FINE_TUNE = 	BIT(5),
	FLD_RF_RX_SINGLE_CAL =		BIT(6),
	FLD_RF_RX_LOW_PASS_FILTER =	BIT(7),
};

#define reg_rf_rx_sfd            REG_ADDR8(0x42a)

#define reg_rf_rx_pilot			REG_ADDR8(0x42b)
enum{
	FLD_RF_PILOT_LEN =			BIT_RNG(0,3),
	FLD_RF_ZB_SFD_CHK =			BIT(4),
	FLD_RF_1M_SFD_CHK =			BIT(5),
	FLD_RF_2M_SFD_CHK = 		BIT(6),
	FLD_RF_ZB_OR_AUTO = 		BIT(7),
};

#define reg_rf_rx_chn_dc		REG_ADDR32(0x42c)
#define reg_rf_rx_q_chn_cal		REG_ADDR8(0x42f)
enum{
	FLD_RF_RX_DCQ_HIGH =		BIT_RNG(0,6),
	FLD_RF_RX_DCQ_CAL_START =	BIT(7),
};
#define reg_rf_rx_pel			REG_ADDR16(0x434)
#define reg_rf_rx_pel_gain		REG_ADDR32(0x434)
#define reg_rf_rx_rssi_offset	REG_ADDR8(0x439)

#define reg_rf_rx_hdx			REG_ADDR8(0x43b)
enum{
	FLD_RX_HEADER_LEN =			BIT_RNG(0,3),
	FLD_RT_TICK_LO_SEL = 		BIT(4),
	FLD_RT_TICK_HI_SEL = 		BIT(5),
	FLD_RT_TICK_FRAME = 		BIT(6),
	FLD_PKT_LEN_OUTP_EN = 		BIT(7),
};

#define reg_rf_rx_gctl			REG_ADDR8(0x43c)
enum{
	FLD_RX_GCTL_CIC_SAT_LO_EN =	BIT(0),
	FLD_RX_GCTL_CIC_SAT_HI_EN = BIT(1),
	FLD_RX_GCTL_AUTO_PWR =		BIT(2),
	FLD_RX_GCTL_ADC_RST_VAL =	BIT(4),
	FLD_RX_GCTL_ADC_RST_EN =	BIT(5),
	FLD_RX_GCTL_PWR_CHG_DET_S =	BIT(6),
	FLD_RX_GCTL_PWR_CHG_DET_N = BIT(7),
};
#define reg_rf_rx_peak			REG_ADDR8(0x43d)
enum{
	FLD_RX_PEAK_DET_SRC_EN =	BIT_RNG(0,2),
	FLD_TX_PEAK_DET_EN =		BIT(3),
	FLD_PEAK_DET_NUM =			BIT_RNG(4,5),
	FLD_PEAK_MAX_CNT_PRD =		BIT_RNG(6,7),
};

#define reg_rf_rx_status		REG_ADDR8(0x443)
enum{
	FLD_RF_RX_STATE =			BIT_RNG(0,3),
	FLD_RF_RX_STA_RSV = 		BIT_RNG(4,5),
	FLD_RF_RX_INTR = 			BIT(6),
	FLD_RF_TX_INTR =			BIT(7),
};

// The value for FLD_RF_RX_STATE  
enum{
	RF_RX_STA_IDLE = 0,
	RF_RX_STA_SET_GAIN = 1,
	RF_RX_STA_CIC_SETTLE = 2,
	RF_RX_STA_LPF_SETTLE = 3,
	RF_RX_STA_PE = 4,
	RF_RX_STA_SYN_START = 5,
	RF_RX_STA_GLOB_SYN = 6,
	RF_RX_STA_GLOB_LOCK = 7,
	RF_RX_STA_LOCAL_SYN = 8,
	RF_RX_STA_LOCAL_LOCK = 9,
	RF_RX_STA_ALIGN = 10,
	RF_RX_STA_ADJUST = 11,
	RF_RX_STA_DEMOD = 12,		// de modulation
	RF_RX_STA_FOOTER = 13,
};

#define reg_rx_rnd_mode			REG_ADDR8(0x447)
enum{
	FLD_RX_RND_SRC =			BIT(0),
	FLD_RX_RND_MANU_MODE =		BIT(1),
	FLD_RX_RND_AUTO_RD =		BIT(2),
	FLD_RX_RND_FREE_MODE =		BIT(3),
	FLD_RX_RND_CLK_DIV =		BIT_RNG(4,7),
};
#define reg_rnd_number			REG_ADDR16(0x448)

#define reg_bb_max_tick			REG_ADDR16(0x44c)
#define reg_rf_rtt				REG_ADDR32(0x454)
enum{
	FLD_RTT_CAL =				BIT_RNG(0,7),
	FLD_RTT_CYC1 =				BIT_RNG(8,15),
	FLD_RTT_LOCK =				BIT_RNG(16,23),
	FLD_RT_SD_DLY_40M =			BIT_RNG(24,27),
	FLD_RT_SD_DLY_BYPASS = 		BIT(28),
};

#define reg_rf_chn_rssi			REG_ADDR8(0x458)

#define reg_rf_rx_gain_agc(i)	REG_ADDR32(0x480+((i)<<2))

#define reg_rf_rx_dci			REG_ADDR8(0x4cb)	//  different from the document, why
#define reg_rf_rx_dcq			REG_ADDR8(0x4cf)	//  different from the document, why

#define reg_pll_rx_coarse_tune	REG_ADDR16(0x4d0)
#define reg_pll_rx_coarse_div	REG_ADDR8(0x4d2)
#define reg_pll_rx_fine_tune	REG_ADDR16(0x4d4)
#define reg_pll_rx_fine_div		REG_ADDR8(0x4d6)
#define reg_pll_tx_coarse_tune	REG_ADDR16(0x4d8)
#define reg_pll_tx_coarse_div	REG_ADDR8(0x4da)
#define reg_pll_tx_fine_tune	REG_ADDR16(0x4dc)
#define reg_pll_tx_fine_div		REG_ADDR8(0x4de)

#define reg_pll_rx_frac			REG_ADDR32(0x4e0)
#define reg_pll_tx_frac			REG_ADDR32(0x4e4)

#define reg_pll_tx_ctrl			REG_ADDR8(0x4e8)
#define reg_pll_ctrl16			REG_ADDR16(0x4e8)
#define reg_pll_ctrl			REG_ADDR32(0x4e8)
enum{
	FLD_PLL_TX_CYC0 =			BIT(0),
	FLD_PLL_TX_SOF =			BIT(1),
	FLD_PLL_TX_CYC1 =			BIT(2),
	FLD_PLL_TX_PRE_EN =			BIT(3),
	FLD_PLL_TX_VCO_EN =			BIT(4),
	FLD_PLL_TX_PWDN_DIV =		BIT(5),
	FLD_PLL_TX_MOD_EN =			BIT(6),
	FLD_PLL_TX_MOD_TRAN_EN =	BIT(7),
	FLD_PLL_RX_CYC0 =			BIT(8),
	FLD_PLL_RX_SOF = 			BIT(9),
	FLD_PLL_RX_CYC1 =			BIT(10),
	FLD_PLL_RX_PRES_EN = 		BIT(11),
	FLD_PLL_RX_VCO_EN =			BIT(12),
	FLD_PLL_RX_PWDN_DIV =		BIT(13),
	FLD_PLL_RX_PEAK_EN =		BIT(14),
	FLD_PLL_RX_TP_CYC = 		BIT(15),
	FLD_PLL_SD_RSTB =			BIT(16),
	FLD_PLL_SD_INTG_EN =		BIT(17),
	FLD_PLL_CP_TRI = 			BIT(18),
	FLD_PLL_PWDN_INTG1 = 		BIT(19),
	FLD_PLL_PWDN_INTG2 =		BIT(20),
	FLD_PLL_PWDN_INTG_DIV =		BIT(21),
	FLD_PLL_PEAK_DET_EN =		BIT(22),
	FLD_PLL_OPEN_LOOP_EN =		BIT(23),
	FLD_PLL_RX_TICK_EN =		BIT(24),
	FLD_PLL_TX_TICK_EN =		BIT(25),
	FLD_PLL_RX_ALWAYS_ON =		BIT(26),
	FLD_PLL_TX_ALWAYS_ON =		BIT(27),
	FLD_PLL_MANUAL_MODE_EN =	BIT(28),
	FLD_PLL_CAL_DONE_EN =		BIT(29),
	FLD_PLL_LOCK_EN =			BIT(30),
};
#define reg_pll_rx_ctrl			REG_ADDR8(0x4e9)
enum{
	FLD_PLL_RX2_CYC0 =			BIT(0),
	FLD_PLL_RX2_SOF = 			BIT(1),
	FLD_PLL_RX2_CYC1 =			BIT(2),
	FLD_PLL_RX2_PRES_EN = 		BIT(3),
	FLD_PLL_RX2_VCO_EN =		BIT(4),
	FLD_PLL_RX2_PD_DIV =		BIT(5),
	FLD_PLL_RX2_PEAK_EN =		BIT(6),
	FLD_PLL_RX2_TP_CYC = 		BIT(7),
};

#define reg_pll_ctrl_a			REG_ADDR8(0x4eb)
enum{
	FLD_PLL_A_RX_TICK_EN =		BIT(0),
	FLD_PLL_A_TX_TICK_EN =		BIT(1),
	FLD_PLL_A_RX_ALWAYS_ON =	BIT(2),
	FLD_PLL_A_TX_ALWAYS_ON =	BIT(3),
	FLD_PLL_A_MANUAL_MODE_EN =	BIT(4),
	FLD_PLL_A_CAL_DONE_EN =		BIT(5),
	FLD_PLL_A_LOCK_EN =			BIT(6),
};
// pll polarity
#define reg_pll_pol_ctrl		REG_ADDR16(0x4ec)
enum{
	FLD_PLL_POL_TX_PRE_EN =		BIT(0),
	FLD_PLL_POL_TX_VCO_EN =		BIT(1),
	FLD_PLL_POL_TX_PD_DIV =		BIT(2),
	FLD_PLL_POL_MOD_EN =		BIT(3),
	FLD_PLL_POL_MOD_TRAN_EN =	BIT(4),
	FLD_PLL_POL_RX_PRE_EN =		BIT(5),
	FLD_PLL_POL_RX_VCO_EN =		BIT(6),
	FLD_PLL_POL_RX_PD_DIV =		BIT(7),
	FLD_PLL_POL_SD_RSTB =		BIT(8),
	FLD_PLL_POL_SD_INTG_EN =	BIT(9),
	FLD_PLL_POL_CP_TRI =		BIT(10),
	FLD_PLL_POL_TX_SOF =		BIT(11),
	FLD_PLL_POL_RX_SOF =		BIT(12),
};

#define reg_rf_rx_cap			REG_ADDR8(0x4f0)		//  电容
#define reg_rf_tx_cap			REG_ADDR8(0x4f1)		//  电容

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
 aes regs struct: begin  addr : 0x540
 *****************************************************/

#define reg_aes_ctrl            REG_ADDR8(0x540)
#define reg_aes_data            REG_ADDR32(0x548)

#define reg_aes_key(key_id)     reg_aes_key##key_id 

#define reg_aes_key0            REG_ADDR8(0x550)
#define reg_aes_key1            REG_ADDR8(0x551)
#define reg_aes_key2            REG_ADDR8(0x552)
#define reg_aes_key3            REG_ADDR8(0x553)
#define reg_aes_key4            REG_ADDR8(0x554)
#define reg_aes_key5            REG_ADDR8(0x555)
#define reg_aes_key6            REG_ADDR8(0x556)
#define reg_aes_key7            REG_ADDR8(0x557)
#define reg_aes_key8            REG_ADDR8(0x558)
#define reg_aes_key9            REG_ADDR8(0x559)
#define reg_aes_key10            REG_ADDR8(0x55a)
#define reg_aes_key11            REG_ADDR8(0x55b)
#define reg_aes_key12            REG_ADDR8(0x55c)
#define reg_aes_key13            REG_ADDR8(0x55d)
#define reg_aes_key14            REG_ADDR8(0x55e)
#define reg_aes_key15            REG_ADDR8(0x55f)





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
#define reg_gpio_f_datai		REG_ADDR32(0x580)
#define reg_gpio_f_datao		REG_ADDR32(0x584)
#define reg_gpio_f_oe			REG_ADDR32(0x588)
#define reg_gpio_f_nrm			REG_ADDR32(0x58c)
enum{
	FLD_MSDO_FUNC = 			BIT(0),
	FLD_I2C_FUNC = 				BIT(1),
	FLD_PWM0_GPIO_FUNC =		BIT(2),
	FLD_PWM1_GPIO_FUNC =		BIT(3),
	FLD_SWS_GPIO_FUNC =			BIT(4),
	FLD_SWM_GPIO_FUNC = 		BIT(5),
	FLD_UART_FUNC =				BIT(6),
	FLD_CN_GPIO_FUNC = 			BIT(7),
	FLD_CK_GPIO_FUNC = 			BIT(8),
	FLD_DO_GPIO_FUNC = 			BIT(9),
	FLD_DI_GPIO_FUNC =			BIT(10),
	FLD_MSC_GPIO_FUNC =			BIT(11),
	FLD_MIO_GPIO_FUNC =			BIT(12),
	FLD_MV_GPIO_FUNC = 			BIT(13),
	FLD_ME_GPIO_FUNC = 			BIT(14),
	FLD_R0_GPIO_FUNC =			BIT(15),
	FLD_TE_GPIO_FUNC =			BIT(16),
	FLD_TE_DMIC_FUNC =			BIT(17),
	FLD_R0_SDM_FUNC =			BIT(18),
	FLD_I2S_FUNC =				BIT(19),
	FLD_DP_GPIO_FUNC =			BIT(20),
};
#define reg_gpio_f_ie			REG_ADDR32(0x590)
#define reg_gpio_f_pol			REG_ADDR32(0x594)
#define reg_gpio_f_ds			REG_ADDR32(0x598)
#define reg_gpio_f_wakeup_en	REG_ADDR32(0x59c)
#define reg_gpio_f_2risc0		REG_ADDR32(0x5a0)
#define reg_gpio_f_2risc1		REG_ADDR32(0x5a4)
#define reg_gpio_f_2risc2		REG_ADDR32(0x5a8)
#define reg_gpio_g_datao		REG_ADDR32(0x5ac)
#define reg_gpio_g_oe			REG_ADDR32(0x5b0)
#define reg_gpio_g_ie			REG_ADDR32(0x5b4)
#define reg_gpio_g_ds			REG_ADDR32(0x5b8)
#define reg_gpio_g_wakeup_en	REG_ADDR32(0x5bc)
#define reg_gpio_wakeup_en		REG_ADDR8(0x5bf)
enum{
	FLD_GPIO_WAKEUP_SRC24_26 =	BIT_RNG(0,2),
	FLD_GPIO_WAKEUP_EN =		BIT(3),
	FLD_GPIO_IRQ_EN =			BIT(4),
};

#define reg_gpio_g_2risc0		REG_ADDR32(0x5c0)
#define reg_gpio_g_2risc1		REG_ADDR32(0x5c4)
#define reg_gpio_g_2risc2		REG_ADDR32(0x5c8)
#define reg_gpio_g_pol			REG_ADDR32(0x5cc)
#define reg_gpio_g_datai		REG_ADDR32(0x5d0)

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
 sbc regs struct: begin  0x700
 *****************************************************/
#define reg_sbc_enc_buf_addr	REG_ADDR16(0x700)
#define reg_sbc_dec_buf_addr	REG_ADDR16(0x702)
#define reg_sbc_buf_addr		REG_ADDR32(0x700)
enum{
	FLD_SBC_ENC_BUF_ADDR =		BIT_RNG(0,15),
	FLD_SBC_DEC_BUF_ADDR =		BIT_RNG(16,31),
};

#define reg_sbc_codec_en		REG_ADDR8(0x704)
#define reg_sbc_ctrl			REG_ADDR32(0x704)
enum{
	FLD_SBC_ENC_EN =			BIT(0),
	FLD_SBC_DEC_EN =			BIT(1),
	FLD_SBC_FST_BLK_EN =		BIT(2),
	FLD_SBC_ENC_DCT_STP_EN =	BIT(3),
	FLD_SBC_DEC_DCT_STP_EN =	BIT(4),
	FLD_SBC_UPACKT_EN =			BIT(5),
	FLD_SBC_BITPOOL = 			BIT_RNG(8,15),
	FLD_SBC_NRO_BUB =			BIT(16),
	FLD_SBC_ALLOC_MODE =		BIT(17),
	FLD_SBC_CHN_MODE =			BIT_RNG(18,19),
	FLD_SBC_BLK_MODE =			BIT_RNG(20,21),
	FLD_SBC_FREQ_MODE = 		BIT_RNG(22,23),
};
#define reg_sbc_irq				REG_ADDR8(0x707)
enum{
	FLD_SBC_IRQ_ENC =			BIT(0),
	FLD_SBC_IRQ_DEC =			BIT(1),
	FLD_SBC_IRQ_FST_BLK_STOP =	BIT(2),
	FLD_SBC_IRQ_DCT_STOP =		BIT(3),
	FLD_SBC_IRQ_DEC_DCT_STOP =	BIT(4),
};

#define reg_sbc_gain_band0123	REG_ADDR32(0x708)
#define reg_sbc_gain_band4567	REG_ADDR32(0x70c)
#define reg_sbc_gain(i)			REG_ADDR8(0x708+(i))
enum{
	FLD_GAIN_ADD_QUART =		BIT(0),
	FLD_GAIN_ADD_HALF =			BIT(1),
	FLD_GAIN_SHFT_BITS = 		BIT_RNG(2,5),
	FLD_GAIN_SHFT_DIR =			BIT(6),
	FLD_GAIN_ENC_DEC = 			BIT(7),
};

#define reg_sbc_ram_addr		REG_ADDR8(0x710)

#define reg_fifo0_data			REG_ADDR32(0x800)
#define reg_fifo1_data			REG_ADDR32(0x900)
#define reg_fifo2_data			REG_ADDR32(0xa00)

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

#define reg_dfifo0_addr            REG_ADDR16(0xb00)
#define reg_dfifo0_size            REG_ADDR16(0xb02)
#define reg_dfifo1_addr            REG_ADDR16(0xb04)
#define reg_dfifo1_size            REG_ADDR16(0xb06)
#define reg_dfifo2_addr            REG_ADDR16(0xb08)
#define reg_dfifo2_size            REG_ADDR16(0xb0a)


#define reg_dfifo_buf_thres        REG_ADDR32(0xb0c)
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

#define reg_dfifo_ana_in        REG_ADDR8(0xb11)
enum{
    FLD_DFIFO_MIC0_RISING_EDGE = BIT(0),
    FLD_DFIFO_MIC1_RISING_EDGE = BIT(1),
    FLD_DFIFO_AUD_INPUT_SEL =    BIT_RNG(2,3),
    FLD_DFIFO_AUD_INPUT_MONO =    BIT(4),
    FLD_DFIFO_AUD_INPUT_BYPASS = BIT(5),
};
enum{
    REG_AUD_INPUT_SEL_USB = 0,
    REG_AUD_INPUT_SEL_I2S = 1,
    REG_AUD_INPUT_SEL_ADC = 2,
    REG_AUD_INPUT_SEL_DMIC = 3,
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

#define reg_dfifo0_rd_ptr        REG_ADDR16(0xb14)
#define reg_dfifo0_wr_ptr        REG_ADDR16(0xb16)
#define reg_dfifo1_rd_ptr        REG_ADDR16(0xb18)
#define reg_dfifo1_wr_ptr        REG_ADDR16(0xb1a)
#define reg_dfifo2_rd_ptr        REG_ADDR16(0xb1c)
#define reg_dfifo2_wr_ptr        REG_ADDR16(0xb1e)

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

