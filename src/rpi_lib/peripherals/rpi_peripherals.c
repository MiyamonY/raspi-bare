/**
 * File:  rpi_peripherals.c
 * Author: ymiyamoto
 *
 * Created on Thu May  4 13:24:23 2017
 */

#include <stdint.h>

#include "rpi_peripherals.h"

rpi_peripheral_gpio_t GPIO __attribute__((section(".peripheral_gpio")));
