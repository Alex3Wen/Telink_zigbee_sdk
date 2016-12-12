
#include "../tl_common.h"
#include "../mcu/audhw.h"

void aud_init(void){
#if (!MODULE_DMIC_ENABLE)
	audhw_set_pre_gain(1,1);
	audhw_set_post_gain(0,0);
#endif

	reg_aud_ctrl = FLD_AUD_ISO_EN | FLD_AUD_MODE_SEL;
	#if(MIC_SAMPLE_RATE == 16000)		//	0x60 ÊÇÎ¢µ÷
		//  15.625K --> 16K,  0x7d10 == ( 0x8000 * (2000*1000 / 128 ) / 16000 ),  see reg_dfifo_scale
		reg_ascl_tune = 0x7d100060;	// PLL clock as DMIC clock source
		//reg_ascl_tune = 0x7e0000f0;		// 32M RC clock for DMIC clock source
	#else
		reg_ascl_tune = 0x29b00020;		//  15.625K --> 48K
	#endif

	//reg_ascl_tune = 0x80000020;		//  keep same as received from devices

}

