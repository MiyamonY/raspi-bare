/**
 * File:  test_rpi_gpio.c
 * Author: ymiyamoto
 *
 * Created on Sat Apr 29 12:27:11 2017
 */

#include <criterion/criterion.h>

#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"

enum {
  FUNC_INPUT = 0b000,
  FUNC_OUTPUT = 0b001,
  FUNC_ALT0 = 0b100,
  FUNC_ALT1 = 0b101,
  FUNC_ALT2 = 0b110,
  FUNC_ALT3 = 0b111,
  FUNC_ALT4 = 0b011,
  FUNC_ALT5 = 0b010,
};

static rpi_peripheral_gpio_t gpio;

static void setup(void)
{
  rpi_gpio_init(&gpio);
  gpio.GPFSEL0 = 0;
  gpio.GPFSEL1 = 0;
  gpio.GPFSEL2 = 0;
  gpio.GPFSEL3 = 0;
  gpio.GPFSEL4 = 0;
  gpio.GPFSEL5 = 0;
}

static void assert_pin_mode(rpi_peripheral_register_t *reg, gpio_pin_t pin, gpio_pin_t mode, uint32_t mode_expect)
{
  cr_assert(rpi_gpio_set_pin_mode(pin, mode));
  uint32_t offset = (pin % 10) * 3;
  cr_assert_eq(*reg, mode_expect << offset, "GPFSEL is 0x%08x, actual is 0x%08x\n", *reg, mode_expect << offset);
}

static void assert_pin_all_mode(rpi_peripheral_register_t *reg, gpio_pin_t pin)
{
  assert_pin_mode(reg, pin, GPIO_MODE_INPUT, FUNC_INPUT);
  assert_pin_mode(reg, pin, GPIO_MODE_OUTPUT, FUNC_OUTPUT);
  assert_pin_mode(reg, pin, GPIO_MODE_ALT0, FUNC_ALT0);
  assert_pin_mode(reg, pin, GPIO_MODE_ALT1, FUNC_ALT1);
  assert_pin_mode(reg, pin, GPIO_MODE_ALT2, FUNC_ALT2);
  assert_pin_mode(reg, pin, GPIO_MODE_ALT3, FUNC_ALT3);
  assert_pin_mode(reg, pin, GPIO_MODE_ALT4, FUNC_ALT4);
  assert_pin_mode(reg, pin, GPIO_MODE_ALT5, FUNC_ALT5);
}

static void assert_set_pin_high(rpi_peripheral_register_t *reg, gpio_pin_t pin)
{
  cr_assert(rpi_gpio_set_pin(pin, GPIO_HIGH));
  cr_assert_eq(*reg, 0x01 << (pin % 32));
}

static void assert_set_pin_low(rpi_peripheral_register_t *reg, gpio_pin_t pin)
{
  cr_assert(rpi_gpio_set_pin(pin, GPIO_LOW));
  cr_assert_eq(*reg, 0x01 << (pin % 32));
}

static void assert_get_pin(rpi_peripheral_register_t *reg, gpio_pin_t pin)
{
  gpio_hl_t hl = GPIO_LOW;

  *reg = 0x00 << pin;
  cr_assert(rpi_gpio_get_pin(pin, &hl));
  cr_assert_eq(hl, GPIO_LOW);

  *reg = 0x01 << pin;
  cr_assert(rpi_gpio_get_pin(pin, &hl));
  cr_assert_eq(hl, GPIO_HIGH);
}

TestSuite(rpi_gpio, .init = setup);

Test(rpi_gpio, Pin0ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL0, 0);
}

Test(rpi_gpio, Pin9ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL0, 9);
}

Test(rpi_gpio, Pin10ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL1, 10);
}

Test(rpi_gpio, Pin19ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL1, 19);
}

Test(rpi_gpio, Pin20ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL2, 20);
}

Test(rpi_gpio, Pin29ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL2, 29);
}

Test(rpi_gpio, Pin30ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL3, 30);
}

Test(rpi_gpio, Pin39ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL3, 39);
}

Test(rpi_gpio, Pin40ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL4, 40);
}

Test(rpi_gpio, Pin49ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL4, 49);
}

Test(rpi_gpio, Pin50ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL5, 50);
}

Test(rpi_gpio, Pin53ModeCheck)
{
  assert_pin_all_mode(&gpio.GPFSEL5, 53);
}

Test(rpi_gpio, Pin54NotExist)
{
  cr_assert_not(rpi_gpio_set_pin_mode(54, GPIO_MODE_INPUT));
}

Test(rpi_gpio, SetPinModeNotEffectOtherPins)
{
  gpio_pin_t pin_a = 4;
  gpio_pin_t pin_b = 5;
  cr_assert(rpi_gpio_set_pin_mode(pin_a, FUNC_ALT1));
  cr_assert(rpi_gpio_set_pin_mode(pin_b, FUNC_ALT1));
  cr_assert_eq(gpio.GPFSEL0, (FUNC_ALT1 << (pin_a * 3)) | (FUNC_ALT1 << (pin_b * 3)));
}

Test(rpi_gpio, CheckSetPin0)
{
  gpio_pin_t pin = 0;
  assert_set_pin_high(&gpio.GPSET0, pin);
  assert_set_pin_low(&gpio.GPCLR0, pin);
}

Test(rpi_gpio, CheckSetPin31)
{
  gpio_pin_t pin = 31;
  assert_set_pin_high(&gpio.GPSET0, pin);
  assert_set_pin_low(&gpio.GPCLR0, pin);
}

Test(rpi_gpio, CheckSetPin32)
{
  gpio_pin_t pin = 32;
  assert_set_pin_high(&gpio.GPSET1, pin);
  assert_set_pin_low(&gpio.GPCLR1, pin);
}

Test(rpi_gpio, CheckSetPin53)
{
  gpio_pin_t pin = 53;
  assert_set_pin_high(&gpio.GPSET1, pin);
  assert_set_pin_low(&gpio.GPCLR1, pin);
}

Test(rpi_gpio, SetPinPinNotExist)
{
  cr_assert_not(rpi_gpio_set_pin(54, GPIO_HIGH));
}

Test(rpi_gpio, CheckGetPin0)
{
  assert_get_pin(&gpio.GPLEV0, 0);
}

Test(rpi_gpio, CheckGetPin31)
{
  assert_get_pin(&gpio.GPLEV0, 31);
}

Test(rpi_gpio, CheckGetPin32)
{
  assert_get_pin(&gpio.GPLEV1, 32);
}

Test(rpi_gpio, CheckGetPin53)
{
  assert_get_pin(&gpio.GPLEV1, 53);
}

Test(rpi_gpio, CheckGetPinPinNotExist)
{
  gpio_hl_t hl = GPIO_LOW;
  cr_assert_not(rpi_gpio_get_pin(54, &hl));
}
