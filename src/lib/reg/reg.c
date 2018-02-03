/**
 * File:  reg.c
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 21:12:13 2018
 */
#include "reg.h"

reg_gpio_t reg_gpio __attribute__((section(".peripheral_gpio")));
reg_system_timer_t reg_system_timer __attribute__((section(".peripheral_system_timer")));
