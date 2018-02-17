/**
 * File:  timer.c
 * Author: ymiyamoto
 *
 * Created on Sun Feb 18 03:24:40 2018
 */

#include <stdbool.h>
#include <stdint.h>

#include "lib/reg/reg.h"

static reg_timer_t *timer_p;

void timer_init(reg_timer_t *addr)
{
  timer_p = addr;
}

void timer_set_value(uint32_t value)
{
  timer_p->LOAD = value;
  timer_p->RELOAD = value;
}

void timer_set_pre_divider(uint32_t pre_divider)
{
  timer_p->PREDIVIDER = pre_divider;
}

void timer_irq_clear(void)
{
  timer_p->IRQ = 0;
}

void timer_stop(void)
{
  timer_p->CONTROL &= 0xffffff00;
}

void timer_start(reg_timer_control_timer_bits_t len)
{
  timer_p->CONTROL |= (REG_TIMER_CONTROL_TIMER_ENABLE | len);
}

void timer_interrupt_enable(void)
{
  timer_p->CONTROL |= REG_TIMER_CONTROL_INTERRUPT_ENABLE;
}

void timer_interrupt_disable(void)
{
  timer_p->CONTROL &= ~REG_TIMER_CONTROL_INTERRUPT_ENABLE;
}
