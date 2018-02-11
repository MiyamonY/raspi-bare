/**
 * File:  ADT7310.c
 * Author: ymiyamoto
 *
 * Created on Sat Feb 10 16:22:23 2018
 */
#include <stdbool.h>
#include <stdint.h>

#include "ADT7310.h"
#include "lib/spi/spi0.h"
#include "lib/types.h"

#define CLOCK 5000000

#define COM_READ (1 << 6)
#define COM_WRITE (0 << 6)
#define COM_CONTINUOUS_READ (1 << 2)
#define COM_ADDR(addr) ((addr) << 3)

#define ADDR_STATUS (0x00)
#define ADDR_CONF (0x01)
#define ADDR_TEMPERATURE (0x02)
#define ADDR_ID (0x03)

#define STATUS_RESOLUTION(res) ((res) << 7)
#define STATUS_OPERATION_MODE(mode) ((mode) << 5)

static bool ContinuousMode;

void ADT7310_init(void)
{
  spi0_begin(SPI_MODE3, CLOCK);

  byte reset[] = {0xff, 0xff, 0xff, 0xff};
  spi0_xfer(reset, sizeof(reset), NULL, 0);
}

void ADT7310_configure(adt7310_resolution_t res, adt7310_mode_t mode, bool continuous)
{
  byte conf[] = {COM_WRITE | COM_ADDR(ADDR_CONF), STATUS_RESOLUTION(res) | STATUS_OPERATION_MODE(mode)};
  spi0_xfer(conf, sizeof(conf), NULL, 0);

  if (continuous) {
    byte cont[] = {COM_READ | COM_ADDR(ADDR_TEMPERATURE) | COM_CONTINUOUS_READ};
    spi0_xfer(cont, sizeof(cont), NULL, 0);
    ContinuousMode = continuous;
  }
}

byte ADT7310_id(void)
{
  byte com[] = {COM_READ | COM_ADDR(ADDR_ID), 0x00};
  byte res[2];
  spi0_xfer(com, sizeof(com), res, sizeof(res));

  return res[1];
}

double ADT7310_temperature(void)
{
  uint16_t tmp;
  if (ContinuousMode) {
    byte com[2] = {0x00, 0x00};
    byte res[2];
    spi0_xfer(com, sizeof(com), res, sizeof(res));
    tmp = (res[0] << 8) | res[1];
  } else {
    byte com[] = {COM_READ | COM_ADDR(ADDR_TEMPERATURE), 0x00, 0x00};
    byte res[3];
    spi0_xfer(com, sizeof(com), res, sizeof(res));
    tmp = (res[1] << 8) | res[2];
  }

  return ((int16_t)tmp) / 128.0;
}
