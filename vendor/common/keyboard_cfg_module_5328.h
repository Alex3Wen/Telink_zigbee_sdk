
#pragma once

#include "../../proj/drivers/usbkeycode.h"
#include "keycode_custom.h"

#define KB_LINE_MODE            0
#define KB_LINE_HIGH_VALID        0

#define KB_DRV_DELAY_TIME        20                // in us
#define KB_SCAN_DELAY_TIME        20                // in us
#define KB_RM_GHOST_KEY_EN        0

#define KB_HAS_FN_KEY            0

#define  KB_KEY_FLASH_PIN_MULTI_USE   1

u32 drive_pins[] = {
        GPIO_GP0, GPIO_GP1, GPIO_GP2, GPIO_GP3, GPIO_CN
};

u32 scan_pins[] = {
        GPIO_DP, GPIO_DM, GPIO_MSDI, GPIO_MSDO, GPIO_MCLK
};
u8 kb_map[ARRAY_SIZE(scan_pins)][ARRAY_SIZE(drive_pins)] = {
    {VK_0,    VK_1, VK_2, VK_3, VK_4},
    {VK_5,    VK_6, VK_7, VK_8, VK_9},
    {VK_A,    VK_B, VK_C, VK_D, VK_E},
    {VK_F,    VK_G, VK_H, VK_I, VK_J},
    {VK_K,    VK_L, VK_M, VK_N, VK_O},
};

