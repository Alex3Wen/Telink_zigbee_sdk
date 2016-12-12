
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define _USER_CONFIG_DEFINED_    1    // must define this macro to make others known 

#define    USB_PRINTER                1
//////////// product  Infomation  //////////////////////////////
#define ID_VENDOR                0x248a            // for report
//#define ID_PRODUCT_BASE            0x8800
// If ID_PRODUCT left undefined, it will default to be combination of ID_PRODUCT_BASE and the USB config USB_SPEAKER_ENABLE/USB_MIC_ENABLE...
#define ID_PRODUCT_BASE            (0x880e + USB_PRINTER)

#define STRING_VENDOR            L"Telink"
#define STRING_PRODUCT            L"Remote Control"
#define STRING_SERIAL            L"TLSR8869"

#define CHIP_TYPE                CHIP_TYPE_8870        // 8869, 8666
#define APPLICATION_DONGLE        1            // or else APPLICATION_DEVICE
#define DONLGE_MONITOR_MODE        0            // by pass mode,  no sending pkts

//////////// debug  /////////////////////////////////
#define __MOUSE_SIMU__      0
#define __KEYBOARD_SIMU__      0

/////////////////// MODULE /////////////////////////////////

#define MODULE_PM_ENABLE        0
#define MODULE_ETH_ENABLE        0

///////////////////  Hardware  //////////////////////////////

/////////////////// Clock  /////////////////////////////////
#define CLOCK_SYS_TYPE          CLOCK_TYPE_PLL    //  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ      30000000

/////////////////// watchdog  //////////////////////////////


///////////////////  interrupt  //////////////////////////////

///////////////////  GPIO  /////////////////////////////////
//  only need to define those are not default
//  all gpios are default to be output disabled, input disabled, output to 0, output strength to 1

/// Antena
///  PA  gpio
#define MODULE_RF_PA_ENABLE        0
#if(MODULE_RF_PA_ENABLE)
#define GPIO_RF_PA_TXEN         GPIO_MV
#define GPIO_RF_PA_RXEN         GPIO_ME
#define    MV_FUNC                    AS_GPIO
#define MV_OUTPUT_ENABLE        1
#define MV_INPUT_ENABLE            0
#define    ME_FUNC                    AS_GPIO
#define ME_OUTPUT_ENABLE        1
#define ME_INPUT_ENABLE            0
#define ME_DATA_OUT                1
#endif

// ir
#define    GPIO_IR                    GPIO_GP21
#define GPIO21_OUTPUT_ENABLE    1

//////////////////    RF configuration //////////////
#define RF_PROTOCOL                RF_PROTO_PROPRIETARY        //  RF_PROTO_PROPRIETARY / RF_PROTO_RF4CE / RF_PROTO_ZIGBEE

///////////////////  ADC  /////////////////////////////////


///////////////////  Keyboard //////////////////////////////
#define KB_PWR_TIME_INTERVAL        (2000*1000)


///////////////////  Audio  /////////////////////////////////
#define MIC_RESOLUTION_BIT        16
#define MIC_SAMPLE_RATE            16000
#define MIC_CHANNLE_COUNT        1
#define    AUD_ENCODER_ENABLE        1

#define    USB_SPEAKER_48K_COMPACT    0


///////////////////  POWER MANAGEMENT  //////////////////

#define PM_ACTIVE_SUSPEND_WAKEUP_TIME      200         // in ms
#define PM_USB_WAKEUP_TIME              4     // in ms
#define PM_ENTER_DEEPSLEEP_TIME            600        // in MS
#define PM_REMOTE_WAKEUP_ENABLE            0        // in MS

#define PM_SUSPEND_WAKEUP_GPIO_PIN      0
#define PM_SUSPEND_WAKEUP_GPIO_LEVEL      1
#define PM_SUSPEND_WAKEUP_FUNC_PIN         0
#define PM_SUSPEND_WAKEUP_FUNC_LEVEL     1
/*
the should be the combination of the followings:
DEEPSLEEP_WAKEUP_PIN_GPIO0 to DEEPSLEEP_WAKEUP_PIN_GPIO3
DEEPSLEEP_WAKEUP_PIN_ANA01 to DEEPSLEEP_WAKEUP_PIN_ANA12
*/
#define PM_DEEPSLEEP_WAKEUP_PIN         0
#define PM_DEEPSLEEP_WAKEUP_LEVEL         0

///////////////////  USB   /////////////////////////////////
#if(APPLICATION_DONGLE)
#define    USB_PRINTER_ENABLE         USB_PRINTER    //
#define    USB_SPEAKER_ENABLE         1
#define    USB_MIC_ENABLE             1
#define    USB_MOUSE_ENABLE         1
#define    USB_KEYBOARD_ENABLE     1
#define    USB_SOMATIC_ENABLE      0   //  when USB_SOMATIC_ENABLE, USB_EDP_PRINTER_OUT disable
//#define USB_SPEAKER_16K            1
#define    AUDIO_ENCODER_BUFFER_EN    1
#define    DFIFO1_SIZE             0x400
#define    DFIFO0_SIZE             0x400
#endif

////////////////  ethernet /////////////////    
#define ETH_PHY_RST_GPIO            GPIO_GP0
#define GPIO0_OUTPUT_ENABLE            1

////////////////  hopping /////////////////    
#define HOPPING_ENABLE                1

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
#if(USB_SOMATIC_ENABLE)
    EV_USB_OUT_DATA,
#endif

    EV_RF_PKT_RECV,
    EV_EVENT_MAX,
}ev_event_e;

typedef enum{
    EV_POLL_RF_RECV,
    EV_POLL_USB_IRQ,
    EV_POLL_DEVICE_PKT,
    EV_POLL_AUDIO_DEC,
    EV_POLL_MOUSE_REPORT,
    EV_POLL_MOUSE_RELEASE_CHECK,
    EV_POLL_KEYBOARD_RELEASE_CHECK,
    EV_POLL_RF_CHN_HOPPING,
#if(MODULE_ETH_ENABLE)    
    EV_POLL_ETH_RECV,
#endif    
    EV_POLL_IDLE, //  Must be the last item in ev_poll_e
    EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

