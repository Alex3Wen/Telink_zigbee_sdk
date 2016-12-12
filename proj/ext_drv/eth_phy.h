
#pragma once

STATIC_ASSERT(_USER_CONFIG_DEFINED_);

#define	ETH_PHY_TYPE_DM916 	 	1
#define ETH_PHY_CHIP_TYPE		ETH_PHY_TYPE_DM916

#if(ETH_PHY_CHIP_TYPE == ETH_PHY_TYPE_DM916)
	#define ETH_SPEED_100M		0
#else	
	#define ETH_SPEED_100M		1
#endif

#define reg_eth_phy_bcr		0					// basic control register
enum{
	FLD_ETH_PHY_BSR_RESERVE = BIT_RNG(0, 7),
	FLD_ETH_PHY_BSR_FULL_DUPLEX = BIT(8),
	FLD_ETH_PHY_BSR_RESTART_NEGOT = BIT(9),
	FLD_ETH_PHY_BSR_ISOLATE = BIT(10),
	FLD_ETH_PHY_BSR_POWER_DOWN = BIT(11),
	FLD_ETH_PHY_BSR_NEGOT_EN = BIT(12),
	FLD_ETH_PHY_BSR_SPEED_100M = BIT(13),		//  1: 100M,  0: 10M
	FLD_ETH_PHY_BSR_LOOPBACK = BIT(14),
	FLD_ETH_PHY_BSR_SOFT_RST = BIT(15),
};

#if(ETH_PHY_CHIP_TYPE == ETH_PHY_TYPE_DM916)
#define reg_eth_phy_dscr		16				// devicom control register,  !!! for dm916a only
enum{
	FLD_ETH_PHY_DSCR_ROUT = BIT(0),
	FLD_ETH_PHY_DSCR_SLEEP = BIT(1),
	FLD_ETH_PHY_DSCR_MFPSC = BIT(2),			// preamble supression enable
	FLD_ETH_PHY_DSCR_SMRST = BIT(3),
	FLD_ETH_PHY_DSCR_RPD_CTR_EN = BIT(4),		// reduced power down control enable
	FLD_ETH_PHY_DSCR_COLLED = BIT(5),
	FLD_ETH_PHY_DSCR_SPLED = BIT(6),
	FLD_ETH_PHY_DSCR_FLINK_100 = BIT(7),

	FLD_ETH_PHY_DSCR_RMII_EN = BIT(8),			// reduced mii enable
	FLD_ETH_PHY_DSCR_RESERVE = BIT(9),
	FLD_ETH_PHY_DSCR_100_TX = BIT(10),			// 100-base-T tx mode control
	FLD_ETH_PHY_DSCR_REPEATER = BIT(11),
	FLD_ETH_PHY_DSCR_BP_ADPOK = BIT(12),
	FLD_ETH_PHY_DSCR_BP_ALIGN = BIT(13),
	FLD_ETH_PHY_DSCR_BP_SCR = BIT(14),
	FLD_ETH_PHY_DSCR_BP_4B5B = BIT(15),

};

#define reg_eth_phy_spe_conf	20				// devicom specified config register,  !!! for dm916a only
enum{
	FLD_ETH_PHY_SPE_CONF_PWDN_CTL = BIT(0),
	FLD_ETH_PHY_SPE_CONF_RMII_VER = BIT(1),		// support rmii verion,  1: 1.0,  	0: 1.2
};
#endif

