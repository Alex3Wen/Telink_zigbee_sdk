
#include "../config/user_config.h"
#include "eth_phy.h"
#include "../drivers/eth_hw.h"
#include "../mcu/gpio.h"

static inline u8 eth_phy_get_addr(void){
	return 0;
}
static inline void eth_phy_reset(void){
	assert(gpio_is_output_en(ETH_PHY_RST_GPIO));
	gpio_write(ETH_PHY_RST_GPIO, 1);
	gpio_write(ETH_PHY_RST_GPIO, 0);
	gpio_write(ETH_PHY_RST_GPIO, 1);
}

static inline void eth_phy_init(void){
	eth_phy_reset();
#if(ETH_PHY_CHIP_TYPE == ETH_PHY_TYPE_DM916)
	eth_hw_write_phy_reg(reg_eth_phy_bcr, (ETH_SPEED_100M ? FLD_ETH_PHY_BSR_SPEED_100M : 0) | FLD_ETH_PHY_BSR_FULL_DUPLEX);
	eth_hw_write_phy_reg(reg_eth_phy_dscr, FLD_ETH_PHY_DSCR_MFPSC | FLD_ETH_PHY_DSCR_RPD_CTR_EN | FLD_ETH_PHY_DSCR_RMII_EN
		| (ETH_SPEED_100M ? FLD_ETH_PHY_DSCR_100_TX : 0));
	eth_hw_write_phy_reg(reg_eth_phy_spe_conf, FLD_ETH_PHY_SPE_CONF_RMII_VER);	// rmii version == 1.0
#endif
}

