#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

//#define USE_SW_PWM                1
//#define IRQ_PWM_TIMER             1
#define USE_HW_PWM                1
//#define ZB_SILENT_START_SUPPORT   1

#define _USER_CONFIG_DEFINED_     1    // must define this macro to make others known 

#define USB_PRINTER               1

//////////// product  Infomation  //////////////////////////////
#define ID_VENDOR				0x248a			// for report 
#define ID_PRODUCT_BASE			0x880C
// If ID_PRODUCT left undefined, it will default to be combination of ID_PRODUCT_BASE and the USB config USB_SPEAKER_ENABLE/USB_MIC_ENABLE...
// #define ID_PRODUCT			0x8869

#define STRING_VENDOR			L"Telink"
#define STRING_PRODUCT			L"2.4G Zigbee Pro"
#define STRING_SERIAL			L"TLSR8869"

//#define CHIP_TYPE				CHIP_TYPE_8566		// 8868-24, 8568-32 & 8568-56
#define CHIP_TYPE                 CHIP_TYPE_8869        // 8869, 8666
#define APPLICATION_DONGLE		0			// or else APPLICATION_DEVICE
#define	FLOW_NO_OS				1
#define DONLGE_MONITOR_MODE       0                     // by pass mode,  no sending pkts

    //////////// debug  /////////////////////////////////
#define __MOUSE_SIMU__            0
#define __KEYBOARD_SIMU__         0
#define __DEBUG__                 0

    /////////////////// MODULE /////////////////////////////////

#define MODULE_PM_ENABLE          0
#define MODULE_ETH_ENABLE         0
#define MODULE_MOUSE_ENABLE       0
#define MODULE_USB_ENABLE         1
#define MODULE_BUFM_ENABLE        1
#define MODULE_PRIQ_ENABLE        1

#define MODULE_ADC_ENABLE         0
#define MODULE_AUDIO_ENABLE       0
#define AUD_ENCODER_ENABLE        0
#define MODULE_SPEAKER_ENABLE     0
#define MODULE_MIC_ENABLE         0

#define STATIC_V_INST

    //////////////////// Timer  //////////////////////////////
#define IRQ_TIMER1_ENABLE         1

    ///////////////////  Hardware  //////////////////////////////
#define MODULE_LED_ENABLE         0
    /////////////////// Clock  /////////////////////////////////
#define CLOCK_SYS_TYPE            CLOCK_TYPE_PLL    //  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ        30000000

    /////////////////// watchdog  //////////////////////////////


    ///////////////////  interrupt  //////////////////////////////
#define IRQ_GPIO_ENABLE           1

    ///////////////////  GPIO  /////////////////////////////////
    //  only need to define those are not default
    //  all gpios are default to be output disabled, input disabled, output to 0, output strength to 1
// Antena
// PA GPIO
#define MODULE_RF_PA_ENABLE       1
#if(MODULE_RF_PA_ENABLE)
#define GPIO_RF_PA_TXEN           GPIO_MV
#define GPIO_RF_PA_RXEN           GPIO_ME
#define MV_FUNC                   AS_GPIO
#define MV_OUTPUT_ENABLE          1
#define MV_INPUT_ENABLE           0
#define ME_FUNC                   AS_GPIO
#define ME_OUTPUT_ENABLE          1
#define ME_INPUT_ENABLE           0
#define ME_DATA_OUT               1
#else
#define GPIO_RF_PA_TXEN           
#define GPIO_RF_PA_RXEN

#endif


// ZB_LED, used for Debug in EVK board
//#define ZB_LED_EN                 1



///////////////////  ADC  /////////////////////////////////
#define ADC_CHN0_ANA_INPUT      ADC_CHN_INP_ANA_7
#define ADC_CHN0_REF_SRC        ADC_REF_SRC_INTERNAL


    //////////////////   DFIFO ////////////////////////////////
#define    DFIFO0_SIZE            0
#define    DFIFO1_SIZE            0


    ///////////////////  Keyboard //////////////////////////////
#define MODULE_KEYBOARD_ENABLE    0

    ///////////////////  Audio  /////////////////////////////////
#define MIC_SAMPLE_RATE			16000


    ///////////////////  POWER MANAGEMENT  //////////////////

#define PM_ACTIVE_SUSPEND_WAKEUP_TIME      200         // in ms
#define PM_USB_WAKEUP_TIME                 4           // in ms
#define PM_ENTER_DEEPSLEEP_TIME            600         // in ms

#define PM_SUSPEND_WAKEUP_GPIO_PIN         0
#define PM_SUSPEND_WAKEUP_GPIO_LEVEL       1
#define PM_SUSPEND_WAKEUP_FUNC_PIN         0
#define PM_SUSPEND_WAKEUP_FUNC_LEVEL       1
    /*
    the should be the combination of the followings:
    DEEPSLEEP_WAKEUP_PIN_GPIO0 to DEEPSLEEP_WAKEUP_PIN_GPIO3
    DEEPSLEEP_WAKEUP_PIN_ANA01 to DEEPSLEEP_WAKEUP_PIN_ANA12
    */
#define PM_DEEPSLEEP_WAKEUP_PIN            0
#define PM_DEEPSLEEP_WAKEUP_LEVEL          0

    ///////////////////  USB   /////////////////////////////////
#if (MODULE_USB_ENABLE)
#define    USB_PRINTER_ENABLE              USB_PRINTER    //
#define    USB_SPEAKER_ENABLE              0
#define    USB_MIC_ENABLE                  0
#define    USB_MOUSE_ENABLE                0
#define    USB_KEYBOARD_ENABLE             0
#define    USB_SOMATIC_ENABLE              0   //  when USB_SOMATIC_ENABLE, USB_EDP_PRINTER_OUT disable
//#define USB_SPEAKER_16K                  1
#define    USB_CDC_ENABLE                  0
#define    AUDIO_ENCODER_BUFFER_EN         1
#define    DFIFO1_SIZE                     0
#endif

    ////////////////  ethernet /////////////////    
#define ETH_PHY_RST_GPIO                   GPIO_GP0
#define GPIO0_OUTPUT_ENABLE                1

    ////////////////  hopping /////////////////    
#define HOPPING_ENABLE                     1

    ///////////////////  ZigBee   //////////////
#define TL_RF4CE                           1
#define USE_ZBOSS_MAC                      1
//#define USE_TELINK_MAC                     1

#ifdef WIN32
#define HOST_TRANSCEIVER_MODE_ENABLE     1
#define HOST_ROLE                        1
#define APP_SAVE_TO_FLASH                0
#else
#define APP_SAVE_TO_FLASH                1
#endif

#if (!HOST_ROLE)
#define ZB_CONFIGURABLE_MAC_PIB            1
#endif

#define  USB_PID                       "880f"

/////////////////// set default   ////////////////
#define  EV_POST_TASK_ENABLE       1

#include "../common/default_config.h"

    /////////////////// main loop, event loop  ////////////////
enum{
	EV_FIRED_EVENT_MAX = 1
};

typedef enum{
	EV_EVENT_MAX = 1,
}ev_event_e;

typedef enum{
    EV_POLL_USB_IRQ,
    EV_RF_ERR_CHK_TASK,
    EV_POLL_ED_DETECT,
#if (HOST_ROLE)
	EV_TRANSCEIVER_POLL_TASK,
	EV_SOCK_APP_POLL_TASK,
#endif
    EV_POLL_IDLE, //  Must be the last item in ev_poll_e
	EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

