
#include "../tl_common.h"
#include "../drivers/adc.h"
#include "../drivers/dfifo.h"
#include "../drivers/audio.h"
#include "../drivers/sbc.h"
#include "syshw.h"

void syshw_init(){
	dma_init();
	gpio_init();
#if (MODULE_ADC_ENABLE)
	adc_init();
#endif
#if(MODULE_AUDIO_ENABLE)
	dfifo_init();
	aud_init();
#if(MIC_ENOCDER_ENABLE)
	sbc_init();
#endif
#endif	
}


