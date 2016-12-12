/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: TC32-specific platform depenedent stuff
*/

#ifndef ZB_OSIF_TC32_H
#define ZB_OSIF_TC32_H 1

/*! \addtogroup ZB_OSIF_TC32 */
/*! @{ */

//#include <stdio.h>
//#include <limits.h>
#include "../../../proj/tl_common.h"
#include "../../../proj/common/string.h"
#include "../../../proj/common/types.h"
#include "../../../proj/common/assert.h"
#include "../../../proj/mcu/clock.h"
#include "../../../proj/mcu/watchdog_i.h"
#include "../../../proj/mcu/irq_i.h"


#define ZB_VOLATILE volatile

#define ZB_INTERRUPT void

#define ES IE_bit.ES0
#define TI SCON0_bit.TI0
#define RI SCON0_bit.RI0
#define SBUF SBUF0
#define PS IP_bit.PS0
#define SCON SCON0
#define NSSMD0 SPI0CN_bit.NSSMD0
#define NSSMD1 SPI0CN_bit.NSSMD1
#define SPIEN SPI0CN_bit.SPIEN
#define TR0 TCON_bit.TR0
#define EA IE_bit.EA
#define IT1 TCON_bit.IT1
#define PX1 IP_bit.PX1
#define EX1 IE_bit.EX1
#define ET0 IE_bit.ET0
#define ET1 IE_bit.ET1
#define TR1 TCON_bit.TR1
#define SPIF SPI0CN_bit.SPIF
#define WCOL SPI0CN_bit.WCOL
#define RXOVRN SPI0CN_bit.RXOVRN

#define LED1 P3_bit.P30
#define LED2 P3_bit.P31

#define CONFIG_PAGE       0x0F    /* SYSTEM AND PORT CONFIGURATION PAGE */
#define LEGACY_PAGE       0x00    /* LEGACY SFR PAGE */




#define ZB_ABORT() { zb_char_t *p = 0; *p = 0; }


#define ZB_SDCC_BANKED
#define ZB_SDCC_XDATA


#define ZB_TRACE_LOCK()
#define ZB_TRACE_UNLOCK()

#define ZB_CONFIG_PAGE 0
#define ZB_VOLATILE_PAGE 128
#define ZB_SCRATCHPAD_PAGE_SIZE 128



/**
   Put 8051 into idle state.

   Wnen not do it, at Keil simulator works much faster! It could be useful to
   disable idle when debug (bit not sure...)
   Use ZB_DBG_NO_IDLE define to disable idle.
 */

#define ZB_FORCE_IDLE() (PCON |= 0x01, PCON = PCON)


/**
   Put 8051 into idle state, interrupt will wakeup it.
 */
#define ZB_GO_IDLE()  ev_main()
#define CHECK_INT_N_TIMER()
/**
   Complilers stuff
 */

  #define INTERRUPT_DEFINITION(x, y)



#define INTERRUPT_DECLARATION(x, y)
#define INTERRUPT_DECLARATION_NOBANK(x)



#define DECLARE_REGISTER_AT(type, var, val) type var = val


#define ZB_OSIF_GLOBAL_LOCK()   ZB_DISABLE_ALL_INTER()
#define ZB_OSIF_GLOBAL_UNLOCK() ZB_ENABLE_ALL_INTER()

#define ZB_TEST_BIT(B) ((B) ? (B = 0, 1) : 0)

#define REGISTER_BANK_1     1
#define REGISTER_BANK_2     2
#define REGISTER_BANK_3     3


#define SERIAL_INTER_NUMBER 4
#define TIMER0_INTER_NUMBER 1   // PS TBD


#define ZB_DISABLE_TC32()  //EX1 = 0, EX1 = 0
#define ZB_ENABLE_TC32() //EX1 = 1


extern u8 irqS;
#define ZB_ENABLE_ALL_INTER() (irq_enable())
#define ZB_DISABLE_ALL_INTER() (irqS = irq_disable())


