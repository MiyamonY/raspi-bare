#include "rpi_lib/rpi.h"

#define GPFSEL0 0x3F200000
#define GPFSEL1 0x3F200004
#define GPFSEL2 0x3F200008
#define GPFSEL4 0x3F200010
#define GPSET0 0x3F20001C
#define GPSET1 0x3F200020
#define GPCLR0 0x3F200028
#define GPCLR1 0x3F20002C

void main(void)
{
  rpi_init();

  *(volatile unsigned int *)GPFSEL4 = 0x01 << (3 * 7);
  *(volatile unsigned int *)GPSET1 = 0x01 << 15;

  while (1)
    ;

  return;
}
