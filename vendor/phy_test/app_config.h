#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

#define _USER_CONFIG_DEFINED_     1    // must define this macro to make others known 

#define USB_PRINTER               0

    //////////// product  Infomation  //////////////////////////////
#define ID_VENDOR				0x248a			// for report
//#define ID_PRODUCT_BASE         0x8800
// If ID_PRODUCT left undefined, it will default to be combination of ID_PRODUCT_BASE and the USB config USB_SPEAKER_ENABLE/USB_MIC_ENABLE...
#define ID_PRODUCT_BASE			0x0152
#define	ID_PRODUCT				(0x0152 + USB_PRINTER)

#define STRING_VENDOR             L"Telink"
#define STRING_PRODUCT            L"PHY Test"
#define STRING_SERIAL			  L"TLSR8869"

#define CHIP_TYPE				CHIP_TYPE_8869		// 8868-24, 8568-32 & 8568-56

#define APPLICATION_DONGLE        1                     // or else APPLICATION_DEVICE
#define DONLGE_MONITOR_MODE       0                     // by pass mode,  no sending pkts

    //////////// debug  /////////////////////////////////
#define __MOUSE_SIMU__            0
#define __KEYBOARD_SIMU__         0
#define __DEBUG__                 0
#define __DEBUG_BUFM__            1
#define __LOG_RT_ENABLE__         0

    /////////////////// MODULE /////////////////////////////////

#define MODULE_PM_ENABLE          0
#define MODULE_FLASH_ENABLE       1
#define MODULE_ETH_ENABLE         0
#define MODULE_USB_ENABLE         1
#define MODULE_MIC_ENABLE         0
#define MOUDLE_SPEAKER_ENABLE     0
#define MODULE_BUFM_ENABLE        1
#define MODULE_PRIQ_ENABLE        1
#define EV_POST_TASK_ENABLE       1
#define STATIC_V_INST

#define MODULE_AUDIO_ENABLE       0
    //////////////////// Timer  //////////////////////////////
#define IRQ_TIMER1_ENABLE         1
#define IRQ_PWM_TIMER             0


    ///////////////////  Hardware  //////////////////////////////
#define MODULE_LED_ENABLE         0
    /////////////////// Clock  /////////////////////////////////
#define CLOCK_SYS_TYPE            CLOCK_TYPE_PLL    //  one of the following:  CLOCK_TYPE_PLL, CLOCK_TYPE_OSC, CLOCK_TYPE_PAD, CLOCK_TYPE_ADC
#define CLOCK_SYS_CLOCK_HZ        32000000

    /////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE      0
#define WATCHDOG_INIT_TIMEOUT       800

#define ENABLE_FREQ_AGILITY   1

    ///////////////////  interrupt  //////////////////////////////
#define IRQ_GPIO_ENABLE           0

///////////////////  GPIO  /////////////////////////////////
//  only need to define those are not default
//  all gpios are default to be output disabled, input disabled, output to 0, output strength to 1
#define	MAXTRIX_GPIO_PULL_DOWN      PM_PIN_PULLDOWN_100K

#define PULL_GLOBAL             MAXTRIX_GPIO_PULL_DOWN
#define	PULL_WAKEUP_SRC_PWM0	MAXTRIX_GPIO_PULL_DOWN


#define	CK_FUNC			AS_GPIO
#define CK_OUTPUT_ENABLE  1
#define CK_INPUT_ENABLE   0
#define CK_DATA_OUT     0


#define	DI_FUNC			AS_GPIO	
#define DI_OUTPUT_ENABLE  1
#define DI_INPUT_ENABLE   0
#define DI_DATA_OUT     0


#define PWM0_FUNC       AS_GPIO
#define PWM0_OUTPUT_ENABLE  1
#define	PWM0_INPUT_ENABLE		0
#define PWM0_DATA_OUT     0


//#define SWS_FUNC       AS_GPIO
//#define SWS_OUTPUT_ENABLE       1
//#define SWS_INPUT_ENABLE        0
//#define SWS_DATA_OUT            1


#define SWM_FUNC       AS_GPIO
#define SWM_OUTPUT_ENABLE       1
#define SWM_INPUT_ENABLE        0
#define SWM_DATA_OUT            1


#define	GPIO14_OUTPUT_ENABLE		1
#define	GPIO14_INPUT_ENABLE		0
#define GPIO14_DATA_OUT     0

// Antena
// PA GPIO
#define MODULE_RF_PA_ENABLE       1
#if (MODULE_RF_PA_ENABLE)
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





    ///////////////////  ADC  /////////////////////////////////

    //////////////////   DFIFO ////////////////////////////////
#define    DFIFO0_SIZE            0
#define    DFIFO1_SIZE            0

    ///////////////////  Air Mouse //////////////////////////////
#define MODULE_MOUSE_ENABLE       0
#define AIR_MOUSE_EN              0
#define	GYRO_L3G_ENABLE  	      0
#define	GSENSOR_MMA865X_ENABLE	  0



    ///////////////////  Keyboard //////////////////////////////
#define MODULE_KEYBOARD_ENABLE    0

    ///////////////////  Audio  /////////////////////////////////
//#define MIC_RESOLUTION_BIT      16
//#define MIC_SAMPLE_RATE         16000
//#define MIC_CHANNLE_COUNT       1
//#define    AUD_ENCODER_ENABLE   1
#define MIC_SAMPLE_RATE			16000

#define USB_SPEAKER_48K_COMPACT   0
#define DEC_BUFF_SIZE             (MIC_BIT_POOL * 2 + 12 )
#define SPEAKER_BIT_POOL          (USB_SPEAKER_48K_COMPACT ? 0x28 : 0x48)

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
#define    USB_CDC_ENABLE                  1
//#define USB_SPEAKER_16K                  1
#define    AUDIO_ENCODER_BUFFER_EN         0
#define    DFIFO1_SIZE                     0
#endif

    ////////////////  ethernet /////////////////    
#define ETH_PHY_RST_GPIO                   GPIO_GP0
#define GPIO0_OUTPUT_ENABLE                1

    ////////////////  hopping /////////////////    
#define HOPPING_ENABLE                     1

    ///////////////////  RF4CE   /////////////////////////////////
#define FREAKZ_ENABLE                      0
#define TL_RF4CE                           1
#define RF_STATISTIC_ENABLE                1


#define RF4CE_MAX_PAIR_ENTRY_NUM           1

#define HOST_TRANSCEIVER_MODE_ENABLE     0
#define HOST_ROLE                        0

#define  USB_PID                       "881f"

    ///////////////////  RF4CE Profile Configuration /////////////////////////////////
#include "profile_config.h"

    /////////////////// set default   ////////////////
#include "../common/default_config.h"

    /////////////////// main loop, event loop  ////////////////
enum{
	EV_FIRED_EVENT_MAX = 1
};

typedef enum{
	EV_SUSPEND_NOTIFY,
	EV_EVENT_MAX,
} ev_event_e;

typedef enum{
    EV_POLL_USB_IRQ,
    EV_RF_ERR_CHK_TASK,
	EV_POLL_KEYBOARD_RELEASE_CHECK,
	EV_POLL_MOUSE_REPORT,
	EV_POLL_MOUSE_RELEASE_CHECK,
	EV_POLL_ED_DETECT,
	EV_POLL_EMI_TEST,
    EV_POLL_IDLE, //  Must be the last item in ev_poll_e
	EV_POLL_MAX,
}ev_poll_e;

    /* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

