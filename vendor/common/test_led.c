
#include "../../proj/tl_common.h"
#include "test_led.h"


int zb_led_blink(void* arg)
{
  static u8 count = 1;
  gpio_write(HEART_BEAT_LED, count%2);
  count++;
  return 0;
}


static ev_time_event_t zbLedTimer;
void zb_led_init(void)
{
    
  zbLedTimer.cb = zb_led_blink;
  ev_on_timer(&zbLedTimer, 1000*1000*3);

  /* Enable Node Heart Beat LED */
  gpio_set_func(HEART_BEAT_LED, AS_GPIO);
  gpio_set_output_en(HEART_BEAT_LED, 1);

  /* Enable link LED */
  gpio_set_func(COMMISSIONING_LED, AS_GPIO);
  gpio_set_output_en(COMMISSIONING_LED, 1);
}

