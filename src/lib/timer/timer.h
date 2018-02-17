/**
 * File:  timer.h
 * Author: ymiyamoto
 *
 * Created on Sun Feb 18 03:24:45 2018
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>

#include "lib/reg/reg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void timer_init(reg_timer_t *addr);
extern void timer_set_value(uint32_t value);
extern void timer_set_pre_divider(uint32_t pre_divider);
extern void timer_irq_clear(void);
extern void timer_start(reg_timer_control_timer_bits_t len);
extern void timer_stop(void);
extern void timer_interrupt_enable(void);
extern void timer_interrupt_disable(void);

#ifdef __cplusplus
}
#endif

#endif /* _TIMER_H_ */
