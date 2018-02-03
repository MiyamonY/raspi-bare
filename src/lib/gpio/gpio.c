/**
 * File:  gpio.c
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 18:08:49 2018
 */
#include "gpio.h"

static gpio_addr_t *gpio;

static inline addr_t gpio_mode_addr(uint32_t index)
{
  switch (index) {
  case 0:
    return &gpio->GPFSEL0;
  case 1:
    return &gpio->GPFSEL1;
  case 2:
    return &gpio->GPFSEL2;
  case 3:
    return &gpio->GPFSEL3;
  case 4:
    return &gpio->GPFSEL4;
  case 5:
    return &gpio->GPFSEL5;
  default:
    return &gpio->GPFSEL0;
  }
}

static inline addr_t gpio_set_addr(uint32_t index)
{
  switch (index) {
  case 0:
    return &gpio->GPSET0;
  case 1:
    return &gpio->GPSET1;
  }
}

static inline addr_t gpio_clr_addr(uint32_t index)
{
  switch (index) {
  case 0:
    return &gpio->GPCLR0;
  case 1:
    return &gpio->GPCLR1;
  }
}

void gpio_init(gpio_addr_t *addr)
{
  gpio = addr;
}

void gpio_set_mode(gpio_pin_t pin, gpio_mode_t mode)
{
  addr_t addr = gpio_mode_addr(pin / 10);

  uint32_t offset = 3 * (pin % 10);
  uint32_t mask = ~(0b111 << offset);
  *addr &= mask;

  uint32_t val = mode << offset;
  *addr |= val;
}

void gpio_set_output(gpio_pin_t pin, gpio_output_t output)
{
  switch (output) {
  case GPIO_OUTPUT_HI: {
    addr_t addr = gpio_set_addr(pin / 32);
    *addr |= 1 << (pin % 32);
  } break;
  case GPIO_OUTPUT_LO:
  default: {
    addr_t addr = gpio_clr_addr(pin / 32);
    *addr |= 1 << (pin % 32);
  } break;
  }
}
