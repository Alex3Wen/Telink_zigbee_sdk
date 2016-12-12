
#include "../mcu/register.h"
#include "../common/assert.h"
#include "../common/static_assert.h"
#include "../mcu/analog.h"
#include "../mcu/anareg_i.h"
#include "syshw.h"
#include "adc.h"
#include "../mcu/clock.h"
#include "dfifo.h"
#include "../common/compatibility.h"
#include "../common/utility.h"

#include "../mcu/gpio.h"
#include "../os/ev.h"
#include "../mcu/irq_i.h"

#include "../mcu/clock_i.h"


#define _ADC_AUTO_MODE_		    0   // 0: ADC Manual mode  , 1: ADC auto mode.
//#define _ADC_BIGDATA_MODE_      // Lab mode for collection ADC result.


// F-sample = 1M / (9+9+1) = 52632.   T = 1/ F-sample = 1.8999 x 10(-5) = 19 us
#ifndef ADC_RECOVER_TIME
#define ADC_RECOVER_TIME            19+30       //us
#endif

#if(CHIP_REVISION == CHIP_REVISION_A5)
#define ADC_SIGN_BIT_ENABLE      0x80
#else
#define ADC_SIGN_BIT_ENABLE      0x00
#endif

#ifndef _ADC_AUTO_MODE_	
#define _ADC_AUTO_MODE_		0
#endif


#if defined(_ADC_BIGDATA_MODE_)
static u16 Semaphore =0 ;
#define SET_ADC_ACTIVE()            (Semaphore |=0x01)
#define CLR_ADC_ACTIVE()            (Semaphore &= ~0x01)
#define IS_ADC_ACTIVE()              (Semaphore & 0x01)

#define SET_DATA_READY()            (Semaphore |=0x02)
#define CLR_DATA_READY()            (Semaphore &= ~0x02)
#define IS_DATA_READY()              (Semaphore & 0x02)
#endif


#if defined(_ADC_BIGDATA_MODE_)
u16 AdcSample0Buff[256];  //128   
#endif

//u16 AdcSample1Buff[128];

//u32 clock_record ;
//u32 ATimeResult =0 ;

////////////////////////////////////////////////////////////////
//  Function: quickSort
//  Purpose : quick sort algorithm for sorting data.
//  Argument: u16 *arr =>  Data array which contents will be sorted
//                 u16 elements => Number of quick sort elements 
//  Referrer: This public-domain C original implemented by Darel Rex Finley.
//
//  * Example calls:
//    quickSort(&myArray[0],5); // sorts elements 0, 1, 2, 3, and 4
//    quickSort(&myArray[3],5); // sorts elements 3, 4, 5, 6, and 7
////////////////////////////////////////////////////////////////
void adc_quickSort(u16 *arr, u16 elements) 
{
 #ifndef  MAX_ASIZE
 #define  MAX_ASIZE	8
 #elif (MAX_ASIZE > 32)
 #undef   MAX_ASIZE
 #define  MAX_ASIZE	8
 #endif
 
  int pivot, beg[MAX_ASIZE], end[MAX_ASIZE], L, R, swap ,i=0;

  beg[0]=0; end[0]=elements;
  while (i>=0) {
    L=beg[i]; R=end[i]-1;
    if (L<R) {
      pivot=arr[L];
      while (L<R) {
        while (arr[R]>=pivot && L<R) R--; if (L<R) arr[L++]=arr[R];
        while (arr[L]<=pivot && L<R) L++; if (L<R) arr[R--]=arr[L]; }
		
      arr[L]=pivot; beg[i+1]=L+1; end[i+1]=end[i]; end[i++]=L;
      if (end[i]-beg[i]>end[i-1]-beg[i-1]) {
        swap=beg[i]; beg[i]=beg[i-1]; beg[i-1]=swap;
        swap=end[i]; end[i]=end[i-1]; end[i-1]=swap; }}
      else {
      	   i--; 
	}}
}

	  
/////////////////////////////////////////////////////////////////

static inline void adc_set_sampling(int cyc0, int res0, int cyc1_2)
{
    reg_adc_samp_clk_res = MASK_VAL(FLD_ADC_CHN0_SAMP_CYCLE,cyc0, FLD_ADC_CHN0_SAMP_RESOL, res0, FLD_ADC_CHN12_SAMP_CYCLE, cyc1_2);
}

static inline void adc_set_clk_freq(u8 mhz)
{
    assert((reg_adc_mod_h & FLD_ADC_MOD_H) == 0 && (reg_adc_mod_h & FLD_ADC_MOD_H_STEP) == 0);    // use low bits only
    reg_adc_mod = MASK_VAL(FLD_ADC_MOD, CLK_FHS_MZ, FLD_ADC_CLK_EN, 1);
    reg_adc_step_l = mhz;
}

void adc_clk_en(int en)
{
    if	(en){
        SET_FLD(reg_adc_mod_h, FLD_ADC_MOD_H_CLK);
    }else{
        CLR_FLD(reg_adc_mod_h, FLD_ADC_MOD_H_CLK);
    }
}

