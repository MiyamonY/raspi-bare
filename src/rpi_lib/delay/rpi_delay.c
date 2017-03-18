/**
 * File:  rpi_delay.c
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:28:58 2017
 */

#include "rpi_delay.h"
#include "rpi_lib/rpi_types.h"
#include "rpi_lib/timer/rpi_timer.h"

void delay(uint32_t ms)
{
  delayMicroseconds(ms * 1000);
}

void delayMicroseconds(uint32_t us)
{
  uint64_t tend = micros() + us;
  while (micros() < tend)
    ;

  return;
}
