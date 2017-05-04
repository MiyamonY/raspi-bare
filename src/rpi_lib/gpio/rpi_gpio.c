/**
 * File:  rpi_gpio.c
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:40:25 2017
 */

#include <stdbool.h>
#include <stdlib.h>

#include "rpi_gpio.h"
#include "rpi_lib/rpi.h"

#if defined(ARM)
#define WAIT_150_CYCLE()                                                                                                                   \
  do {                                                                                                                                     \
    for (uint32_t i = 0; i < 150; i++) {                                                                                                   \
      asm("mov r0,r0");                                                                                                                    \
    }                                                                                                                                      \
  } while (0)
#else
#define WAIT_150_CYCLE()
#endif

#define BITSET3(val, set, offset)                                                                                                          \
  do {                                                                                                                                     \
    (val) = (((val) & ((~((uint32_t)0b111 << (offset))))) | ((set) << (offset)));                                                          \
  } while (0)

typedef enum {
  PIN_MODE_INPUT = 0b000,
  PIN_MODE_OUTPUT = 0b001,
  PIN_MODE_ALT0 = 0b100,
  PIN_MODE_ALT1 = 0b101,
  PIN_MODE_ALT2 = 0b110,
  PIN_MODE_ALT3 = 0b111,
  PIN_MODE_ALT4 = 0b011,
  PIN_MODE_ALT5 = 0b010,
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

static rpi_peripheral_gpio_t *gpio;

void rpi_gpio_init(rpi_peripheral_gpio_t *peripheral)
{
  gpio = peripheral;
}

bool rpi_gpio_set_pin_mode(gpio_pin_t pin, gpio_mode_t mode)
{
  rpi_peripheral_register_t *select_addr = &gpio->GPFSEL0;

  if (pin > 53) return false;

  if (pin < 10) {
    select_addr = &gpio->GPFSEL0;
  } else if (pin < 20) {
    select_addr = &gpio->GPFSEL1;
  } else if (pin < 30) {
    select_addr = &gpio->GPFSEL2;
  } else if (pin < 40) {
    select_addr = &gpio->GPFSEL3;
  } else if (pin < 50) {
    select_addr = &gpio->GPFSEL4;
  } else {
    select_addr = &gpio->GPFSEL5;
  }

  uint32_t offset = (pin % 10) * 3;

  rpi_peripheral_register_t *pullup_addr = &gpio->GPPUDCLK0;
  if (pin < 32) {
    pullup_addr = &gpio->GPPUDCLK0;
  } else {
    pullup_addr = &gpio->GPPUDCLK1;
  }

  switch (mode) {
  case GPIO_MODE_INPUT:
  default:
    BITSET3(*select_addr, PIN_MODE_INPUT, offset);
    break;
  case GPIO_MODE_OUTPUT:
    BITSET3(*select_addr, PIN_MODE_OUTPUT, offset);
    break;
  case GPIO_MODE_INPUT_PULL_UP:
    gpio->GPPUD = PULL_UD_PULL_UP_ENABLE;
    WAIT_150_CYCLE();
    *pullup_addr = (PULL_UD_CLK_ASSERT << (pin % 32));
    WAIT_150_CYCLE();
    break;
  case GPIO_MODE_INPUT_PULL_DOWN:
    gpio->GPPUD = PULL_UD_PULL_DOWN_ENABLE;
    WAIT_150_CYCLE();
    *pullup_addr = (PULL_UD_CLK_ASSERT << (pin % 32));
    WAIT_150_CYCLE();
    break;
  case GPIO_MODE_ALT0:
    BITSET3(*select_addr, PIN_MODE_ALT0, offset);
    break;
  case GPIO_MODE_ALT1:
    BITSET3(*select_addr, PIN_MODE_ALT1, offset);
    break;
  case GPIO_MODE_ALT2:
    BITSET3(*select_addr, PIN_MODE_ALT2, offset);
    break;
  case GPIO_MODE_ALT3:
    BITSET3(*select_addr, PIN_MODE_ALT3, offset);
    break;
  case GPIO_MODE_ALT4:
    BITSET3(*select_addr, PIN_MODE_ALT4, offset);
    break;
  case GPIO_MODE_ALT5:
    BITSET3(*select_addr, PIN_MODE_ALT5, offset);
    break;
  }

  return true;
}

bool rpi_gpio_set_pin(gpio_pin_t pin, gpio_hl_t hl)
{
  if (pin > 53) return false;

  uint32_t offset = pin % 32;
  uint32_t value = GPIO_HIGH << offset;

  if (pin < 32) {
    if (hl == GPIO_LOW) {
      gpio->GPCLR0 = value;
    } else {
      gpio->GPSET0 = value;
    }
  } else {
    if (hl == GPIO_LOW) {
      gpio->GPCLR1 = value;
    } else {
      gpio->GPSET1 = value;
    }
  }

  return true;
}

bool rpi_gpio_get_pin(gpio_pin_t pin, gpio_hl_t *hl)
{
  if (pin > 53) return false;

  uint32_t offset = pin % 32;

  if (pin < 32) {
    *hl = ((gpio->GPLEV0) >> offset) & 0x0001;
  } else {
    *hl = ((gpio->GPLEV1) >> offset) & 0x0001;
  }

  return true;
}
