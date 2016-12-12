
#include "../mcu/register.h"
#include "../common/utility.h"
#include "../common/assert.h"
#include "syshw.h"
#include "sbc.h"
#include "dfifo.h"

#define SUB_COEFF_COUNT        60
const u32 coeff_int[SUB_COEFF_COUNT] = {
    // for sub-band 4
    0x00000023,0x006200b3,
    0x00fb00ff,0x007aff37,
    0x02cb053b,0x0764083e,
    0x06a00192,0xf89fec1f,
    0x22b631eb,0x3f244826,
    0x4b584826,0x3f2431eb,
    0xdd4aec1f,0xf89f0192,
    0x06a0083e,0x0764053b,
    0xfd35ff37,0x007a00ff,
    0x00fb00b3,0x00620023,
    // for sub-band 8
    0x0000000a,0x00160024,
    0x0036004b,0x00610075,
    0x0084008a,0x0083006a,
    0x003bfff4,0xff94ff1b,
    0x0173020e,0x02ad0343,
    0x03c00412,0x042703ec,
    0x03500244,0x00c0febe,
    0xfc41f951,0xf5fff262,
    0x1168153e,0x18fb1c77,
    0x1f8e221e,0x24082538,
    0x259f2538,0x2408221e,
    0x1f8e1c77,0x18fb153e,
    0xee98f262,0xf5fff951,
    0xfc41febe,0x00c00244,
    0x035003ec,0x04270412,
    0x03c00343,0x02ad020e,
    0xfe8dff1b,0xff94fff4,
    0x003b006a,0x0083008a,
    0x00840075,0x0061004b,
    0x00360024,0x0016000a
};

// The final gain is calculated as follows:
// if (increase == 1) then gain = 2 ** level + (1/2) * add_half + (1/4) * add_quarter
// if (increase == 0) then gain = 2 ** (-level)

// 1:  increase,  0: decrease
enum{
    SBC_GAIN_SB0_INC = 0,
    SBC_GAIN_SB1_INC = 0,
    SBC_GAIN_SB2_INC = 0,
    SBC_GAIN_SB3_INC = 0,
    SBC_GAIN_SB4_INC = 0,
    SBC_GAIN_SB5_INC = 0,
    SBC_GAIN_SB6_INC = 0,
    SBC_GAIN_SB7_INC = 0,
};

// intial suband gains, gain = 2**level
enum{
    SBC_GAIN_SB0_LEVEL = 0,
    SBC_GAIN_SB1_LEVEL = 0,
    SBC_GAIN_SB2_LEVEL = 0,
    SBC_GAIN_SB3_LEVEL = 0,
    SBC_GAIN_SB4_LEVEL = 0,
    SBC_GAIN_SB5_LEVEL = 0,
    SBC_GAIN_SB6_LEVEL = 0,
    SBC_GAIN_SB7_LEVEL = 0,
};

// 1:  add 1/2 gain,  0: no addition
enum{
    SBC_GAIN_SB0_ADD_HALF = 0,
    SBC_GAIN_SB1_ADD_HALF = 0,
    SBC_GAIN_SB2_ADD_HALF = 0,
    SBC_GAIN_SB3_ADD_HALF = 0,
    SBC_GAIN_SB4_ADD_HALF = 0,
    SBC_GAIN_SB5_ADD_HALF = 0,
    SBC_GAIN_SB6_ADD_HALF = 0,
    SBC_GAIN_SB7_ADD_HALF = 0,
};

// 1:  add 1/4 gain,  0: no addition
enum{
    SBC_GAIN_SB0_ADD_QUART = 0,
    SBC_GAIN_SB1_ADD_QUART = 0,
    SBC_GAIN_SB2_ADD_QUART = 0,
    SBC_GAIN_SB3_ADD_QUART = 0,
    SBC_GAIN_SB4_ADD_QUART = 0,
    SBC_GAIN_SB5_ADD_QUART = 0,
    SBC_GAIN_SB6_ADD_QUART = 0,
    SBC_GAIN_SB7_ADD_QUART = 0,
};
//  1: encode,  0: decode
#define SBC_GAIN_CODEC_MODE        1

// sbc config
#define SBC_NORF_SUBBAND    SBC_NROF_SUBBAND_8
#define SBC_ALLOC_MODE        SBC_ALLOCATE_MODE_LOUDNESS
#define SBC_CHANNEL_MODE    SBC_CHANNEL_MODE_STEREO
#define SBC_BLOCK_MODE        SBC_BLOCK_MODE_16
#define SBC_FREQUENT_MODE    SBC_FREQUENT_MODE_32
#define SBC_BITPOOL            64

#define        SBC_COEF_RATIO        192
static inline void sbc_init_coeff(){
    // set coeffs address
    static u32 _attribute_aligned_(256) sbc_buf[640];
    reg_sbc_ram_addr = (u8)((((u32)(&sbc_buf[0])) & 0xffff) >> 8);

    s16 *pd = (s16 *) (sbc_buf + 0xf0);
    s16 *ps = (s16 *) coeff_int;
    foreach(i, 2*SUB_COEFF_COUNT){                 //set the coeff table!  table address = base_address+ 0x3c0
        *pd++ = (SBC_COEF_RATIO * (*ps++)) >> 8;
    }
}

