
#include "../tl_common.h"

#if (MCU_CORE_TYPE != MCU_CORE_3520)

void audhw_set_pre_gain(int gain_left, int gain_right){
	u8 v = MASK_VAL(FLDA_AUD_PRE_GAIN_LEFT, gain_left, FLDA_AUD_PRE_GAIN_RIGHT, gain_right);
	analog_write(rega_aud_ctrl, v);
}

void audhw_set_post_gain(int gain_left, int gain_right){
	u8 v = MASK_VAL(FLDA_AUD_PST_GAIN_LEFT, gain_left, FLDA_AUD_PST_GAIN_RIGHT, gain_right);
	analog_write(rega_aud_ctrl2, v);
}

#endif
