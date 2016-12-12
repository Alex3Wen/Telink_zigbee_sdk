
#include "../tl_common.h"
#include "ir.h"

// infrared protocols 
static void ir_stop_carrier(void){
#if(IR_USE_PWM)
    pwm_stop(IR_PWM_ID);
#else
    gpio_write(GPIO_IR, 1);
#endif
}

static void ir_out_carrier(u32 t_us){
#if(IR_USE_PWM)
    pwm_start(IR_PWM_ID);
#else
    gpio_write(GPIO_IR, 0);
#endif
    sleep_us(t_us);
    ir_stop_carrier();
}

static void ir_send_bit(int bit){
    if(bit){
        ir_out_carrier(IR_HIGH_CARR_TIME);
        sleep_us(IR_HIGH_NO_CARR_TIME);
    }else{
        ir_out_carrier(IR_LOW_CARR_TIME);
        sleep_us(IR_LOW_NO_CARR_TIME);
    }
}

static void ir_send_byte(u8 data){
    int mask = 0x01;
    foreach(i, 8){        //  send  LSB first
        ir_send_bit(mask & data);
        mask = mask << 1;
    }
}

static void ir_send_data(u8 dat){
    ir_send_byte(dat);
    ir_send_byte(~dat);
}

static void ir_send_intro(void){
    ir_out_carrier(IR_INTRO_CARR_TIME);
    sleep_us(IR_INTRO_NO_CARR_TIME);
}

static void ir_send_repeat(void){
    ir_out_carrier(IR_INTRO_CARR_TIME);
    sleep_us(IR_REPEAT_NO_CARR_TIME);
}

static void ir_end_transmit(void){
    ir_out_carrier(IR_END_TRANS_TIME);
}


void ir_send_switch(u8 addr, u8 cmd){
    ir_send_intro();
    ir_send_byte(addr);
    ir_send_byte(cmd);
    ir_send_data(IR_SWITCH_CODE);
    ir_end_transmit();
    sleep_us(IR_REPEAT_INTERVAL_TIME);
    ir_send_repeat();
}

////////////////////////////////////////////////////////////////////////

#define IR_LEARN_CARR_GLITCH_MIN    (3*CLOCK_SYS_CLOCK_1US)
#define IR_LEARN_CARR_MIN            (7 * CLOCK_SYS_CLOCK_1US)
#define IR_LEARN_CARR_MAX            (20 * CLOCK_SYS_CLOCK_1US)
#define IR_LEARN_NONE_CARR_MIN        (80 * CLOCK_SYS_CLOCK_1US)
#define IR_LEARN_INTRO_MIN            (2200 * CLOCK_SYS_CLOCK_1US)        //  JVC is 2400us
#define IR_LEARN_MAX_TIME            (200000 * CLOCK_SYS_CLOCK_1US)

#define IR_LEARN_REPEAT_SPACE        (15000 * CLOCK_SYS_CLOCK_1US)        // nokia, < 20ms
#define IR_LEARN_REPEAT_INTRO        (8000 * CLOCK_SYS_CLOCK_1US)
#define IR_MITSUBISH_MIN     (3000 * CLOCK_SYS_CLOCK_1US)
#define IR_MITSUBISH_MAX    (6000 * CLOCK_SYS_CLOCK_1US)
#define IR_LEARN_SERIES_CNT            80
#define IR_SONY_INTRO_MAXTM    (3000 * CLOCK_SYS_CLOCK_1US)
#define IR_SONY_BIT_MAXTM    (800 * CLOCK_SYS_CLOCK_1US)
#define IR_THOMSON_STARTTM    (7000 * CLOCK_SYS_CLOCK_1US)
#define IR_THOMSON_MIN    (6500 * CLOCK_SYS_CLOCK_1US)
#define IR_THOMSON_MAX    (8500 * CLOCK_SYS_CLOCK_1US)

typedef struct{
    int is_carr;
    int carr_found;
    u32 carr_check_cnt;        //  check carrier freq     
    u32 carr_switch_start_tm;

    u32 series_cnt;
    int series_tm[IR_LEARN_SERIES_CNT];//must be int type.

    u32 time_interval;
    u32 last_trigger_tm;
    u32 curr_trigger_tm;
    u32 learn_timer_started;
    int ir_int_cnt;

}ir_learn_ctrl_t;

