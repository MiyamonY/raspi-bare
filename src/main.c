#include "rpi_lib/delay/rpi_delay.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi.h"

int main(void)
{
  rpi_init();

  *GPIO_GPFSEL4 = 0x01 << (3 * 7);

  while (1) {
    static uint32_t count = 0;
    delay(1000);

    if (count) {
      *GPIO_GPSET1 = 0x01 << 15;
    } else {
      *GPIO_GPCLR1 = 0x01 << 15;
    }

    count = ~count;
  }

  return 0;
}
