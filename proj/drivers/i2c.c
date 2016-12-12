
#include "../tl_common.h"
#include "../mcu/clock.h"
#include "i2c.h"

#ifndef PIN_I2C_CN
#define PIN_I2C_CN				GPIO_CN
#endif
#ifndef PIN_I2C_SCL
#define PIN_I2C_SCL				GPIO_CK
#endif
#ifndef PIN_I2C_SDA
#define PIN_I2C_SDA				GPIO_DI
#endif

static inline void i2c_wait(void){
}
void i2c_long_wait(void){
	CLOCK_DLY_600NS;
}

// Pulling the line to ground is considered a logical zero while letting the line float is a logical one.   http://en.wikipedia.org/wiki/I%C2%B2C
static inline void i2c_scl_out(int v){
	gpio_set_output_en(PIN_I2C_SCL, (!v));
}

static inline int i2c_scl_in(void){
	return gpio_read(PIN_I2C_SCL);
}

// Pulling the line to ground is considered a logical zero while letting the line float is a logical one.   http://en.wikipedia.org/wiki/I%C2%B2C
static inline void i2c_sda_out(int v){
	gpio_set_output_en(PIN_I2C_SDA, (!v));
}

static inline int i2c_sda_in(void){
	return gpio_read(PIN_I2C_SDA);
}

static inline void i2c_scl_init(void){
	gpio_set_func(PIN_I2C_SCL, AS_GPIO); 
}

static inline void i2c_sda_init(void){
	gpio_set_func(PIN_I2C_SDA, AS_GPIO); 
	gpio_set_input_en(PIN_I2C_SDA, 1);
}

static inline void i2c_scl_idle(void){
	gpio_set_output_en(PIN_I2C_SCL, 0); 
	gpio_write(PIN_I2C_SCL, 0);
}

static inline void i2c_sda_idle(void){
	gpio_set_output_en(PIN_I2C_SDA, 0); 
	gpio_write(PIN_I2C_SDA, 0);
}

void i2c_init(){
	gpio_write(PIN_I2C_CN, 1);
	gpio_write(PIN_I2C_SDA, 1);
}

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\ void i2c_start(void)
\\   Sets clock high, then data high.  This will do a stop if data was low.
\\   Then sets data low, which should be a start condition.
\\   After executing, data is left low, while clock is left high
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void i2c_start(void)
{
	i2c_scl_init();	
	i2c_sda_init();	
	i2c_sda_idle();	
	i2c_scl_idle();		
	i2c_sda_out(1);		//sda: 1
	i2c_scl_out(1);		//scl: 1
	i2c_sda_out(0);		//sda: 0
	i2c_wait();

}

/*
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
\\ void i2c_stop(void)    
\\  puts data low, then clock low,
\\  then clock high, then data high.
\\  This should cause a stop, which
\\  should idle the bus, I.E. both clk and data are high.
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void i2c_stop(void)
{
	i2c_sda_out(0);
	i2c_wait();
	i2c_scl_out(0);
	i2c_wait();
	i2c_scl_out(1);
	i2c_wait();
	i2c_sda_out(1);
}

static void i2c_wirte_bit (int bit)
{
	i2c_scl_out(0);
	i2c_sda_out(bit);
	i2c_long_wait();
	i2c_scl_out(1);
}

// Read a bit from I2C bus
static int i2c_read_bit(void) {
	i2c_wirte_bit(1);
	return i2c_sda_in();
}

int i2c_write_byte(u8 dat){
	int i = 0x80;
	while(i){
		i2c_wirte_bit((dat & i));
		i = i >> 1;
	}
	return i2c_read_bit();
}

u8 i2c_read_byte(int last){
	u8 dat = 0;
	foreach(i, 8){
		i2c_wirte_bit(1);
		if(i2c_sda_in()){
			dat = (dat << 1) | 0x01;
		}else{
			dat = dat << 1;
		}
	}
	i2c_wirte_bit(last);
	return dat;
}

void i2c_write(u8 id, u8 addr, u8 dat)
{
	i2c_start();
	i2c_write_byte(id);
	i2c_write_byte(addr);
	i2c_write_byte(dat);
	i2c_stop();
}

u8 i2c_read(u8 id, u8 addr)
{
	u8 dat;
	i2c_burst_read (id, addr, &dat, 1);
	return dat;
}

void i2c_burst_read(u8 id, u8 addr,u8 *p,u8 n)
{
	i2c_start();

	i2c_write_byte (id);
	i2c_write_byte (addr);
	i2c_sda_out(1);
	i2c_scl_out(0);
	i2c_long_wait();
	i2c_scl_out(1);
	i2c_sda_out(0);
	
	i2c_write_byte (id | 1);

	for (int k = 0; k < n; ++k) {
		*p++ = i2c_read_byte( k == (n-1) );
	}
	i2c_stop();
	
}


