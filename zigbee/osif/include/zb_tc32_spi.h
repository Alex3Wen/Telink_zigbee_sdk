/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Declare spi transport for TC32

*/

#ifndef ZB_TC32_SPI_H
#define ZB_TC32_SPI_H 1

/* for SDCC: handler prototype MUST be defined in the same file with main() function */
#define DECLARE_SPI_INTER_HANDLER() \
  void spi_inter_handler(void) INTERRUPT_DEFINITION(SPI_INTER_NUMBER, REGISTER_BANK_2);

#define ZB_SPI_TX_IN_PROGRESS(spi_ctx) ((spi_ctx)->tx_in_progress == 1)

#define ZB_START_SPI_WRITE(io_ctx)                      \
  if (!ZB_SPI_TX_IN_PROGRESS(&(io_ctx)->spi_ctx))       \
  {                                                     \
    ZB_SET_SPI_TRANSMIT_FLAG();                         \
  }

#define ZB_START_SPI_RECEIVE(io_ctx)                    \
  if (!ZB_SPI_TX_IN_PROGRESS(&(io_ctx)->spi_ctx))       \
  {                                                     \
    (io_ctx)->spi_ctx.io_request = ZB_SPI_RX_REQUEST;   \
    ZB_SET_SPI_TRANSMIT_FLAG();                         \
  }

/* spi definitions */
#define ZB_TC32_CKR_VALUE 1
#define ZB_ESPI_BIT    0x01 /* spi interrupt bit 0 */
#define ZB_ENABLE_SPI_INTER() (EIE1 |= ZB_ESPI_BIT)
#define ZB_DISABLE_SPI_INTER() (EIE1 &= ~ZB_ESPI_BIT)

#define ZB_SET_SPI_TRANSMIT_FLAG()   (SPIF = 1)
#define ZB_CLEAR_SPI_TRANSMIT_FLAG() (SPIF = 0)

#define ZB_NO_SPI_IO_REQUEST 0
#define ZB_SPI_RX_REQUEST    1
#define ZB_SPI_TX_REQUEST    2

typedef struct zb_tc32_spi_ctx_s
{
  zb_uint8_t sent_num;         /* number of sent bytes */
  zb_uint8_t tx_in_progress:1; /* flag to show if tx is going or not */
  zb_uint8_t io_request:2;     /* io request type, can be ZB_NO_SPI_IO_REQUEST, ZB_SPI_RX_REQUEST, ZB_SPI_TX_REQUEST
                                  is used to determine if dummy send is needed or not. Dummy send is used during 
                                  spi receive - need to send 1 byte to receive synchronously 1 byte */
  zb_uint8_t reserved:5;
}
zb_tc32_spi_ctx_t;

void zb_spi_init();

#endif /* ZB_TC32_SPI_H */
