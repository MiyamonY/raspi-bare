/**
 * File:  rpi_serial.c
 * Author: ymiyamoto
 *
 * Created on Mon Mar 20 10:06:43 2017
 */

#include "rpi_serial.h"
#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi_types.h"
#include "rpi_lib/timer/rpi_timer.h"

#define F_UARTCLK 3000000

static int32_t SerialReadTimeOutMs = -1;
static int32_t SerialWriteTimeOutMs = -1;

static inline uint32_t calc_baurate_integer(uint32_t baurate)
{
  return F_UARTCLK / baurate;
}

static inline uint32_t calc_baurate_fractional(uint32_t baurate)
{
  uint32_t i = calc_baurate_integer(baurate);
  return (((((uint64_t)F_UARTCLK * 1000) / baurate) - i * 1000) * 64 + (0.5 * 1000)) / 1000;
}

int32_t Serial_begin(uint32_t baurate)
{
  *UART0_CR = 0x0000;

  pinMode(GPIO_UART0_TX_PIN, GPIO_MODE_INPUT_PULL_DOWN);
  pinMode(GPIO_UART0_RX_PIN, GPIO_MODE_INPUT_PULL_DOWN);
  pinMode(GPIO_UART0_TX_PIN, GPIO_MODE_ALT0);
  pinMode(GPIO_UART0_RX_PIN, GPIO_MODE_ALT0);

  /* baurate */
  uint32_t i = calc_baurate_integer(baurate);
  if ((i < 1) || (0xffff < i)) return -1;

  uint32_t f = calc_baurate_fractional(baurate);

  *UART0_IBRD = 1;
  *UART0_FBRD = 40;

  /* 8bit, fifo eanble */
  *UART0_LCRH = 0x70;

  /* receive/transmit enable, uart enable */
  *UART0_CR = 0x0301;

  return 0;
}

void Serial_end(void)
{
  *UART0_CR = 0x0000;
  return;
}

int32_t Serial_available(void)
{
  return !(*UART0_FR & (0x01 << 4));
}

int32_t Serial_write(int8_t *buf, uint32_t len)
{
  for (uint32_t i = 0; i < len; i++) {
    int32_t ret = uart0_putc(buf[i]);
    if (ret == -1) return i;
  }

  return len;
}

int32_t Serial_read(void)
{
  return uart0_getc();
}

void setSerialTimeout(int32_t read_ms, int32_t write_ms)
{
  SerialReadTimeOutMs = read_ms;
  SerialWriteTimeOutMs = write_ms;
  return;
}

int32_t uart0_getc(void)
{
  uint64_t start = millis();

  while ((SerialReadTimeOutMs < 0) || (millis() < start + SerialReadTimeOutMs)) {
    if (!((*UART0_FR) & (1 << 4))) {
      return (*UART0_DR & 0x000000ff);
    }
  }

  return -1;
}

int32_t uart0_putc(int32_t c)
{
  uint64_t start = millis();
  *UART0_DR = c & 0x000000ff;

  while ((SerialWriteTimeOutMs < 0) || (millis() < start + SerialWriteTimeOutMs)) {
    if ((*UART0_FR) & (1 << 7)) {
      return 1;
    }
  }

  return -1;
}

uint32_t uart0_puts(int8_t *s)
{
  uint32_t count = 0;
  do {
    if (uart0_putc(s[count]) == -1) return count;
    count++;
  } while ((s[count - 1] != '\0') && (s[count - 1] != '\n'));

  return count;
}

int8_t *uart0_gets(int8_t *s, uint32_t len)
{
  for (uint32_t i = 0; i < (len - 1); i++) {
    int32_t ret = uart0_getc();
    if (ret == -1) {
      return (void *)0;
    } else if (ret == '\0') {
      s[i] = '\0';
      return s;
    } else {
      s[i] = ret;
    }
  }

  s[len - 1] = '\0';
  return s;
}
