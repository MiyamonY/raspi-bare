/**
 * File:  main.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:49:25 2018
 */

#include "lib/rpi.h"
#include <stdio.h>

static void timerIRQ_handler(void)
{
  static bool led = 0;

  if (led) {
    printf("led: on\r\n");
    gpio_set_output(ACT_PIN, GPIO_OUTPUT_HI);
  } else {
    printf("led: off\r\n");
    gpio_set_output(ACT_PIN, GPIO_OUTPUT_LO);
  }
  led = !led;
}

void interrupt_irq_callback(void){
  if (interrupt_timer_pending()) {
    timerIRQ_handler();
    timer_irq_clear();
  }
}

int main(void)
{
  rpi_init();

  interrupt_disable_all();
  gpio_set_output(ACT_PIN, GPIO_OUTPUT_HI);

  printf("START PROGRAM\r\n");
  timer_stop();
  timer_set_pre_divider(249);
  timer_set_value(1000000 - 1);
  timer_irq_clear();
  timer_interrupt_enable();
  timer_start(REG_TIMER_CONTROL_23BIT_COUNTER);

  interrupt_enable(REG_BASIC_INTERRUPT_ENABLE_TIMER);
  interrupt_enable_irq();

  while (true) {
  }

  return 0;
}
