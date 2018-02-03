/**
 * File:  gpio.h
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 18:09:40 2018
 */

#ifndef _GPIO_H_
#define _GPIO_H_

#include "lib/reg/reg.h"
#include "lib/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  GPIO_MODE_INPUT = 0b000,
  GPIO_MODE_OUTPUT = 0b001,
  GPIO_MODE_ALT0 = 0b100,
  GPIO_MODE_ALT1 = 0b101,
  GPIO_MODE_ALT2 = 0b110,
  GPIO_MODE_ALT3 = 0b111,
  GPIO_MODE_ALT4 = 0b011,
  GPIO_MODE_ALT5 = 0b010,
} gpio_mode_t;

typedef enum {
  GPIO_PIN0 = 0,
  GPIO_PIN1,
  GPIO_PIN2,
  GPIO_PIN3,
  GPIO_PIN4,
  GPIO_PIN5,
  GPIO_PIN6,
  GPIO_PIN7,
  GPIO_PIN8,
  GPIO_PIN9,
  GPIO_PIN10,
  GPIO_PIN11,
  GPIO_PIN12,
  GPIO_PIN13,
  GPIO_PIN14,
  GPIO_PIN15,
  GPIO_PIN16,
  GPIO_PIN17,
  GPIO_PIN18,
  GPIO_PIN19,
  GPIO_PIN20,
  GPIO_PIN21,
  GPIO_PIN22,
  GPIO_PIN23,
  GPIO_PIN24,
  GPIO_PIN25,
  GPIO_PIN26,
  GPIO_PIN27,
  GPIO_PIN28,
  GPIO_PIN29,
  GPIO_PIN30,
  GPIO_PIN31,
  GPIO_PIN32,
  GPIO_PIN33,
  GPIO_PIN34,
  GPIO_PIN35,
  GPIO_PIN36,
  GPIO_PIN37,
  GPIO_PIN38,
  GPIO_PIN39,
  GPIO_PIN40,
  GPIO_PIN41,
  GPIO_PIN42,
  GPIO_PIN43,
  GPIO_PIN44,
  GPIO_PIN45,
  GPIO_PIN46,
  GPIO_PIN47,
  GPIO_PIN48,
  GPIO_PIN49,
  GPIO_PIN50,
  GPIO_PIN51,
  GPIO_PIN52,
  GPIO_PIN53
} gpio_pin_t;

typedef enum {
  GPIO_OUTPUT_LO,
  GPIO_OUTPUT_HI,
} gpio_output_t;

extern void gpio_init(reg_gpio_t *addr);
extern void gpio_set_mode(gpio_pin_t pin, gpio_mode_t mode);
extern void gpio_set_output(gpio_pin_t pin, gpio_output_t output);

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_H_ */
