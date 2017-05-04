/**
 * File:  rpi_gpio.c
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:40:25 2017
 */

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
    (val) &= (((~((uint32_t)0b111 << ((offset)*3)))) | ((set) << ((offset)*3)));                                                           \
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

void pinMode(gpio_pin_t pin, gpio_pin_t mode)
{
  rpi_peripheral_register_t *select_addr = &gpio->GPFSEL0;
  uint32_t offset = 0;

  if (pin < 10) {
    select_addr = &gpio->GPFSEL0;
    offset = pin;
  } else if (pin < 20) {
    select_addr = &gpio->GPFSEL1;
    offset = (pin - 10);
  } else if (pin < 30) {
    select_addr = &gpio->GPFSEL2;
    offset = (pin - 20);
  } else if (pin < 40) {
    select_addr = &gpio->GPFSEL3;
    offset = (pin - 30);
  } else if (pin < 50) {
    select_addr = &gpio->GPFSEL4;
    offset = (pin - 40);
  } else if (pin < 54) {
    select_addr = &gpio->GPFSEL5;
    offset = (pin - 50);
  } else {
    /* error */
  }

  offset *= 3;

  rpi_peripheral_register_t *pullup_addr = &gpio->GPPUDCLK0;
  if (pin < 32) {
    pullup_addr = &gpio->GPPUDCLK0;
  } else if (pin < 54) {
    pullup_addr = &gpio->GPPUDCLK1;
  } else {
    /* error */
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

  return;
}

void digitalWrite(gpio_pin_t pin, gpio_hl_t hl)
{
  rpi_peripheral_register_t *addr = &gpio->GPCLR0;
  uint32_t offset = 0;

  if (pin < 32) {
    if (hl == GPIO_LOW) {
      addr = &gpio->GPCLR0;
    } else {
      addr = &gpio->GPCLR0;
    }
  } else if (pin < 54) {
    if (hl == GPIO_LOW) {
      addr = &gpio->GPCLR1;
    } else {
      addr = &gpio->GPSET1;
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
  rpi_peripheral_register_t *addr = &gpio->GPLEV0;
  uint32_t offset = 0;

  if (pin < 32) {
    addr = &gpio->GPLEV0;
  } else if (pin < 54) {
    addr = &gpio->GPLEV1;
  } else {
    /* error */
  }

  offset = pin % 32;

  return ((*addr) >> offset) & 0x0001;
}
