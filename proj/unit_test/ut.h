
#pragma once

#include "../common/printf.h"

extern int ut_case_fail;

typedef void (*ut_func_t)(void);
#define ut_assert(message, test)     do{ if (!(test)){printf("Test fail at %s:%d, %s\r\n",__FUNCTION__, __LINE__, message); ut_case_fail = 1;} } while (0)

int ut_unit_test();

