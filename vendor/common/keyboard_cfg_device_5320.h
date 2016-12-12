
#pragma once

#include "../../proj/drivers/usbkeycode.h"
#include "keycode_custom.h"

#define KB_LINE_MODE            0
#define KB_LINE_HIGH_VALID        0

#define KB_DRV_DELAY_TIME        2                // in us
#define KB_SCAN_DELAY_TIME        2                // in us
#define KB_RM_GHOST_KEY_EN        0

#define KB_HAS_FN_KEY            0

static const u32 drive_pins[] = {
        GPIO_GP19, GPIO_T0, GPIO_T1
};

static const u32 scan_pins[] = {
        GPIO_GP23, GPIO_PWM1,  GPIO_GP16, GPIO_MSC
};
const u8 kb_map[ARRAY_SIZE(scan_pins)][ARRAY_SIZE(drive_pins)] = {
        {VK_B,            VK_LEFT,        VK_S    },
        {VK_PAGE_UP,    VK_UP,            VK_ESC    },
        {VK_PAGE_DOWN,    VK_MOUSE_LEFT,    VK_RIGHT},
        {VK_F5,            VK_MOUSE_RIGHT,    VK_DOWN    }
};

