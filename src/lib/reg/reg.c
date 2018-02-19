/**
 * File:  reg.c
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 21:12:13 2018
 */
#include "reg.h"

reg_gpio_t reg_gpio __attribute__((section(".peripheral_gpio")));
reg_system_timer_t reg_system_timer __attribute__((section(".peripheral_system_timer")));
reg_uart_t reg_uart __attribute__((section(".peripheral_uart")));
reg_spi0_t reg_spi0 __attribute__((section(".peripheral_spi0")));
reg_timer_t reg_timer __attribute__((section(".peripheral.timer")));
reg_interrupt_t reg_interrupt __attribute__((section(".peripheral.interrupt")));