enum{
    IR_NEC_FORMAT = 0,
    IR_TOSHIBA_FORMAT = 0,//NEC and TOSHIBA is very similare, so use same value.
    IR_MITSUBISH_FORMAT = 2,
    IR_SONY_FORMAT = 3,
    IR_PHILIPS_FORMAT = 4,
    IR_THOMSON_FORMAT = 5,
};
typedef struct{
    u32 learn_protocol;
    u32 carr_high_tm;
    u32 carr_low_tm;
    u32 intro_carr_tm;
    u32 intro_none_carr_tm;
    
    u32 digit0_carr_tm;
    u32 digit0_none_carr_tm;
    u32 digit1_carr_tm;
    u32 digit1_none_carr_tm;
    u32 end_carr_tm;
    u32 data_interval;//used by IR_MITSUBISH_FORMAT
}ir_learn_pattern_t;


#define IR_LEARN_KEY_COUNT_MAX    50
// STATIC_ASSERT_INT_DIV((IR_LEARN_KEY_COUNT_MAX+1), 4);
typedef struct{
    u8 key_count;
    u8 bits_cnt;
    u8 resv[2];
    u32 code[IR_LEARN_KEY_COUNT_MAX];
}ir_learn_code_t;

ir_learn_ctrl_t ir_learn_ctrl;
ir_learn_pattern_t ir_learn_pattern;
ir_learn_code_t       ir_learn_code;

#define IR_ITT_PULSE_MIN        (10 * CLOCK_SYS_CLOCK_1US)

#define IR_NEC_INTRO_TIME_MIN    (4000*CLOCK_SYS_CLOCK_1US)    // some chip: intro == 4500us
#define IR_NEC_CARR_TIME_MAX    (1800*CLOCK_SYS_CLOCK_1US)

#define IR_RC5_CARR_TIME_MIN    (800*CLOCK_SYS_CLOCK_1US)
#define IR_RC5_CARR_TIME_MAX    (1000*CLOCK_SYS_CLOCK_1US)

void ir_learn_init(void){
    memset4(&ir_learn_ctrl, 0, sizeof(ir_learn_ctrl));
}

void ir_learn_pwm(int with_carr, int start){
    int is_carr = 1;
    int cmd_received = 0;
    ir_learn_code.code[ir_learn_code.key_count] = 0;
    int last_duration = 0;
    for(int i = start; i < ir_learn_ctrl.series_cnt; ++i){
        int duration = ir_learn_ctrl.series_tm[i];
        if(is_carr){
            // do not learn repeat code
            if(cmd_received && duration > IR_LEARN_REPEAT_INTRO){
                break;
            }
            if(0 == ir_learn_pattern.intro_carr_tm && duration > IR_LEARN_INTRO_MIN){
                ir_learn_pattern.intro_carr_tm = duration;
            }
            if((duration < IR_LEARN_INTRO_MIN)||
                (ir_learn_pattern.learn_protocol == IR_THOMSON_FORMAT)){
                last_duration = duration;
                #ifdef WIN32
                printf("THOMSON FORMAT");
                #endif
            }
        }else{
            // do not learn repeat code
            if(cmd_received && duration > IR_LEARN_REPEAT_SPACE){
                ir_learn_pattern.end_carr_tm = last_duration;
                break;
            }
            if(ir_learn_pattern.learn_protocol == IR_THOMSON_FORMAT){
                cmd_received = 1;
                if(((duration-last_duration) > IR_THOMSON_MIN )&&
                    ((duration-last_duration) < IR_THOMSON_MAX ))
                {
                    //bit 1
                    ir_learn_code.code[ir_learn_code.key_count] |= (1 << ir_learn_code.bits_cnt);

                    ir_learn_pattern.digit1_carr_tm = last_duration;
                    ir_learn_pattern.digit1_none_carr_tm = duration;
                }else{
                    //bit 0
                    ir_learn_pattern.digit0_carr_tm = last_duration;
                    ir_learn_pattern.digit0_none_carr_tm = duration;
                }
                ++ir_learn_code.bits_cnt;
                is_carr = !is_carr;
                continue;
            }
            if(cmd_received && duration > IR_MITSUBISH_MIN && 
                duration < IR_MITSUBISH_MAX){               
                ir_learn_pattern.learn_protocol = IR_MITSUBISH_FORMAT;
                ir_learn_pattern.data_interval = duration;
                ir_learn_pattern.end_carr_tm = last_duration;
                // ignore 4.22ms interval, continue to learn next bit.
                #ifdef WIN32
                printf("\n..........MITSUBISH FORMAT......\n");
                printf("\n..........enter into interval......\n");
                #endif
                is_carr = !is_carr;
                continue;
            }
            
            if(0 == ir_learn_pattern.intro_none_carr_tm && duration > IR_LEARN_INTRO_MIN){
                ir_learn_pattern.intro_none_carr_tm = duration;
            }
            if(0 == ir_learn_pattern.intro_none_carr_tm && 
                (ir_learn_pattern.intro_carr_tm < IR_SONY_INTRO_MAXTM )&&
                duration < IR_SONY_BIT_MAXTM){//SONY FORMAT
                #ifdef WIN32
                printf("\n..........SONY FORMAT......\n");
                printf("\n.......write down intro none carrtime......\n");
                #endif
                ir_learn_pattern.learn_protocol = IR_SONY_FORMAT;
                ir_learn_pattern.intro_none_carr_tm = duration;
                is_carr = !is_carr;
                continue;
            }
            
            if(duration < IR_LEARN_INTRO_MIN){
                cmd_received = 1;
                if(((duration > last_duration)&&((duration << 1) > (last_duration * 3)))||
                    ((last_duration > duration)&&((last_duration << 1) > (duration * 3)))){
                    //bit 1
                    ir_learn_code.code[ir_learn_code.key_count] |= (1 << ir_learn_code.bits_cnt);

                    ir_learn_pattern.digit1_carr_tm = last_duration;
                    ir_learn_pattern.digit1_none_carr_tm = duration;
                }else{
                    //bit 0
                    ir_learn_pattern.digit0_carr_tm = last_duration;
                    ir_learn_pattern.digit0_none_carr_tm = duration;
                }
                ++ir_learn_code.bits_cnt;
            }            
        }
        is_carr = !is_carr;
    }
}
         
