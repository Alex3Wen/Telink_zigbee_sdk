int no_rc_action;
void   a350_enable(void);
void   a350_disable(void);
unsigned char spi_sim_read(void);
void spi_sim_write( unsigned char data);
unsigned char   a350_read(unsigned char  addr);
void   a350_write(unsigned char addr, unsigned char dat);
