
#pragma once

#include "../tl_common.h"

static inline void pwm_reg_set(u32 id, u32 max_cnt, u32 cmp_cnt, u32 clk_sel){
    if(0 == id){
        reg_pwm0_setting1 = MASK_VAL(FLD_PWM_MAX, max_cnt, FLD_PWM_CMP, cmp_cnt);
        reg_pwm0_setting2 = MASK_VAL(FLD_PWM_WAVEFORM_MODE, 3, FLD_PWM_OUT_MODE, 2, FLD_PWM_CLK_SEL, clk_sel);
    }else if(1 == id){
        reg_pwm1_setting1 = MASK_VAL(FLD_PWM_MAX, max_cnt, FLD_PWM_CMP, cmp_cnt);
        reg_pwm1_setting2 = MASK_VAL(FLD_PWM_WAVEFORM_MODE, 3, FLD_PWM_OUT_MODE, 2, FLD_PWM_CLK_SEL, clk_sel);
    }
#if(MCU_CORE_TYPE == MCU_CORE_5328)
    else if(2 == id){
        reg_pwm2_setting1 = MASK_VAL(FLD_PWM_MAX, max_cnt, FLD_PWM_CMP, cmp_cnt);
        reg_pwm2_setting2 = MASK_VAL(FLD_PWM_WAVEFORM_MODE, 3, FLD_PWM_OUT_MODE, 2, FLD_PWM_CLK_SEL, clk_sel);
    }
#endif

}

static inline void pwm_set_by_tick(u32 id, u32 cycle, u32 cycle_high, int offset){
    if(cycle < cycle_high){
        // cannot set this frequency
    }
    else if(cycle < 255){
        if(0 == id){
            pwm_reg_set(0, cycle + offset, cycle_high, 1);
        }else{
            pwm_reg_set(1, cycle + offset, cycle_high, 1);
        }
    }
    else if(cycle < (255 * 8)){
        if(0 == id){
            pwm_reg_set(0, cycle / 8 + offset, cycle_high / 8, 2);
        }else{
            pwm_reg_set(1, cycle / 8 + offset, cycle_high / 8, 2);
        }
    }
    else if(cycle < (255 * 16)){
        if(0 == id){
            pwm_reg_set(0, cycle / 16 + offset, cycle_high / 16, 3);
        }else{
            pwm_reg_set(1, cycle / 16 + offset, cycle_high / 16, 3);
        }
    }
    else if(cycle < (255 * 32)){
        if(0 == id){
            pwm_reg_set(0, cycle / 32 + offset, cycle_high / 32, 4);
        }else{
            pwm_reg_set(1, cycle / 32 + offset, cycle_high / 32, 4);
        }
    }
    else if(cycle < (255 * 64)){
        if(0 == id){
            pwm_reg_set(0, cycle / 64 + offset, cycle_high / 64, 5);
        }else{
            pwm_reg_set(1, cycle / 64 + offset, cycle_high / 64, 5);
        }
    }
    else if(cycle < (255 * 128)){
        if(0 == id){
            pwm_reg_set(0, cycle / 128 + offset, cycle_high / 128, 6);
        }else{
            pwm_reg_set(1, cycle / 128 + offset, cycle_high / 128, 6);
        }
    }
    else if(cycle < (255 * 256)){
        if(0 == id){
            pwm_reg_set(0, cycle / 256 + offset, cycle_high / 256, 7);
        }else{
            pwm_reg_set(1, cycle / 256 + offset, cycle_high / 256, 7);
        }
    }else{
        // cannot set this frequency
    }
}

static inline void pwm_set(u32 id, u32 freq, int offset, u32 duty){
    u32 cycle = (CLOCK_SYS_CLOCK_HZ / freq);
    pwm_set_by_tick(id, cycle, cycle / duty, offset);
}


static inline void pwm_start(u32 id){
    if(0 == id){
    	reg_rst0_16 = FLD_RST_PWM0;
        BM_SET(reg_pwm0_en, FLD_PWM_EN);
    }else if(1 == id){
        reg_rst0_16 = FLD_RST_PWM1;
        BM_SET(reg_pwm1_en, FLD_PWM_EN);
    }
#if(MCU_CORE_TYPE == MCU_CORE_5328)
    else if(2 == id){
        BM_SET(reg_pwm2_en, FLD_PWM_EN);
    }
    reg_pwm_en = FLD_PWM0_EN | FLD_PWM1_EN | FLD_PWM2_EN;
#endif    
}

static inline void pwm_stop(u32 id){
    if(0 == id){
        gpio_set_output_en(GPIO_PWM0, 1);
        gpio_write(GPIO_PWM0, 0);
        BM_CLR(reg_pwm0_en, FLD_PWM_EN);
        gpio_set_output_en(GPIO_PWM0, 0);
    }else if(1 == id){
        gpio_set_output_en(GPIO_PWM1, 1);
        gpio_write(GPIO_PWM1, 0);
        BM_CLR(reg_pwm1_en, FLD_PWM_EN);
        gpio_set_output_en(GPIO_PWM1, 0);
    }
#if(MCU_CORE_TYPE == MCU_CORE_5328)
    else if(2 == id){
        gpio_set_output_en(GPIO_PWM2, 1);
        gpio_write(GPIO_PWM2, 0);
        BM_CLR(reg_pwm2_en, FLD_PWM_EN);
        gpio_set_output_en(GPIO_PWM2, 0);
    }
#endif    
    
}

static inline void pwm_int(u32 id){}

//////////////////////////////////////////////////////////////////////////////////////
//  SPWM
//

