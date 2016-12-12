
#pragma once

#ifdef WIN32
#include <stdio.h>
#else
int my_printf(const char *fmt, ...);
int my_sprintf(char* s, const char *fmt, ...);

#if (__LOG_RT_ENABLE__)
#define printf
#else
#define printf    my_printf
#endif

#define sprintf    my_sprintf

#endif