static inline void sbc_init_gain(void){
    reg_sbc_gain_band0123 = 
        (MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB0_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB0_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB0_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB0_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) | 
        ((
        MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB1_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB1_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB1_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB1_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) << 8) |
        ((
        MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB2_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB2_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB2_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB2_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) << 16) |
        ((
        MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB3_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB3_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB3_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB3_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) << 24);

    reg_sbc_gain_band4567 = 
        (MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB4_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB4_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB4_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB4_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) |
        ((
        MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB5_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB5_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB5_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB5_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) << 8) |
        ((
        MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB6_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB6_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB6_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB6_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) << 16) |
        ((
        MV(FLD_GAIN_ADD_QUART, SBC_GAIN_SB7_ADD_QUART) | MV(FLD_GAIN_ADD_HALF, SBC_GAIN_SB7_ADD_HALF) |
        MV(FLD_GAIN_SHFT_BITS, SBC_GAIN_SB7_LEVEL) | MV(FLD_GAIN_SHFT_DIR, SBC_GAIN_SB7_INC) | MV(FLD_GAIN_ENC_DEC, SBC_GAIN_CODEC_MODE)
        ) << 24);
    
}

static int sbc_frame_len = 0;
int sbc_get_frame_len(){
    return sbc_frame_len;
}
static inline void sbc_config(int nro_sub, int allocate_mode, int channel_mode, int block_mode, int frequent_mode, int bitpool){
/*The value of the bitpool field shall not exceed 
16 * nrof_subbands for the MONO and DUAL_CHANNEL channel modes 
and 32 * nrof_subbands for the STEREO and JOINT_STEREO channel modes.*/
    assert((SBC_CHANNEL_MODE_MONO == channel_mode || SBC_CHANNEL_MODE_DUAL == channel_mode)?(bitpool <= 16 * (4 * (1 + nro_sub))):(bitpool <= 32 * (4 * (1 + nro_sub))));

    reg_sbc_ctrl = MASK_VAL(FLD_SBC_BITPOOL,bitpool,
        FLD_SBC_NRO_BUB, nro_sub,
        FLD_SBC_ALLOC_MODE, allocate_mode,
        FLD_SBC_CHN_MODE,channel_mode,
        FLD_SBC_BLK_MODE,block_mode,
        FLD_SBC_FREQ_MODE,frequent_mode);
    
    /*  frame length calculation    
    frame_length = 4 + (4 *  subbands * channels ) / 8  + blocks * channels * bitpool / 8
    */  
    sbc_frame_len = 4 + (4 * (4 * (1 + nro_sub)) * (channel_mode==SBC_CHANNEL_MODE_MONO?1:2)) / 8 + ((4 * (1 + block_mode)) * (channel_mode==SBC_CHANNEL_MODE_MONO?1:2) * bitpool) / 8;
    return;
}

void sbc_cut_codec_subband(int cut_count){
    assert(cut_count < 8);
    int c = 8 - cut_count;
    while(c < 8){
        reg_sbc_gain(c) = MASK_VAL(FLD_GAIN_SHFT_BITS, ALL_SET);
        ++c;
    }
}

// ecode: 1: for encode,  0: for decode
// increase:  1: increase,  0: decrease
// GAIN == 2 ** level + add_half / 2 + add_quarter / 4
void sbc_set_subband_gain(u8 i, int encode, int increase, u8 level, int add_half, int add_quarter){
    assert(i < 8);
    reg_sbc_gain(i) = MASK_VAL(FLD_GAIN_ENC_DEC,encode,
        FLD_GAIN_SHFT_DIR, increase, 
        FLD_GAIN_SHFT_BITS,level,
        FLD_GAIN_ADD_HALF, add_half, 
        FLD_GAIN_ADD_QUART, add_quarter);
}

void sbc_init(){

#ifdef SBC_CONFIG_ENCODER
    sbc_init_coeff();
    sbc_init_gain();
    sbc_config(SBC_CONFIG_ENCODER);
#else
    sbc_config(SBC_NORF_SUBBAND, SBC_ALLOC_MODE, SBC_CHANNEL_MODE, SBC_BLOCK_MODE, SBC_FREQUENT_MODE_48, SBC_BITPOOL);
#endif
    NOTE("32k frequent means 0x78 not 0xb8??");
}

int sbc_encode_data_rdy(void){
    return dfifo1_high();
}

void sbc_encode_frame(u32 *frame_addr){
    reg_sbc_enc_buf_addr = (u16)(u32)(frame_addr);
    reg_sbc_codec_en = FLD_SBC_ENC_EN;
}

void sbc_decode_frame(u32 *frame_addr){
    reg_sbc_dec_buf_addr = (u16)(u32)(frame_addr);
    reg_sbc_codec_en = FLD_SBC_DEC_EN;
}

int sbc_busy(void){
    return reg_sbc_codec_en & (FLD_SBC_DEC_EN | FLD_SBC_ENC_EN);
}

int sbc_encode_done(void){
    return reg_sbc_irq & FLD_SBC_IRQ_ENC;
}

int sbc_decode_done(void){
    return reg_sbc_irq & FLD_SBC_IRQ_DEC;
}

void sbc_encode_clear(void){
    reg_sbc_irq = FLD_SBC_IRQ_ENC;
}

void sbc_decode_clear(void){
    reg_sbc_irq = FLD_SBC_IRQ_DEC;
}

