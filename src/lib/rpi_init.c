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
#include "spi/spi0.h"
#include "system_timer/system_timer.h"
#include "uart/uart.h"

void rpi_init(void)
{
  clearBss();
  gpio_init(&reg_gpio);
  uart_init(&reg_uart);
  system_timer_init(&reg_system_timer);
  spi0_init(&reg_spi0);
  timer_init(&reg_timer);
  interrupt_init(&reg_interrupt);
}
