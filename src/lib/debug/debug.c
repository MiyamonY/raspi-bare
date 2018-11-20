/**
 * File:  debug.c
 * Author: ymiyamoto
 *
 * Created on Tue Nov 20 09:45:20 2018
 */

#include <stdbool.h>
#include <stdint.h>
#include "lib/gpio/gpio.h"

void debug_init_jtag(void){
  gpio_set_mode(TRST_PIN, GPIO_MODE_ALT4);
  gpio_set_mode(RTCK_PIN, GPIO_MODE_ALT4);
  gpio_set_mode(TDO_PIN, GPIO_MODE_ALT4);
  gpio_set_mode(TCK_PIN, GPIO_MODE_ALT4);
  gpio_set_mode(TDI_PIN, GPIO_MODE_ALT4);
  gpio_set_mode(TMS_PIN, GPIO_MODE_ALT4);
}
