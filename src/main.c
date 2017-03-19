#include "rpi_lib/delay/rpi_delay.h"
#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi.h"

#define SLEEP_MS 1000

int main(void)
{
  rpi_init();

  *GPIO_GPFSEL4 = 0x01 << (3 * 7);

  while (1) {
    static uint32_t count = 0;
    delay(SLEEP_MS);

    if (count) {
      digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);
    } else {
      digitalWrite(GPIO_ACT_PIN, GPIO_LOW);
    }

    count = ~count;
  }

  return 0;
}