void ir_learn_ppm(void){
    //printf("\nenter into ppm\n");
    // philips
    if(ir_learn_ctrl.series_tm[0] > 850 * CLOCK_SYS_CLOCK_1US 
        && ir_learn_ctrl.series_tm[0] < 950 * CLOCK_SYS_CLOCK_1US
        && ir_learn_ctrl.series_tm[1] > 850 * CLOCK_SYS_CLOCK_1US 
        && ir_learn_ctrl.series_tm[1] < 950 * CLOCK_SYS_CLOCK_1US){
        ir_learn_pattern.learn_protocol = IR_PHILIPS_FORMAT;
        #ifdef WIN32
        printf("PHILIPS FORMAT");
        #endif
        ir_learn_code.code[ir_learn_code.key_count] |= (1 << ir_learn_code.bits_cnt);    // bit0 == 1
        ++ir_learn_code.bits_cnt;

        int i;
        for(i = 1; i < ir_learn_ctrl.series_cnt; ++i){
            if((i & 1)){
                ir_learn_code.code[ir_learn_code.key_count] |= (1 << ir_learn_code.bits_cnt);    // bit0 == 1
            }
            ++ir_learn_code.bits_cnt;

            if(ir_learn_ctrl.series_tm[i + 1] > (1350 * CLOCK_SYS_CLOCK_1US)){
                ir_learn_ctrl.series_tm[i + 1] = 895 * CLOCK_SYS_CLOCK_1US;
            }else{
                ++i;
            }            
        }        
    }
}

int ir_check_intro(void){
    for(int i = 0; i < 6; i+=2){    // check only the carrier / high
        if(ir_learn_ctrl.series_tm[i] > IR_LEARN_INTRO_MIN){
            return i;
        }
        if((ir_learn_ctrl.series_tm[i+1]-ir_learn_ctrl.series_tm[i])> IR_THOMSON_STARTTM){
            ir_learn_pattern.learn_protocol = IR_THOMSON_FORMAT;
            return i;
        }
    }    
    return -1;
}
void ir_learn(void){
    if(0 == ir_learn_ctrl.series_cnt)
        return;
    //in order to know the last carrier time.
    ++ir_learn_ctrl.series_cnt;

    //TODO("Filter all that < 100us ");
    // !!! not cover sharp JVC, protocol yet
    int i;
    if((i = ir_check_intro()) >= 0){
        ir_learn_pwm(1, i);
    }else if(ir_learn_ctrl.series_tm[0] < IR_ITT_PULSE_MIN){
        ir_learn_pwm(0, 0);    // ITT
    }
    else{
        ir_learn_ppm();
    }
    ++ir_learn_code.key_count;
    #ifdef WIN32
    printf("\nlearn code is %4x\n",ir_learn_code.code[0]);
    #endif
}

