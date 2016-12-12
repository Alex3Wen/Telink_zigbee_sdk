
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define _USER_CONFIG_DEFINED_    1    // must define this macro to make others known 

//////////// product  Infomation  //////////////////////////////
#define ID_VENDOR                0x248a            // for report 
#define ID_PRODUCT_BASE            0x880C
// If ID_PRODUCT left undefined, it will default to be combination of ID_PRODUCT_BASE and the USB config USB_SPEAKER_ENABLE/USB_MIC_ENABLE...
// #define ID_PRODUCT            0x8869

#define STRING_VENDOR            L"Telink"
#define STRING_PRODUCT            L"2.4G Wireless Audio"
#define STRING_SERIAL            L"TLSR8869"

#define CHIP_TYPE                CHIP_TYPE_8870        // 8869, 8666
#define APPLICATION_DONGLE        0            // or else APPLICATION_DEVICE

//////////// debug  /////////////////////////////////
#define __MOUSE_SIMU__          0
#define __KEYBOARD_SIMU__          0

/////////////////// MODULE /////////////////////////////////
#define MODULE_DMIC_ENABLE        1
#define MODULE_SPEAKER_ENABLE    0

#define MODULE_SOMATIC_ENABLE   0
#define MODULE_USB_ENABLE        0

#define MODULE_OFN_ENABLE       0
#define MODULE_LED_ENABLE       1
#define MODULE_BATT_ENABLE      0

#define MODULE_PM_ENABLE        1

///////////////////  Hardware  //////////////////////////////

/////////////////// Clock  /////////////////////////////////
#if 0
#define CLOCK_SYS_TYPE          CLOCK_TYPE_PLL    //  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ      30000000
#else
#define CLOCK_SYS_TYPE          CLOCK_TYPE_OSC    //  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ      32000000
#endif
/////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE    1

///////////////////  interrupt  //////////////////////////////

///////////////////  GPIO  /////////////////////////////////
//  only need to define those are not default
//  all gpios are default to be output disabled, input disabled, output to 0, output strength to 1

//  I2C  GPIO
#define PIN_I2C_SCL                GPIO_CK
#define PIN_I2C_SDA                GPIO_DI

#define    CN_FUNC                    AS_GPIO
#define    CK_FUNC                    AS_GPIO
#define    DO_FUNC                    AS_GPIO
#define    DI_FUNC                    AS_GPIO

#define DI_OUTPUT_ENABLE        1
#define DI_INPUT_ENABLE            1
#define DI_DATA_OUT                0

#define CK_INPUT_ENABLE            1
#define CK_DATA_OUT                0

#if(MODULE_DMIC_ENABLE)
//dmic
#define    TE_FUNC                   AS_DMIC
#define    ME_FUNC                   AS_DMIC
#endif

/// Antena
///  PA  gpio
#define GPIO_RF_PA_TXEN         GPIO_SWM
#define GPIO_RF_PA_RXEN         GPIO_SWS

////////////////// keyboard gpio
//  T0,T1,R0,R1功能由一个bit控制，所以必须定义相同
#define    T0_FUNC                 AS_GPIO
#define    T1_FUNC                 AS_GPIO
#define    R0_FUNC                 AS_GPIO
#define    R1_FUNC                 AS_GPIO

//// scan pin ////
#define    GPIO23_INPUT_ENABLE     1
#define    GPIO16_INPUT_ENABLE     1
#define    PWM1_FUNC               AS_GPIO
#define MSC_FUNC                AS_GPIO
#define    PWM1_INPUT_ENABLE           1
#define    MSC_INPUT_ENABLE            1

/// drive pin ////
#define    GPIO19_INPUT_ENABLE     1
//#define    GPIO18_INPUT_ENABLE     1
#define    T0_INPUT_ENABLE            1
#define    T1_INPUT_ENABLE            1
// end of keyboard

// turn on DCDC
#define GPIO8_OUTPUT_ENABLE        1
#define    GPIO8_DATA_OUT            1

//  gyro gpio
#define    GPIO_GSENSOR            GPIO_GP17
#define    GPIO17_INPUT_ENABLE        1
#define    GPIO_GYRO                GPIO_GP25
#define    GPIO25_INPUT_ENABLE        1
#define DO_OUTPUT_ENABLE        1

// led gpio
#define    PWM0_FUNC               AS_GPIO
#define PWM0_OUTPUT_ENABLE        1
#define    PWM0_INPUT_ENABLE        0

