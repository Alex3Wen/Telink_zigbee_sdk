
#pragma once

#ifdef WIN32        //  win32 simulation

#define WIN32_ZBOSS_APP   0
#define WIN32_ZBTEST_APP  0
#define WIN32_XAVI_GW     0
#define WIN32_XAVI_LIGHT  0
#define WIN32_OTA_SAMPLE  0
#define WIN32_HA_LIGHT    1
#define WIN32_HA_GW       0



#if (WIN32_ZBOSS_APP)
#define __PROJECT_ZBOSS__        1
#define ZB_PLATFORM_TELINK_TC32
#endif

#if (WIN32_ZBTEST_APP)
#define __PROJECT_ZIGBEE_TEST__     1
#endif

#if (WIN32_XAVI_GW)
#define __PROJECT_XAVI_GW__     1
#endif

#if (WIN32_XAVI_LIGHT)
#define __PROJECT_XAVI_LIGHT__     1
#endif

#if (WIN32_OTA_SAMPLE)
#define __PROJECT_OTA_SAMPLE__     1
#endif

#if (WIN32_HA_LIGHT)
#define __PROJECT_HA_LIGHT__     1
#endif

#if (WIN32_HA_GW)
#define __PROJECT_HA_GATEWAY__     1
#endif

#endif

#if(__PROJECT_PM_TEST_5320__)    //  min environment for testing PM functionality. 
    #define __PROJECT_PM_TEST__                1
    #include "device.h"
#elif (__PROJECT_ZBOSS__)
    #include "../meshApp/app_config.h"
#elif (__PROJECT_ZIGBEE_TEST__)
    #include "../zigbeeTest/app_config.h"
#elif (__PROJECT_XAVI_GW__)
    #include "../xavi_gateway/app_config.h"
#elif (__PROJECT_XAVI_LIGHT__)
    #include "../xavi_light/app_config.h"
#elif (__PROJECT_OTA_SAMPLE__)
    #include "../otaSample/app_config.h"
#elif (__PROJECT_HA_LIGHT__)
    #include "../ha_light/app_config.h"
#elif (__PROJECT_HA_GATEWAY__)
    #include "../ha_gateway/app_config.h"
#elif (__PROJECT_PHY_TEST__)
	#include "../phy_test/app_config.h"
#elif (__PROJECT_MAC_TEST__)
	#include "../mac_test/app_config.h"
#elif (__PROJECT_MESH_APP__)
    #include "../zb_meshApp/app_config.h"
#else
    #include "user_config_common.h"
#endif


