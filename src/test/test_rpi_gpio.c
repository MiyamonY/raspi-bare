/**
 * File:  test_rpi_gpio.c
 * Author: ymiyamoto
 *
 * Created on Sat Apr 29 12:27:11 2017
 */

#include <criterion/criterion.h>

#include "rpi_lib/gpio/rpi_gpio.h"

Test(rpi_gpio, PinModeCheck)
{
  pinMode(0, GPIO_MODE_INPUT);
}
