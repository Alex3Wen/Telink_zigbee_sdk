/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Declare serial transport for TC32

*/

#ifndef ZB_TC32_SERIAL_H
#define ZB_TC32_SERIAL_H 1

/*! \addtogroup ZB_OSIF_TC32 */
/*! @{ */


#define ZB_SERIAL_BAUD_RATE BAUD_RATE_115200

/* for SDCC: handler prototype MUST be defined in the same file with main() function */
#define DECLARE_SERIAL_INTER_HANDLER() \
  void serial_inter_handler(void) INTERRUPT_DEFINITION(SERIAL_INTER_NUMBER, REGISTER_BANK_1);

#define ZB_SERIAL_TX_IN_PROGRESS(serial_ctx) ((serial_ctx)->tx_in_progress == 1)

#define ZB_START_SERIAL_WRITE(io_ctx)                   \
  if (!ZB_SERIAL_TX_IN_PROGRESS(&(io_ctx)->serial_ctx)) \
  {                                                     \
    ZB_SET_SERIAL_TRANSMIT_FLAG();                      \
  }

#ifdef ZB_CC25XX
#define ZB_ENABLE_SERIAL_INTER() (IEN2 |= 0x04, IEN0 |= 0x80)
#define ZB_DISABLE_SERIAL_INTER() (IEN2 &=~0x04 )

#define ZB_SET_SERIAL_TRANSMIT_FLAG()   (UTX0IF = 1)
#define ZB_CLEAR_SERIAL_TRANSMIT_FLAG() (UTX0IF = 0)

#define ZB_SERIAL_TRANSMIT_FLAG     UTX0IF

#define SBUF U0DBUF

#else


#define ZB_ENABLE_SERIAL_INTER() (ES = 1)
#define ZB_DISABLE_SERIAL_INTER() (ES = 0)

#define ZB_SET_SERIAL_TRANSMIT_FLAG()   (TI = 1)
#define ZB_CLEAR_SERIAL_TRANSMIT_FLAG() (TI = 0)

#define ZB_SET_SERIAL_RECV_FLAG()   (RI = 1)
#define ZB_CLEAR_SERIAL_RECV_FLAG() (RI = 0)

#define ZB_SERIAL_RECV_FLAG     RI
#define ZB_SERIAL_TRANSMIT_FLAG TI

#define PCON_SMOD           0x80
#define TMOD_GATE_T1        0x80
#define TMOD_C_T_T1         0x40
#define TMOD_M1_T1          0x20
#define TMOD_M0_T1          0x10
#define T1_MODE_MASK        (TMOD_GATE_T1 | TMOD_C_T_T1 | TMOD_M1_T1 | TMOD_M0_T1)
#define T1_8BIT_AUTO_RELOAD (TMOD_M1_T1)

#define SCON_8N1            0x40
#define SCON_REN            0x10
#endif

typedef enum zb_serial_baud_rate_e
{
  BAUD_RATE_1200,
  BAUD_RATE_2400,
  BAUD_RATE_9600,
  BAUD_RATE_19200,
  BAUD_RATE_38400,
  BAUD_RATE_57600,
  BAUD_RATE_115200,
  NUM_BAUD_RATES
}
zb_serial_baud_rate_t;

ZB_RING_BUFFER_DECLARE(serial_iobuf, zb_uint8_t, 4);

typedef struct zb_tc32_serial_ctx_s
{
  zb_uint8_t tx_in_progress; /* if set, we are waiting for tx complete int */
#ifdef ZB_TRANSPORT_TC32_DATA_UART
  serial_iobuf_t rx_buf;
#endif
  serial_iobuf_t tx_buf;
}
zb_tc32_serial_ctx_t;

void zb_init_tc32_serial();

void zb_TC32_serial_put_bytes(zb_uint8_t *buf, zb_short_t len);

zb_ushort_t zb_tc32_serial_get_bytes(zb_uint8_t *buf, zb_ushort_t size);

zb_ret_t zb_tc32_serial_try_recv();

void zb_putchar(char c);

#ifdef ZB_TRANSPORT_TC32_DATA_UART
#define ZB_TRY_IO() zb_tc32_serial_try_recv()
#else
#define ZB_TRY_IO() RET_BLOCKED
#endif

/*! @} */

#endif /* ZB_TC32_SERIAL_H */

