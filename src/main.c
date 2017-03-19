#include "rpi_lib/delay/rpi_delay.h"
#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi.h"

#define SLEEP_MS 1000

#define UART0_BASE (0x201000)
#define UART0_DR PHY_PERI_ADDR(UART0_BASE + 0x00)
#define UART0_IBRD PHY_PERI_ADDR(UART0_BASE + 0x24)
#define UART0_FBRD PHY_PERI_ADDR(UART0_BASE + 0x28)
#define UART0_LCRH PHY_PERI_ADDR(UART0_BASE + 0x2c)
#define UART0_CR PHY_PERI_ADDR(UART0_BASE + 0x30)

int main(void)
{
  rpi_init();

  *UART0_CR = 0x0000;
  pinMode(14, GPIO_MODE_INPUT_PULL_DOWN);
  pinMode(15, GPIO_MODE_INPUT_PULL_DOWN);
  pinMode(14, GPIO_MODE_ALT0);
  pinMode(15, GPIO_MODE_ALT0);

  *UART0_IBRD = 1;
  *UART0_FBRD = 40;

  *UART0_LCRH = 0x70;
  *UART0_CR = 0x0301;

  pinMode(GPIO_ACT_PIN, GPIO_MODE_OUTPUT);
  digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);

  while (1) {
    static uint32_t count = 0;
    delay(SLEEP_MS);
    *UART0_DR = (0x000000ff & 'a');

    if (count) {
      digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);
    } else {
      digitalWrite(GPIO_ACT_PIN, GPIO_LOW);
    }

    count = ~count;
  }

  return 0;
}
