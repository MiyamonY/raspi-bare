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

  char msg[] = "START PROGRAM\n";
  uart_puts(msg, sizeof(msg));

  while (1) {
    char buf[100];
    size_t len = uart_gets(buf, sizeof(buf));
    uart_puts(buf, len);
  }

  return 0;
}
