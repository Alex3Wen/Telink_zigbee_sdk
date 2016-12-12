#pragma once

/**
 *  @brief  Definition for ZRC device type
 */
enum {
    DEVICE_RESERVED      = 0,
    DEVICE_RC,
    DEVICE_TV,
    DEVICE_PROJECTOR,
    DEVICE_PLAYER,
    DEVICE_RECORDER,
    DEVICE_DVD,
    DEVICE_CD,
    DEVICE_AUDIO,
    DEVICE_STB,
    DEVICE_ALL          =0xFF,
};

/**
 *  @brief  Macro for Remote Control device type
 */
#define RF4CE_DEVICE_TYPE(type)                  (1<<type)

/**********************************************************************
 * Following feature need user to enable
 */

/**
 *  @brief  Definition for which profile to use
 */
#define RF4CE_ZID_ENABLE                          0
#define RF4CE_ZRC_ENABLE                          1


/**
 *  @brief  Definition for Device Type, only one can be enabled
 */
#if (RF4CE_ZID_ENABLE)
    #define ZID_HID_ADAPTER                       1
    #define ZID_HID_CLASS_DEVICE                  0
#endif

#if (RF4CE_ZRC_ENABLE)
    #define ZRC_REMOTE_CONTROLLER                 0
    #define ZRC_TARGET_DEVICE                     1
#endif

/**
 *  @brief  Specify the product device type
 */
#define RF4CE_DEV_TYPE                            RF4CE_DEVICE_TYPE(DEVICE_TV)

/**
 *  @brief  Specify using Security or not
 */
#define SECURITY_ENABLE                           1

#define FREQUENCY_AGILITY_SAMPLE_INTERVAL         2 * 1000  //2ms
#define FREQUENCY_AGILITY_TIMES_PER_CH            32
#define FREQUENCY_AGILITY_ED_THRESHOD             0x30
#define FREQUENCY_AGILITY_NOISY_THRESHOD          0x10
/**********************************************************************
 * Following configuration will calculated automatically
 */

#if (RF4CE_ZID_ENABLE)
    #define RF4CE_GDP_ENABLE                      1
#else
    #define RF4CE_GDP_ENABLE                      0
#endif


#if (ZID_HID_ADAPTER)
    #define RF4CE_TARGET                          1
	#define RF4CE_CONTROLLER                      0
#endif

#if (ZID_HID_CLASS_DEVICE)
	#define RF4CE_CONTROLLER                      1
	#define RF4CE_TARGET                          0
#endif

#if (ZRC_TARGET_DEVICE)
    #define RF4CE_TARGET                          1
    #define RF4CE_CONTROLLER                      0
#endif

#if (ZRC_REMOTE_CONTROLLER)
    #define RF4CE_TARGET                          0
    #define RF4CE_CONTROLLER                      1
#endif