void ir_record(u32 tm, int pol)
{
    ++ir_learn_ctrl.ir_int_cnt;
    ir_learn_ctrl.curr_trigger_tm = tm;

    if(ir_learn_ctrl.ir_int_cnt > 1){
        
        ir_learn_ctrl.time_interval = ir_learn_ctrl.curr_trigger_tm - ir_learn_ctrl.last_trigger_tm;
        // record carrier time
        if((ir_learn_ctrl.time_interval < IR_LEARN_NONE_CARR_MIN) && ir_learn_ctrl.time_interval > IR_LEARN_CARR_GLITCH_MIN){   // removing glitch  // receiving carrier
            if(!ir_learn_ctrl.is_carr){
                if( ir_learn_ctrl.series_cnt > 0){  //  Do not record leading none-carrier
                    ir_learn_ctrl.series_tm[ir_learn_ctrl.series_cnt] = ir_learn_ctrl.curr_trigger_tm - ir_learn_ctrl.carr_switch_start_tm 
                        - (ir_learn_pattern.carr_low_tm + ir_learn_pattern.carr_high_tm);
                    ++ir_learn_ctrl.series_cnt;
                }                
                ir_learn_ctrl.carr_switch_start_tm = ir_learn_ctrl.curr_trigger_tm;
                ir_learn_ctrl.is_carr = 1;
            }
            else{
                ir_learn_ctrl.series_tm[ir_learn_ctrl.series_cnt] = ir_learn_ctrl.curr_trigger_tm - ir_learn_ctrl.carr_switch_start_tm;
               }
            
            //  to calulate duty-cycle of the carrier
            if(ir_learn_ctrl.carr_check_cnt < 10
                && ir_learn_ctrl.time_interval < IR_LEARN_CARR_MAX && ir_learn_ctrl.time_interval > IR_LEARN_CARR_MIN){

                ++ir_learn_ctrl.carr_check_cnt;               
                // we are receiving carrier
                if(pol){
                    if(ir_learn_ctrl.time_interval < ir_learn_pattern.carr_low_tm || 0 == ir_learn_pattern.carr_low_tm)     //  record the shortest cycle
                        ir_learn_pattern.carr_low_tm = ir_learn_ctrl.time_interval;
                }else{
                    if(ir_learn_ctrl.time_interval < ir_learn_pattern.carr_high_tm || 0 == ir_learn_pattern.carr_high_tm)   //  record the shortest cycle
                        ir_learn_pattern.carr_high_tm = ir_learn_ctrl.time_interval;
                }
            }
        }else{
            // record carrier time
            if(ir_learn_ctrl.is_carr){
                // 实际计算时候少了一个周期
                ir_learn_ctrl.series_tm[ir_learn_ctrl.series_cnt] = (ir_learn_ctrl.last_trigger_tm - ir_learn_ctrl.carr_switch_start_tm)
                    + (ir_learn_pattern.carr_low_tm + ir_learn_pattern.carr_high_tm);
#ifndef WIN32
                if(0 == ir_learn_ctrl.learn_timer_started){
                    ir_learn_ctrl.learn_timer_started = 1;
                    // to stop learning after 200 ms
                    static ev_time_event_t record_end = {ir_record_end};
                    ev_on_timer(&record_end, (200*1000));
                }
#endif
                ++ir_learn_ctrl.series_cnt;

                ir_learn_ctrl.carr_switch_start_tm = ir_learn_ctrl.last_trigger_tm;
            }
            ir_learn_ctrl.is_carr = 0;
        }
    }
    ir_learn_ctrl.last_trigger_tm = ir_learn_ctrl.curr_trigger_tm;

}

int ir_record_end(void * data){
    gpio_clr_interrupt(GPIO_IR_LEARN_IN);
    ir_learn();
    return -1;
}

