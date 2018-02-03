/**
 * File:  reg.c
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 21:12:13 2018
 */
#include "reg.h"

gpio_addr_t gpio_addr __attribute__((section(".peripheral_gpio")));
system_timer_addr_t system_timer_addr __attribute__((section(".peripheral_system_timer")));
