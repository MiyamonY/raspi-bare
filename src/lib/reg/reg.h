/**
 * File:  reg.h
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 21:21:30 2018
 */

#ifndef _REG_H_
#define _REG_H_

#include "lib/gpio/gpio.h"
#include "lib/system_timer/system_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

extern gpio_addr_t gpio_addr;
extern system_timer_addr_t system_timer_addr;

#ifdef __cplusplus
}
#endif

#endif /* _REG_H_ */