#ifdef WIN32
#define IR_WIN32_DEBUG printf
typedef struct{
    int is_carr;
    int duration;
}IR_TEST_CTRL;

#define IR_ONE_CYCLE_TICK  (26.316 * CLOCK_SYS_CLOCK_1US)
#define IR_CARR_HIGH_TICK  (8.772 * CLOCK_SYS_CLOCK_1US)

void ir_learn_test(void){
//IR simu data input 
#if 1
    //TOSHIBA protocol
    IR_TEST_CTRL ir_test_ctrl[] = 
            {{0, 200}, 
            {1, 4500}, {0, 4500},//INTRO CODE
            //ae69c356
            {1, 560}, {0, 560},//BIT 0 ; 0110
            {1, 560}, {0, 1690},
            {1, 560}, {0, 1690}, 
            {1, 560}, {0, 560},

            {1, 560}, {0, 1690},//BIT4 ; 1010
            {1, 560}, {0, 560},
            {1, 560}, {0, 1690}, 
            {1, 560}, {0, 560},

            {1, 560}, {0, 1690},//BIT8; 1100
            {1, 560}, {0, 1690},
            {1, 560}, {0, 560}, 
            {1, 560}, {0, 550},

            {1, 560}, {0, 560},//BIT12; 0011
            {1, 560}, {0, 560},
            {1, 560}, {0, 1690}, 
            {1, 560}, {0, 1690},

            {1, 560}, {0, 1690},//BIT16; 1001
            {1, 560}, {0, 560},
            {1, 560}, {0, 560}, 
            {1, 560}, {0, 1690},

            {1, 560}, {0, 570},//BIT20; 0110
            {1, 570}, {0, 1700},
            {1, 550}, {0, 1700}, 
            {1, 560}, {0, 550},

             {1, 560}, {0, 570},//BIT24; 0111
            {1, 570}, {0, 1700},
            {1, 550}, {0, 1700}, 
            {1, 560}, {0, 1690},

            {1, 560}, {0, 560},//BIT28; 0101
            {1, 560}, {0, 1690},
            {1, 560}, {0, 560}, 
            {1, 560}, {0, 1690},//BIT31

      
            {1, 1000} /*end*/, {0, 18000}, {1, 9000}/*repeat*/};
#endif
#if 0
            //NEC protocol
            IR_TEST_CTRL ir_test_ctrl[] = 
            {{0, 200}, 
            {1, 9000}, {0, 4500},//INTRO CODE
            //ae69 56c3            
            {1, 560}, {0, 1690},//BIT8; 1100
            {1, 560}, {0, 1690},
            {1, 560}, {0, 560}, 
            {1, 560}, {0, 550},

            {1, 560}, {0, 560},//BIT12; 0011
            {1, 560}, {0, 560},
            {1, 560}, {0, 1690}, 
            {1, 560}, {0, 1690},
                
            {1, 560}, {0, 560},//BIT 0 ; 0110
            {1, 560}, {0, 1690},
            {1, 560}, {0, 1690}, 
            {1, 560}, {0, 560},

            {1, 560}, {0, 1690},//BIT4 ; 1010
            {1, 560}, {0, 560},
            {1, 560}, {0, 1690}, 
            {1, 560}, {0, 560},

            {1, 560}, {0, 1690},//BIT16; 1001
            {1, 560}, {0, 560},
            {1, 560}, {0, 560}, 
            {1, 560}, {0, 1690},

            {1, 560}, {0, 570},//BIT20; 0110
            {1, 570}, {0, 1700},
            {1, 550}, {0, 1700}, 
            {1, 560}, {0, 550},

            {1, 560}, {0, 570},//BIT24; 0111
            {1, 570}, {0, 1700},
            {1, 550}, {0, 1700}, 
            {1, 560}, {0, 1690},

            {1, 560}, {0, 560},//BIT28; 0101
            {1, 560}, {0, 1690},
            {1, 560}, {0, 560}, 
            {1, 560}, {0, 1690},//BIT31

      
            {1, 560} /*end*/, {0, 18000}, {1, 9000}/*repeat*/};        
#endif
#if 0
             //MITSUBISH  protocol
            IR_TEST_CTRL ir_test_ctrl[] = 
            {{0, 200}, 
            {1, 8440}, {0, 4220},//INTRO CODE                        
            //customer code ;0xea6c
            {1, 530}, {0, 530},// 0011
            {1, 530}, {0, 530},
            {1, 530}, {0, 1580}, 
            {1, 530}, {0, 1580},
                
            {1, 530}, {0, 530},// 0110
            {1, 530}, {0, 1580},
            {1, 530}, {0, 1580}, 
            {1, 530}, {0, 530},

          
             
            //insert end and interval
            {1, 530}, {0, 4220},
            //data code 
            {1, 530}, {0, 530},//BIT28; 0101
            {1, 530}, {0, 1580},
            {1, 530}, {0, 530}, 
            {1, 530}, {0, 1580},//BIT31
            
            {1, 530}, {0, 530},//BIT24; 0111
            {1, 530}, {0, 1580},
            {1, 530}, {0, 1580}, 
            {1, 530}, {0, 1580},

            {1, 530},{0,16000},{1, 9000}};  
#endif
#if 0
            //SONY  protocol
            IR_TEST_CTRL ir_test_ctrl[] = 
            {{0, 200}, 
            {1, 2400}, //INTRO CODE                        
            //7 data bit, 0x16ea
            {0, 600}, 
                
            {1, 600}, {0, 600}, 
            {1, 1200},{0, 600},
            {1, 600}, {0, 600},
            {1, 1200},{0, 600}, 
                
            {1, 600}, {0, 600},
            {1, 1200},{0, 600},
            {1, 1200},{0, 600},                
            {1, 1200},{0, 600},
                
            {1, 600}, {0, 600},
            {1, 1200},{0, 600}, 
            {1, 1200},{0, 600},
            {1, 600}, {0, 600}, 
                
            {1, 1200},{0, 600},
            {1, 600},{0, 600}, 
                
            {1, 1200},
                        
            {0,15000},{1, 2400}};  
#endif
#if 0
            //PHILIPS protocol
            IR_TEST_CTRL ir_test_ctrl[] = 
            {{0, 200}, 
             //INTRO CODE                        
            //7 data bit,0x2103
            {1, 895},{0, 895},                 
            {1, 1790}, {0, 895}, 

            {1, 895},{0, 895},             
            {1, 895},{0, 895},             
            {1, 895},{0, 895},             
            {1, 895},{0, 895},             
            {1, 895},{0, 1790}, 

            {1, 1790},{0, 895},     
            {1, 895},{0, 895},     
            {1, 895},{0, 895},     
            {1, 895},{0, 1790},
            {1, 895}, {0,15000},  
            //     no end bit                
            };  
#endif
#if 0
             //THOMOSON protocol
            IR_TEST_CTRL ir_test_ctrl[] = 
            {{0, 200}, 
            //NO introduction code                
            //7 data bit,29d
            {1, 141},{0, 7449}, 
                
            {1, 141}, {0, 4919}, 
             {1, 141},{0, 7449}, 
              {1, 141},{0, 7449}, 
              {1, 141},{0, 7449}, 
             {1, 141}, {0, 4919}, 
            {1, 141}, {0, 4919}, 
            {1, 141},{0, 7449},                 
            {1, 141}, {0, 4919}, 
            {1, 141},{0, 7449},                 
            {1, 141}, {0, 4919}, 
            
            {1, 141}, {0,30000},
            {1, 141}    
            };  
#endif     
    u32 ttl_cycle = 0;
    int trig_pol = 1;
    foreach(i, ARRAY_SIZE(ir_test_ctrl)){
        u32 cnt = ir_test_ctrl[i].duration * 38 / 1000;
        foreach(j, cnt){
            if(ir_test_ctrl[i].is_carr){
                ir_record((ttl_cycle * IR_ONE_CYCLE_TICK), trig_pol);
                trig_pol = trig_pol ? 0 : 1;
                ir_record((ttl_cycle * IR_ONE_CYCLE_TICK + IR_CARR_HIGH_TICK), trig_pol);
                trig_pol = trig_pol ? 0 : 1;
            }
            ++ttl_cycle;
        }
    }
}
#if 0//simu ir test
int main(void){
    printf("ir test start\n");
    ir_learn_test();
    printf("start learn wave\n");
    ir_learn();
    printf("ir learn end\n");
}
#endif
#endif

