
#pragma once

#include "../common/types.h"

void i2c_init(void);
void i2c_write(u8 id, u8 addr, u8 dat);
u8 i2c_read(u8 id, u8 addr);
void i2c_burst_read(u8 id, u8 addr, u8 *p, u8 n);

