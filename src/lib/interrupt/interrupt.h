/**
 * File:  interrupt.h
 * Author: ymiyamoto
 *
 * Created on Sun Feb 18 04:00:40 2018
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <stdbool.h>

#include "lib/reg/reg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void interrupt_init(reg_interrupt_t *addr);
extern void interrupt_disable_all(void);
extern void interrupt_enable(reg_basic_interrupt_enable_t interrupt);
extern bool interrupt_timer_pending(void);
extern void interrupt_enable_irq(void);
extern void interrupt_disable_irq(void);

#ifdef __cplusplus
}
#endif

#endif /* _INTERRUPT_H_ */
