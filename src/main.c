#include "rpi_lib/delay/rpi_delay.h"
#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/rpi.h"
#include "rpi_lib/serial/rpi_serial.h"
#include <stdio.h>

#define SLEEP_MS 1000
#define UART_BAURATE 115200

int main(void)
{
  rpi_init();

  pinMode(GPIO_ACT_PIN, GPIO_MODE_OUTPUT);
  digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);
  Serial_begin(UART_BAURATE);

  printf("PROGRAM START\n");

  while (1) {
    char str[256];
    uint64_t t = micros();
    sprintf(str, "sysclock %lld (us)\n", t);
    printf("%s", str);
    delay(SLEEP_MS);
  }

  return 0;
}
