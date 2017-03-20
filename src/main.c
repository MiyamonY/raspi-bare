#include "rpi_lib/delay/rpi_delay.h"
#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/rpi.h"
#include "rpi_lib/serial/rpi_serial.h"

#define SLEEP_MS 1000
#define UART_BAURATE 115200

int main(void)
{
  rpi_init();

  pinMode(GPIO_ACT_PIN, GPIO_MODE_OUTPUT);
  digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);

  Serial_begin(UART_BAURATE);

  int8_t hello[] = "Hellow World!\r\n";
  int8_t hoge[] = "hogehoge\r\n";
  uart0_putc('a');
  uart0_puts(hello);
  Serial_write(hoge, sizeof(hoge));
  uart0_puts(hello);

  while (1) {
    int8_t buf[128];
    uart0_gets(buf, 128);
    uart0_puts(buf);
  }

  return 0;
}
