/* This file is defined for compatible with Other telink project */

#pragma once

#include "../proj/common/types.h"

#ifdef WIN32
u8 rf_channel = 15;
#endif


int rf_send_pkt_async (void);
void fec_dec_reset_buf(void);

//void rf_init(void);
