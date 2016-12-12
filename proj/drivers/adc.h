
#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

enum{
    ADC_DONE_SIGNAL_COUNTER,
    ADC_DONE_SIGNAL_RISING,
    ADC_DONE_SIGNAL_FALLING,
};

enum{
    ADC_AUDIO_MODE_NONE,
    ADC_AUDIO_MODE_MONO,
    ADC_AUDIO_MODE_STEREO,
};

enum{
    ADC_SAMPLING_SYCLE_3 = 0,
    ADC_SAMPLING_SYCLE_6 = 1,
    ADC_SAMPLING_SYCLE_9 = 2,
    ADC_SAMPLING_SYCLE_12 = 3,
    ADC_SAMPLING_SYCLE_18 = 4,
    ADC_SAMPLING_SYCLE_24 = 5,
    ADC_SAMPLING_SYCLE_48 = 6,
    ADC_SAMPLING_SYCLE_144 = 7,
};

enum{
    ADC_SAMPLING_RES_6BIT = 0,
    ADC_SAMPLING_RES_7BIT = 1,
    ADC_SAMPLING_RES_8BIT = 2,
    ADC_SAMPLING_RES_9BIT = 3,
    ADC_SAMPLING_RES_10BIT = 4,
    ADC_SAMPLING_RES_11BIT = 5,
    ADC_SAMPLING_RES_12BIT = 6,
    ADC_SAMPLING_RES_13BIT = 7,
};



void adc_clk_en(int en);
int adc_get_value(void);
void adc_alg_pwdn_en(int en);
void adc_init(void);

//void adc_quickSort(u16 *arr, u16 elements) ;
//static inline u16 adc_read(u8 adc_input_channel);


/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif

