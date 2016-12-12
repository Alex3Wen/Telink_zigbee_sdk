
#pragma once

#define OFN_SLIDE_MIN_DISTANCE  30
#define OFN_SLIDE_THRESHOLD     (30*1000)
#define OFN_QK_SLIDE_THRESHOLD  (120*1000)

#define OFN_QK_MASK             BIT(7)
enum{
    OFN_UP,
    OFN_DOWN,
    OFN_LEFT,
    OFN_RIGHT,
    OFN_QK_UP       = OFN_UP    | OFN_QK_MASK,
    OFN_QK_DOWN     = OFN_DOWN  | OFN_QK_MASK,
    OFN_QK_LEFT     = OFN_LEFT  | OFN_QK_MASK,
    OFN_QK_RIGHT    = OFN_RIGHT | OFN_QK_MASK,

    OFN_INVALID,
};

void ofn_getxy(u8 *xy);
void ofn_init(void);
u8 ofn_get_motion(s8 x, s8 y);

#define		A320_I2C_ID		0x66

