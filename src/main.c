/**
 * File:  main.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:49:25 2018
 */

#include "lib/rpi.h"

#define ACT_PIN GPIO_PIN47

int main(void)
{
  rpi_init();

  gpio_set_mode(ACT_PIN, GPIO_MODE_OUTPUT);
  gpio_set_output(ACT_PIN, GPIO_OUTPUT_HI);

  while (1) {
    uart_putc('a');
    system_timer_delay_ms(1000);
  }

  return 0;
}
