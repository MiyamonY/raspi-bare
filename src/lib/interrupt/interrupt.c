/**
 * File:  interrupt.c
 * Author: ymiyamoto
 *
 * Created on Sun Feb 18 04:01:20 2018
 */

#include <stdbool.h>
#include <stdint.h>

#include "lib/reg/reg.h"

static reg_interrupt_t *interrupt_p;

void interrupt_init(reg_interrupt_t *addr)
{
  interrupt_p = addr;
}

void interrupt_disable_all(void)
{
  interrupt_p->DISABLE_IRQS1 = 0xffffffff;
  interrupt_p->DISABLE_IRQS2 = 0xffffffff;
  interrupt_p->DISABLE_BASIC_IRQS = 0xffffffff;
  interrupt_p->FIQ_CONTROL = 0;
}

void interrupt_enable(reg_basic_interrupt_enable_t interrupt)
{
  interrupt_p->ENABLE_BASIC_IRQS |= interrupt;
}

bool interrupt_timer_pending(void)
{
  return (interrupt_p->IRQ_BASIC_PENDING & REG_BASIC_INTERRUPT_PENDING_TIMER) != 0;
}
