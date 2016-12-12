/*
 * a350.c
 *
 *  Created on: Mar 18, 2013
 *      Author: Administrator
 */
#include "../tl_common.h"
#include "../drivers/mouse.h"

#if(!APPLICATION_DONGLE)

#if (MOUSE_SENSOR_A350)
#include "mouse_sensor.h"
#include "a350.h"
#define        DLY_200NS    asm("tnop");asm("tnop");asm("tnop");asm("tnop");asm("tnop");asm("tnop")
#define        DLY_100NS    asm("tnop");asm("tnop");asm("tnop");asm("tnop");asm("tnop");asm("tnop");\
                         asm("tnop");asm("tnop");asm("tnop");asm("tnop");asm("tnop");asm("tnop");

/////////  the pin config of the spi //////////////////////

#define        MISO_AS_GPIO        gpio_set_func(GPIO_DI, AS_GPIO)      //gpio_func_set(DI_FUNC,GPIO)
#define        MISO_OE_CLR            gpio_set_output_en(GPIO_DI, 0)        //gpio_oe_clr(DI_FUNC)
#define        MISO_IE_SET            gpio_set_input_en(GPIO_DI, 1)        //gpio_ie_set(DI_FUNC)
#define        MISO_INPUT            gpio_read(GPIO_DI)                    //gpio_input(DI_FUNC)

#define        MOSI_AS_GPIO        gpio_set_func(GPIO_DO, AS_GPIO)      //gpio_func_set(DO_FUNC,GPIO)
#define        MOSI_OE_SET            gpio_set_output_en(GPIO_DO, 1)      //gpio_oe_set(DO_FUNC)
#define        MOSI_IE_CLR            gpio_set_input_en(GPIO_DO, 0)        //gpio_ie_clr(DO_FUNC)
#define        MOSI_OUT_HIGH        gpio_write(GPIO_DO, 1)                //gpio_out_high(DO_FUNC)
#define        MOSI_OUT_LOW        gpio_write(GPIO_DO, 0)                //gpio_out_low(DO_FUNC)

#define        CS_AS_GPIO            gpio_set_func(GPIO_CN, AS_GPIO)        //gpio_func_set(CN_FUNC,GPIO)
#define        CS_OE_SET            gpio_set_input_en(GPIO_CN, 0);   gpio_set_output_en(GPIO_CN, 1)      //gpio_oe_set(GP14)
#define        CS_OUT_HIGH            gpio_write(GPIO_CN, 1)                //gpio_out_high(GP14)
#define        CS_OUT_LOW            gpio_write(GPIO_CN, 0)                //gpio_out_low(GP14)

#define        MSCK_AS_GPIO        gpio_set_func(GPIO_CK, AS_GPIO)        //gpio_func_set(CK_FUNC,GPIO)
#define        MSCK_OE_SET            gpio_set_input_en(GPIO_CK, 0);   gpio_set_output_en(GPIO_CK, 1)      //gpio_oe_set(CK_FUNC)
#define        MSCK_OUT_HIGH        gpio_write(GPIO_CK, 1)                //gpio_out_high(CK_FUNC)
#define        MSCK_OUT_LOW        gpio_write(GPIO_CK, 0)                //gpio_out_low(CK_FUNC)



static void a350_delay(unsigned int us){
    volatile unsigned int i,j;
    volatile unsigned char bc;
    for(i=0;i<us;i++){
        for(j=0;j<30;j++){
            bc++;
        }
    }

}

void   a350_enable(void){
    CS_OUT_HIGH    ;
    CS_OUT_LOW    ;
    a350_delay(15);
    MSCK_OUT_LOW;
    a350_delay(15);
}


void   a350_disable(void){
    a350_delay(15);
    MSCK_OUT_HIGH;
    CS_OUT_HIGH    ;
}


unsigned char spi_sim_read(void){
    unsigned char ii = 0;
    unsigned char dat = 0;
    for(ii=0; ii<8; ii++){
        MSCK_OUT_LOW;
        DLY_100NS;
        MSCK_OUT_HIGH;
        DLY_100NS;
        if(MISO_INPUT){
            dat |= (1<<(7-ii));
        }else{
            dat &= ~(1<<(7-ii));
        }
    }
    return dat;
}

