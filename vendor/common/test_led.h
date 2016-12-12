#ifndef TEST_LED_H
#define TEST_LED_H 1


#if ZB_LED_EN
#define HEART_BEAT_LED            GPIO_GP15
#define NWK_START_LED             GPIO_ANA4
#define COMMISSIONING_LED         GPIO_PWM1
#define RF_INDICATOR_LED          GPIO_GP16
#define TEST_ONOFF_LED            NWK_START_LED
#else
#define HEART_BEAT_LED            GPIO_GP16
#define NWK_START_LED             GPIO_GP16
#define COMMISSIONING_LED         GPIO_GP16
#define RF_INDICATOR_LED          GPIO_GP16
#define TEST_ONOFF_LED            NWK_START_LED
#endif

void zb_led_init(void);

#endif