/**
 * File:  main.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:49:25 2018
 */
#include <stdbool.h>
#include <stdio.h>

#include "lib/devices/ADT7310/ADT7310.h"
#include "lib/rpi.h"

#define ACT_PIN GPIO_PIN47

int main(void)
{
  rpi_init();

  gpio_set_mode(ACT_PIN, GPIO_MODE_OUTPUT);
  gpio_set_output(ACT_PIN, GPIO_OUTPUT_HI);

  ADT7310_init();
  ADT7310_configure(ATD7310_16BIT, ATD7310_MODE_CONTINUOUS, false);

  printf("START PROGRAM\n");

  while (true) {
    double tmp = ADT7310_temperature();
    printf("tmp is %f\n", tmp);

    system_timer_delay_ms(1000);
  }

  return 0;
}
