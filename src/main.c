#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi.h"

uint64_t get_system(void)
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

void delay_ms(uint32_t delay)
{
  uint64_t alertTime = get_system() + delay * 1000;

  while (get_system() < alertTime)
    ;

  return;
}

int main(void)
{
  rpi_init();

  *SYST_CHI = 0;
  *SYST_CLO = 0;
  *GPIO_GPFSEL4 = 0x01 << (3 * 7);

  while (1) {
    static uint32_t count = 0;
    delay_ms(1000);

    if (count) {
      *GPIO_GPSET1 = 0x01 << 15;
    } else {
      *GPIO_GPCLR1 = 0x01 << 15;
    }

    count = ~count;
  }

  return 0;
}