#define ZB_DISABLE_TRANSIVER_INT() ZB_DISABLE_TC32()
#define ZB_ENABLE_TRANSIVER_INT() ZB_ENABLE_TC32()

#define ZB_POWER_SOWN()   // PS TDB (PCON |= 2, PCON = PCON)


// Common XTAL frequencies (Hz).
#define ZB_SHORT_XTAL_11_059MHZ  11.059200
#define ZB_SHORT_XTAL_12_000MHZ  12.000000
#define ZB_SHORT_XTAL_12_288MHZ  12.288000
#define ZB_SHORT_XTAL_16_000MHZ  16.000000
#define ZB_SHORT_XTAL_20_000MHZ  20.000000
#define ZB_SHORT_XTAL_22_118MHZ  22.118400
#define ZB_SHORT_XTAL_24_000MHZ  24.000000
#define ZB_SHORT_XTAL_24_500MHZ  24.500000
#define ZB_SHORT_XTAL_32_000MHZ  32.000000

#define ZB_SHORT_XTAL_FREQ ZB_SHORT_XTAL_24_500MHZ /* TODO: define it depending on ZB_XTAL_FREQ value */

#define ZB_STOP_WATCHDOG() \
(                          \
  wd_stop();               \
)

//#define ZB_START_DEVICE() ZB_TIMER_INIT(), ZB_ENABLE_ALL_INTER()
#define ZB_START_DEVICE()  ZB_ENABLE_ALL_INTER()

/**
   Return random value

   TODO: implement it!
 */
zb_uint16_t zb_random();
#define ZB_RANDOM() zb_random()

/* use macros to be able to redefine */
#define ZB_MEMCPY memcpy
#define ZB_MEMMOVE memcpy
#define ZB_MEMSET memset
#define ZB_MEMCMP memcmp

void zb_bzero_short(char *s, zb_uint8_t n);
#define ZB_BZERO(s,l) zb_bzero_short((char*)(s), (l))
#define ZB_BZERO2(s) ZB_BZERO(s, 2)

#define ZB_CODE_MEM ((zb_uint8_t code *)0x00)
#define ZB_XDATA_MEM ((zb_uint8_t xdata *)0x00)


/* for SDCC: handler prototype MUST be defined in the same file with main() function */
#define DECLARE_UBEC_2400_INTER_HANDLER() \
  void ubec_2400_handler(void) INTERRUPT_DEFINITION(UBEC_2400_INTER_NUMBER, REGISTER_BANK_0);

#define ZVUNUSED(v) (void)v

/* nvram functions */
/* dummy
typedef zb_uint8_t zb_node_desc_t[15];
typedef zb_uint8_t zb_power_desc_t[2];
typedef zb_uint8_t zb_simple_desc_t[12];
*/

zb_ret_t zb_write_nvram_config(zb_uint8_t aps_designated_coord, zb_uint8_t aps_use_insecure_join, zb_uint8_t aps_use_extended_pan_id,
    zb_ieee_addr_t mac_extended_address);

zb_ret_t zb_config_from_nvram();

void zb_erase_nvram(zb_uint8_t page);

zb_ret_t zb_write_formdesc_data(zb_uint8_t profile_in_use, zb_ieee_addr_t long_parent_addr, zb_uint32_t aps_channel_mask,
zb_uint16_t short_parent_addr, zb_uint8_t     depth, zb_uint16_t pan_id, zb_ext_pan_id_t ext_pan_id, zb_uint16_t nwk_short_addr);

zb_ret_t zb_read_formdesc_data();


zb_ret_t zb_write_security_key();

zb_ret_t zb_read_security_key();

zb_ret_t zb_write_up_counter();

zb_ret_t zb_read_up_counter();

/* config section (for nvram routines */
#define ZB_CONFIG_SIZE 9

/**
   Configure device to issue UZ2400 interrupt
 */

void zb_ext_int_init(); /* external interrupt init */
void zb_xram_init(); /*off-chip xram initialization */


/*! @} */

#endif /* ZB_OSIF_TC32_H */
