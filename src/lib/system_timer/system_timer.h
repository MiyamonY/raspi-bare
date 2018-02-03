/**
 * File:  system_timer.h
 * Author: ymiyamoto
 *
 * Created on Sun Feb  4 03:06:19 2018
 */

#ifndef _SYSTEM_TIMER_H_
#define _SYSTEM_TIMER_H_

#include "lib/reg/reg.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
  reg_t CS;
  reg_t CLO;
  reg_t CHI;
} system_timer_addr_t;

typedef uint64_t system_timer_ms_t;

extern void system_timer_init(system_timer_addr_t *addr);
extern uint64_t system_timer_get_time(void);
extern void system_timer_delay_ms(system_timer_ms_t ms);

#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_TIMER_H_ */
