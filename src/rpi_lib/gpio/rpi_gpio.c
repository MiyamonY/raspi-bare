/**
 * File:  rpi_gpio.c
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:40:25 2017
 */

#include "rpi_gpio.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi_types.h"
#define WAIT_150_CYCLE()                                                                                                                   \
  do {                                                                                                                                     \
    for (uint32_t i = 0; i < 150; i++) {                                                                                                   \
      asm("mov r0,r0");                                                                                                                    \
    }                                                                                                                                      \
  } while (0)

typedef enum {
  PIN_MODE_INPUT = 0b000,
  PIN_MODE_OUTPUT = 0b001,
  PIN_MODE_ALT0 = 0b010,
  PIN_MODE_ALT1 = 0b011,
  PIN_MODE_ALT2 = 0b100,
  PIN_MODE_ALT3 = 0b101,
  PIN_MODE_ALT4 = 0b110,
  PIN_MODE_ALT5 = 0b111,
} gpio_pin_mode_t;

typedef enum {
  PULL_UD_DISABLE = 0b00,
  PULL_UD_PULL_DOWN_ENABLE = 0b01,
  PULL_UD_PULL_UP_ENABLE = 0b10,
  PULL_UP_RESERVED = 0b11,
} gpio_pull_ud_mode_t;

typedef enum {
  PULL_UD_CLK_NO_EFFECT = 0,
  PULL_UD_CLK_ASSERT = 1,
} gpio_pull_ud_clk_t;

void pinMode(gpio_pin_t pin, gpio_pin_t mode)
{
  rpi_peripheral_addr_t select_addr = GPIO_GPFSEL0;
  uint32_t offset = 0;

  if (pin < 10) {
    select_addr = GPIO_GPFSEL0;
    offset = pin;
  } else if (pin < 20) {
    select_addr = GPIO_GPFSEL1;
    offset = pin - 10;
  } else if (pin < 30) {
    select_addr = GPIO_GPFSEL2;
    offset = pin - 20;
  } else if (pin < 40) {
    select_addr = GPIO_GPFSEL3;
    offset = pin - 30;
  } else if (pin < 50) {
    select_addr = GPIO_GPFSEL4;
    offset = pin - 40;
  } else if (pin < 54) {
    select_addr = GPIO_GPFSEL5;
    offset = pin - 50;
  } else {
    /* error */
  }

  rpi_peripheral_addr_t pullup_addr = GPIO_GPPUDCLK0;
  if (pin < 32) {
    pullup_addr = GPIO_GPPUDCLK0;
  } else if (pin < 54) {
    pullup_addr = GPIO_GPPUDCLK1;
  } else {
    /* error */
  }

  switch (mode) {
  case GPIO_MODE_INPUT:
  default:
    *select_addr = (PIN_MODE_INPUT << offset);
    break;
  case GPIO_MODE_OUTPUT:
    *select_addr = (PIN_MODE_OUTPUT << offset);
    break;
  case GPIO_MODE_INPUT_PULL_UP:
    *select_addr = (PIN_MODE_INPUT << offset);
    *GPIO_GPPUD = PULL_UD_PULL_UP_ENABLE;
    WAIT_150_CYCLE();
    *pullup_addr = (PULL_UD_CLK_ASSERT << (pin % 32));
    WAIT_150_CYCLE();
    break;
  case GPIO_MODE_INPUT_PULL_DOWN:
    *select_addr = (PIN_MODE_INPUT << offset);
    *GPIO_GPPUD = PULL_UD_PULL_DOWN_ENABLE;
    WAIT_150_CYCLE();
    *pullup_addr = (PULL_UD_CLK_ASSERT << (pin % 32));
    WAIT_150_CYCLE();
    break;
  case GPIO_ALT0:
    *select_addr = (PIN_MODE_ALT0 << offset);
    break;
  case GPIO_ALT1:
    *select_addr = (PIN_MODE_ALT1 << offset);
    break;
  case GPIO_ALT2:
    *select_addr = (PIN_MODE_ALT2 << offset);
    break;
  case GPIO_ALT3:
    *select_addr = (PIN_MODE_ALT3 << offset);
    break;
  case GPIO_ALT4:
    *select_addr = (PIN_MODE_ALT4 << offset);
    break;
  case GPIO_ALT5:
    *select_addr = (PIN_MODE_ALT5 << offset);
    break;
  }

  return;
}

void digitalWrite(gpio_pin_t pin, gpio_hl_t hl)
{
  rpi_peripheral_addr_t addr = GPIO_GPCLR0;
  uint32_t offset = 0;

  if (pin < 32) {
    if (hl == GPIO_LOW) {
      addr = GPIO_GPCLR0;
    } else {
      addr = GPIO_GPCLR0;
    }
  } else if (pin < 54) {
    if (hl == GPIO_LOW) {
      addr = GPIO_GPCLR1;
    } else {
      addr = GPIO_GPSET1;
    }
  } else {
    /* error */
  }

  offset = pin % 32;
  *addr = (GPIO_HIGH << offset);

  return;
}

gpio_hl_t digitalRead(gpio_pin_t pin)
{
  rpi_peripheral_addr_t addr = GPIO_GPLEV0;
  uint32_t offset = 0;

  if (pin < 32) {
    addr = GPIO_GPLEV0;
  } else if (pin < 54) {
    addr = GPIO_GPLEV1;
  } else {
    /* error */
  }

  offset = pin % 32;

  return ((*addr) >> offset) & 0x0001;
}
