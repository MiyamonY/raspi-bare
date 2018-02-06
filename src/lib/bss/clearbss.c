/**
 * File:  clearbssl.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:47:00 2018
 */
#include <stdint.h>

void clearBss(void)
{
  extern void *__bss_start;
  extern void *__bss_end;

  uint32_t *start = (uint32_t *)&__bss_start;
  uint32_t *end = (uint32_t *)&__bss_end;
  for (uint32_t *p = start; p < end; p++) {
    *p = 0x00;
  }
}
