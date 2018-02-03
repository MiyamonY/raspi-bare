/**
 * File:  system_timer.c
 * Author: ymiyamoto
 *
 * Created on Sun Feb  4 03:08:56 2018
 */

#include "system_timer.h"
#include "lib/types.h"

typedef uint64_t system_timer_us_t;

static system_timer_addr_t *system_timer_addr;

static inline system_timer_us_t to_us(system_timer_ms_t ms)
{
  return ms * 1000;
}

void system_timer_init(system_timer_addr_t *addr)
{
  system_timer_addr = addr;
}

uint64_t system_timer_get_time(void)
{
  uint64_t chi = (uint64_t)system_timer_addr->CHI;
  uint64_t clo = (uint64_t)system_timer_addr->CLO;

  if (chi != system_timer_addr->CHI) {
    chi = (uint64_t)system_timer_addr->CHI;
    clo = (uint64_t)system_timer_addr->CLO;
  }

  return (chi << 32) | clo;
}

void system_timer_delay_ms(system_timer_ms_t ms)
{
  uint64_t expire = system_timer_get_time() + to_us(ms);
  while (system_timer_get_time() <= expire) {
  }
}
