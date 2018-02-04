/**
 * File:  uart.c
 * Author: ymiyamoto
 *
 * Created on Sun Feb  4 12:51:36 2018
 */

#include "uart.h"
#include "lib/gpio/gpio.h"
#include "lib/types.h"

#define UART_CLOCK (uint64_t)(3000000ull)
#define FRAC_CALC_COEF 10000
#define UART_CLOCK_MUL 16
#define UART_CLOCK_FRAC_ROUND_ERROR 0.5
#define UART_CLOCK_FRAC_RATIO 64

static reg_uart_t *uart_addr;

static inline reg_t uart_baud_integer(uart_baud_t baud)
{
  return UART_CLOCK / (UART_CLOCK_MUL * baud);
}

static inline reg_t uart_baud_fractional(uart_baud_t baud)
{
  uint64_t frac = ((UART_CLOCK * FRAC_CALC_COEF) / (UART_CLOCK_MUL * baud)) % FRAC_CALC_COEF;
  return (frac * UART_CLOCK_FRAC_RATIO + UART_CLOCK_FRAC_ROUND_ERROR * FRAC_CALC_COEF) / FRAC_CALC_COEF;
}

void uart_init(reg_uart_t *addr)
{
  uart_addr = addr;
}

void uart_begin(uart_baud_t baud)
{
  gpio_set_mode(GPIO_PIN14, GPIO_MODE_ALT0_PULL_DOWN);
  gpio_set_mode(GPIO_PIN15, GPIO_MODE_ALT0_PULL_DOWN);

  uart_addr->IBRD = uart_baud_integer(baud);
  uart_addr->FBRD = uart_baud_fractional(baud);

  uart_addr->LCRH = REG_UART_LCRH_FEN | REG_UART_LCRH_WLEN_8BITS;
  uart_addr->CR = REG_UART_CR_RXE | REG_UART_CR_TXE | REG_UART_CR_UARTEN;
}

void uart_putc(char c)
{
  uart_addr->DR = 0xff & c;
}

int32_t uart_getc(void)
{
  if ((uart_addr->FR & REG_UART_FR_RXFE) != 0) {
    return UART_EOF;
  } else {
    return uart_addr->DR & 0xff;
  }
}
