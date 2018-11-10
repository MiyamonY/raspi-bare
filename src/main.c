/**
 * File:  main.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:49:25 2018
 */
#include <stdbool.h>
#include <stdio.h>

#include "lib/rpi.h"

#define ACT_PIN GPIO_PIN47

extern void enable_IRQ(void);
extern void disable_IRQ(void);

/* void set_vector_table(void) */
/* { */
/*   extern void *_inital_vector_start; */
/*   extern void *_inital_vector_end; */

/*   volatile uint32_t *vec = 0; */
/*   volatile uint32_t *s = (uint32_t *)&_inital_vector_start; */
/*   volatile uint32_t *e = (uint32_t *)&_inital_vector_end; */
/*   printf("s %p : 0x%x\n", s, (unsigned int)*s); */
/*   printf("e %p : 0x%x\n", e, (unsigned int)*e); */

/*   for (volatile uint32_t *p = s; p < e; p++) { */
/*     printf("%p : 0x%x\n", vec, (unsigned int)*vec); */
/*     *vec = *p; */
/*     vec++; */
/*   } */
/* } */

void timerIRQ_handler(void)
{
  static bool led = 0;

  if (led) {
    printf("led: on \n");
    gpio_set_output(ACT_PIN, GPIO_OUTPUT_HI);
  } else {
    gpio_set_output(ACT_PIN, GPIO_OUTPUT_LO);
  }
  led = !led;
}

void err_handler(void)
{
  printf("called error\n");
  while (true) {
  }
}

void IRQ_handler(void)
{
  printf("called irq\n");

  disable_IRQ();
  if (interrupt_timer_pending()) {
    timerIRQ_handler();
    timer_irq_clear();
  }
  enable_IRQ();
}

int main(void)
{
  rpi_init();
  interrupt_disable_all();

  gpio_set_mode(ACT_PIN, GPIO_MODE_OUTPUT);
  gpio_set_output(ACT_PIN, GPIO_OUTPUT_HI);

  printf("START PROGRAM\r\n");

  printf("%x\r\n", get_p15_vector());

  timer_stop();
  timer_set_pre_divider(249);
  timer_set_value(4000000 - 1);
  timer_irq_clear();
  timer_interrupt_enable();
  timer_start(REG_TIMER_CONTROL_23BIT_COUNTER);

  interrupt_enable(REG_BASIC_INTERRUPT_ENABLE_TIMER);
  enable_IRQ();

  printf("START MAIN LOOP\r\n");
  while (true) {
    printf("LOOP\r\n");
    printf("%d\r\n", interrupt_timer_pending());
    system_timer_delay_ms(1000);
  }

  return 0;
}
