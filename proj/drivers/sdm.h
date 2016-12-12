
#pragma once

void sdm_dithering_proc(int cur_vol);
void sdm_enable(int en);

static inline void sdm_mute(int en){
    if(en){
        reg_dfifo_manu_aud_scl = 1;
    }else{
        reg_dfifo_manu_aud_scl = 0;
    }
}