static inline u16 adc_read(u8 adc_input_channel)
{
#if _ADC_AUTO_MODE_
    return reg_adc_dat_byp_outp ;    // mst read 0x34, 0x35 to get channel 1 value
#else
    u8 r = irq_disable();
    write_reg8(0x80002c, adc_input_channel);
    write_reg8(0x800035, 0x80);      //Manual operation    
    while((read_reg8(0x800035) & 0x80) != 0x00);
    irq_restore(r);
    return reg_adc_dat_byp_outp;
#endif /* _ADC_AUTO_MODE_ */
}


///////////////////////////////////////////////////////////////////////////////
// Function: void Adc_get_BigData()
// Purpose: Fetch big amount of ADC result 
// Return : Result store in the AdcSample0Buff[] .
//////////////////////////////////////////////////////////////////////////////
#if defined(_ADC_BIGDATA_MODE_)
  //Test
void Adc_get_BigData()
{
      if (!IS_ADC_ACTIVE())
          return ;
	if (!IS_DATA_READY())
      {
		foreach(i,256)
		{
			AdcSample0Buff[i] = Adc_get_ANA1_GPIO15();     // GPIO 15 (pin 42)
			//AdcSample1Buff[i] = Adc_get_ANA7_GPIO20();     // GPIO 20 (pin 55)
		}
		AdcCh2Value = 0x88 ;
		SET_DATA_READY();
	}
	CLR_ADC_ACTIVE();
}

#endif  





void adc_init(void)
{
    /*[Configure ADC Channel 0 input to get data. */
    reg_adc_setting0 = MASK_VAL(FLD_ADC_CHN_PGA_INP_LEFT0,ADC_PGA_CHN_INP_NONE,
        FLD_ADC_CHN_PGA_INP_RIGHT0, ADC_PGA_CHN_INP_NONE,
        FLD_ADC_CHN_PGA_INP_LEFT12, ADC_PGA_CHN_INP_NONE,
        FLD_ADC_CHN_PGA_INP_RIGHT12, ADC_PGA_CHN_INP_NONE,
        FLD_ADC_REF_CHN0,ADC_REF_SRC_AVDD,     //ADC_CHN0_REF_SRC,    
        FLD_ADC_REF_CHN1,ADC_REF_SRC_AVDD,     //ADC_CHN0_REF_SRC, 	
        FLD_ADC_REF_CHN2,ADC_REF_SRC_AVDD);    //ADC_CHN0_REF_SRC
		
         //Reference internal : 1.3 V ==> ADC_CHN0_REF_SRC
 #if _ADC_AUTO_MODE_
	reg_adc_setting1 = MASK_VAL(FLD_ADC_AUTO_CHN0_ANA_SEL, ADC_CHN_INP_ANA_7,
        FLD_ADC_DIFF_CHN0_ANA_SEL, ADC_CHN_INP_ANA_NONE,
        FLD_ADC_AUTO_CHN1_ANA_SEL, ADC_CHN_INP_ANA_8,
        FLD_ADC_AUTO_CHN2_ANA_SEL, ADC_CHN_INP_ANA_2,
        FLD_ADC_AUTO_CHN_RESV, ((ADC_SAMPLING_RES_8BIT<<3)|ADC_SAMPLING_RES_8BIT));  

	TODO("to cal adc sample rate precisely");
        // M Period  = {ADCMAXMH(0x31) , ADCMAXML (0x30)} = { 0x00 , 0xB8 } = 0xB8;
        // M Freq = 30M (System clock) /184 (0xB8) = 163,043 hz.
        
    	// LR Period = {ADCMAXLR(0x32) } * 16 =  {0x70} * 16 = 0x700 ;
    	// LR Freq = 30M (System clock) / 1792 = 16,741 hz .
    	
        // Ideal Register setting from 0x30 to  0x33 : 30h => 0xB8 , 31h => 0x0 ,32h => 0x70
        // Due to reg shift issue between 0x30 to 0x33 , write 30h => 0xB8 ,31h=> 0x00 , 32h = 0x00 , 33h = F7 ;	
 	reg_adc_samp_and_ctrl = MASK_VAL(FLD_ADC_CHN0_SAMP_DIV_L, 0xB8,
    	FLD_ADC_CHN0_SAMP_DIV_H, 0x0,FLD_ADC_CHN12_SAMP_DIV, 0x0);
		
    write_reg8(0x800033, 0xF7);  //  ch0,ch1,ch2 channel work together.
        
 #else      //Manual mode configuration

    reg_adc_setting1 = MASK_VAL(FLD_ADC_AUTO_CHN0_ANA_SEL, ADC_CHN_INP_ANA_7,
        FLD_ADC_DIFF_CHN0_ANA_SEL, ADC_CHN_INP_ANA_NONE);
    write_reg8(0x800033, 0x00);  // Disable auto mode.
        
 #endif		 

    adc_set_sampling(ADC_SAMPLING_SYCLE_9, ADC_SAMPLING_RES_8BIT, ADC_SAMPLING_SYCLE_9);
    adc_set_clk_freq(1);	

}

