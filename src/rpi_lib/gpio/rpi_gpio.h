/**
 * File:  rpi_gpio.h
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:21:19 2017
 */

#ifndef _RPI_GPIO_H_
#define _RPI_GPIO_H_

#include "rpi_lib/rpi_types.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef uint64_t gpio_pin_t;

#define GPIO_PWR_PIN ((gpio_pin_t)35)
#define GPIO_ACT_PIN ((gpio_pin_t)47)

#define GPIO_UART0_TX_PIN ((gpio_pin_t)14)
#define GPIO_UART0_RX_PIN ((gpio_pin_t)15)

#define GPIO_BSC1_SDA1_PIN ((gpio_pin_t)2)
#define GPIO_BSC1_SCL1_PIN ((gpio_pin_t)3)

#define GPIO_SPI0_CE1 ((gpio_pin_t)7)
#define GPIO_SPI0_CE0 ((gpio_pin_t)8)
#define GPIO_SPI0_MISO ((gpio_pin_t)9)
#define GPIO_SPI0_MOSI ((gpio_pin_t)10)
#define GPIO_SPI0_SCLK ((gpio_pin_t)11)

typedef enum {
  GPIO_MODE_INPUT,
  GPIO_MODE_OUTPUT,
  GPIO_MODE_INPUT_PULL_UP,
  GPIO_MODE_INPUT_PULL_DOWN,
  GPIO_MODE_ALT0,
  GPIO_MODE_ALT1,
  GPIO_MODE_ALT2,
  GPIO_MODE_ALT3,
  GPIO_MODE_ALT4,
  GPIO_MODE_ALT5
} gpio_mode_t;

typedef enum {
  GPIO_LOW = 0,
  GPIO_HIGH = 1,
} gpio_hl_t;

extern void pinMode(gpio_pin_t pin, gpio_pin_t mode);
extern void digitalWrite(gpio_pin_t pin, gpio_hl_t hl);
extern gpio_hl_t digitalRead(gpio_pin_t pin);

#ifdef __cplusplus
}
#endif

#endif /* _RPI_GPIO_H_ */