void spi_sim_write( unsigned char data){
    unsigned char ii = 0;
    //unsigned char dat = data | 0x80;
    //CFG_SDAT_OUT;
    for(ii=0; ii<8; ii++){
        MSCK_OUT_LOW;
        if(data&(1<<(7-ii))){
            MOSI_OUT_HIGH;
        }else{
            MOSI_OUT_LOW;
        }
        DLY_100NS;
        MSCK_OUT_HIGH;
        DLY_100NS;
    }
    //CFG_SDAT_IN;
}

unsigned char   a350_read(unsigned char  addr){
    unsigned char value;
    CS_OUT_HIGH    ;
    CS_OUT_LOW    ;
    a350_delay(0);
    MSCK_OUT_LOW;
    a350_delay(0);
    spi_sim_write(addr);
    a350_delay(0);
    a350_delay(0);
    value = spi_sim_read();
    a350_delay(0);

    MSCK_OUT_HIGH;
    CS_OUT_HIGH    ;
    return (value);

}

void   a350_write(unsigned char addr, unsigned char dat){
    CS_OUT_HIGH    ;
    CS_OUT_LOW    ;
    a350_delay(0);
    MSCK_OUT_LOW;
    a350_delay(0);
    spi_sim_write(addr|0x80);
    a350_delay(0);
    spi_sim_write(dat);
    MSCK_OUT_HIGH;
    CS_OUT_HIGH    ;

}

u8 a350_setting[][2] = {
    {0x3a, 0x5a},  /* reset */
    {0x1d, 0x8a},  //event ctl
    {0x1c, 0x04},
    {0x1c, 0x10},
    {0x60, 0x84},        //OFN  engine0
    {0x61, 0x89},        //OFN  engine1
    {0x62, 0x00},
    {0x63, 0x03},
    {0x64, 0x0c},
    {0x65, 0x0a},
    {0x66, 0x14},
    {0x67, 0x12},
    {0x68, 0x18},
    {0x69, 0x16},
    {0x6a, 0x20},
    {0x6b, 0x1e},
    {0x6d, 0xc5},
    {0x6e, 0x3a},
    {0x6f, 0x40},
    {0x70, 0x35},
    {0x71, 0x3b},
    {0x75, 0xba},
    {0x72, 0x99},
    {0x73, 0x02},
    {0x74, 0x00},
    {0x7b, 0x21},
    {0x7e, 0x19},
    {0x7c, 0x50},
    {0x13, 0x20},
    {0x6c, 0x00},
    {0x15, 0x03},  /* set the reset1 to reset2 time :   x * 16 * 20ms */
    {0x16, 0x01},
    {0x17, 0x01}   /* set the reset2 to reset3 time :   x * 128 * 10ms */
};

static void  a350_init(void){
    MISO_AS_GPIO;
    MISO_OE_CLR    ;
    MISO_IE_SET    ;
    //MISO_INPUT;

    MOSI_AS_GPIO;
    MOSI_OE_SET    ;
    MOSI_IE_CLR    ;
    MOSI_OUT_HIGH    ;
    MOSI_OUT_LOW;

    CS_AS_GPIO    ;
    CS_OE_SET    ;
    CS_OUT_HIGH    ;
    //CS_OUT_LOW    ;

    MSCK_AS_GPIO;
    MSCK_OE_SET    ;
    MSCK_OUT_HIGH;
    //MSCK_OUT_LOW;
    a350_write(0x3a,0x5a);  //reset
    a350_delay(300);
    int i;
    for(i = 0; i < sizeof(a350_setting)/sizeof(u16); i++){
        a350_write(a350_setting[i][0], a350_setting[i+1][1]);
    }
}

u32 mouse_sensor_init(void){
    a350_init();
    a350_enable();
    return 0;
}

void mouse_sensor_powerup(void){
    a350_enable();
}

void mouse_sensor_powerdown(void){
    a350_disable();
}

void mouse_sensor_enable(int en){

}

void mouse_drv_enable_6_axis(int en){

}

int mouse_sensor_getxy(mouse_data_t *mouse_data){
    assert(mouse_data);
    mouse_data->x = 0;
    mouse_data->y = 0;
    static u32 last_report_time = 0;
    if(clock_time_exceed(last_report_time, 8000)){
        last_report_time = clock_time();
        char t_x = (char)a350_read(0x03);
        char t_y = (char)a350_read(0x04);
        mouse_data->x = t_x;
        mouse_data->y = t_y;
        return 1;
    }
    return 0;
}

#endif
#endif