#define    SWM_FUNC                   AS_GPIO
#define SWM_OUTPUT_ENABLE        1
#define    SWM_INPUT_ENABLE        0

#define GPIO24_OUTPUT_ENABLE    1


//////////////////    RF configuration //////////////
#define RF_PROTOCOL                RF_PROTO_PROPRIETARY        //  RF_PROTO_PROPRIETARY / RF_PROTO_RF4CE / RF_PROTO_ZIGBEE

///////////////////  ADC  /////////////////////////////////

///////////////////  battery  /////////////////////////////////

#define BATT_ADC_CHANNEL        0
#define BATT_FULL_VOLT            (4100)    //  mV
#define BATT_LOW_VOLT            (3700)    //  mV
#define BATT_NO_PWR_VOLT        (3400)    //  mV
#define    ADC_CHN0_ANA_INPUT        ADC_CHN_INP_ANA_7
#define ADC_CHN0_REF_SRC        ADC_REF_SRC_INTERNAL


///////////////////  Mouse  Keyboard //////////////////////////////
#define MOUSE_HAS_WHEEL            0
#define MOUSE_HAS_BUTTON        1

///////////////////  Audio  /////////////////////////////////
#define MIC_RESOLUTION_BIT        16
#define MIC_SAMPLE_RATE            16000
#define MIC_CHANNLE_COUNT        1
#define    AUD_ENCODER_ENABLE        1

///////////////////  gsensor //////////////////////////////
#define GSENSOR_START_MOVING_CHECK      1
#define GSENSOR_CRANKING_ENABLE         1
#define AIRMOUSE_ENABLE_CHECK           1

///////////////////  POWER MANAGEMENT  //////////////////

#define PM_ACTIVE_SUSPEND_WAKEUP_TIME      20         // in ms
#define PM_ENTER_DEEPSLEEP_TIME            5000    //    600        // in MS

#define PM_SUSPEND_WAKEUP_GPIO_PIN      0
#define PM_SUSPEND_WAKEUP_GPIO_LEVEL      0
#define PM_SUSPEND_WAKEUP_FUNC_PIN         0
#define PM_SUSPEND_WAKEUP_FUNC_LEVEL     0
/*
the should be the combination of the followings:
DEEPSLEEP_WAKEUP_PIN_GPIO0 to DEEPSLEEP_WAKEUP_PIN_GPIO3
DEEPSLEEP_WAKEUP_PIN_ANA01 to DEEPSLEEP_WAKEUP_PIN_ANA12
*/
#define PM_DEEPSLEEP_WAKEUP_PIN         (WAKEUP_SRC_ANA6 | WAKEUP_SRC_ANA9 | WAKEUP_SRC_ANA10)
#define PM_DEEPSLEEP_WAKEUP_LEVEL         1

///////////////////  USB   /////////////////////////////////

////////////////  ethernet /////////////////    
#define ETH_PHY_RST_GPIO            GPIO_GP0

///////////////////  RF4CE   /////////////////////////////////
#define FREAKZ_ENABLE                0
#define TL_RF4CE                    1


/////////////////// set default   ////////////////

#include "../common/default_config.h"

/////////////////// main loop, event loop  ////////////////
enum{ 
    EV_FIRED_EVENT_MAX = 8
};

typedef enum{
    EV_SUSPEND_NOTIFY,
    EV_WAKEUP_NOTIFY,
    EV_KEY_PRESS,
#if(MOUSE_USE_RAW_DATA)
    EV_MOUSE_RAW_DATA,
#endif    
    EV_RF_PKT_RECV,
    EV_PAIRING_START,
    EV_PAIRING_STOP,
    EV_MOUSE_EVENT,
    EV_KEYBOARD_EVENT,
#if(MODULE_SOMATIC_ENABLE)    
    EV_SOMATIC_EVENT,    
#endif
    EV_CALI_START,
    EV_CALI_STOP,
    EV_EVENT_MAX,
}ev_event_e;

typedef enum{
    EV_POLL_MOUSE_EVENT,
    EV_POLL_KEYBOARD_EVENT,
#if(MODULE_SOMATIC_ENABLE)    
    EV_POLL_SOMATIC_EVENT,
#endif    
    EV_POLL_RF_RECV,
    EV_POLL_DEVICE_PKT,
    EV_POLL_RF_CHN_HOPPING,
    EV_POLL_IDLE, //  Must be the last item in ev_poll_e
    EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

