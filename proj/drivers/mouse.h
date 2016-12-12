
#pragma once

#include "../config/user_config.h"
#include "../common/types.h"
#include "../common/bit.h"
#include "../common/utility.h"

#define MOUSE_LEFT_BTN_DOWN_MASK		BIT(0)
#define MOUSE_RIGHT_BTN_DOWN_MASK		BIT(1)
#define MOUSE_MID_BTN_DOWN_MASK		    BIT(2)
#define MOUSE_FWD_BTN_DOWN_MASK		    BIT(3)
#define MOUSE_BWD_BTN_DOWN_MASK		    BIT(4)



typedef struct {
	s8 btn;
	s8 x;
	s8 y;
	s8 w;
}mouse_data_t;

extern int mouse_drv_getxy(mouse_data_t *data);
extern void mouse_drv_getbtn(mouse_data_t *mouse_data);
extern int mouse_drv_getwheel(void);

void mouse_init(void);
int mouse_wheel_chk_dir(u32 w0, u32 w1);	// expose for unit testing
int mouse_is_data_not_empty(mouse_data_t *data);
void mouse_set_data_empty(mouse_data_t *data);


