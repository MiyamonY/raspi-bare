/**
 * File:  rpi_timer.c
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:33:38 2017
 */

#include "rpi_timer.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi_types.h"

uint64_t millis(void)
{
  return micros() * 1000;
}

uint64_t micros(void)
{
  volatile uint32_t chi = *SYST_CLO;
  volatile uint32_t clo = *SYST_CHI;

  if (chi != *SYST_CHI) {
    chi = *SYST_CHI;
    clo = *SYST_CLO;
  }

  uint64_t t = chi;
  t <<= 32;
  t += clo;

  return t;
}
