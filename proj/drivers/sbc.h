
#pragma once

#include "../common/bit.h"
#include "../common/types.h"
#include "../config/user_config.h"

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

enum{
    SBC_NROF_SUBBAND_4 = 0,
    SBC_NROF_SUBBAND_8,
};

enum{
    SBC_ALLOCATE_MODE_LOUDNESS = 0,
    SBC_ALLOCATE_MODE_SNR,
};

enum{
    SBC_BLOCK_MODE_4 = 0x00,
    SBC_BLOCK_MODE_8 = 0x01,
    SBC_BLOCK_MODE_12 = 0x02,
    SBC_BLOCK_MODE_16 = 0x03,
};

enum{
    SBC_CHANNEL_MODE_MONO = 0x00,
    SBC_CHANNEL_MODE_DUAL = 0x01,
    SBC_CHANNEL_MODE_STEREO = 0x02,
    SBC_CHANNEL_MODE_JOINT_STEREO = 0x03,
};

enum{
    SBC_FREQUENT_MODE_16 = 0x00,
    SBC_FREQUENT_MODE_32 = 0x01,
    SBC_FREQUENT_MODE_44_1 = 0x02,
    SBC_FREQUENT_MODE_48 = 0x03,
};

int sbc_get_frame_len();
// void sbc_config(int nro_sub, int allocate_mode, int channel_mode, int block_mode, int frequent_mode, int bitpoo);
void sbc_cut_codec_subband(int cut_count);
void sbc_set_subband_gain(u8 i, int encode, int increase, u8 level, int add_half, int add_quarter);
void sbc_init();
int sbc_encode_data_rdy(void);
void sbc_encode_frame(u32 *frame_addr);
void sbc_decode_frame(u32 *frame_addr);
int sbc_busy(void);
int sbc_encode_done(void);
int sbc_decode_done(void);
void sbc_encode_clear(void);
void sbc_decode_clear(void);

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

