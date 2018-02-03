/**
 * File:  rpi_init.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:50:26 2018
 */

#include "bss/rpi_bss.h"
#include "gpio/gpio.h"
#include "reg/reg.h"
#include "rpi.h"
#include "system_timer/system_timer.h"

void rpi_init(void)
{
  clearBss();
  gpio_init(&reg_gpio);
  system_timer_init(&reg_system_timer);
}
