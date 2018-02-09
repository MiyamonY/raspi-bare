/**
 * File:  spi0.h
 * Author: ymiyamoto
 *
 * Created on Fri Feb  9 19:34:00 2018
 */

#ifndef _SPI0_H_
#define _SPI0_H_

#include <stdint.h>

#include "lib/reg/reg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  SPI_MODE0 = 0b00,
  SPI_MODE1 = 0b01,
  SPI_MODE2 = 0b10,
  SPI_MODE3 = 0b11,
} spi_mode_t;

typedef uint32_t spi_clock_t;

extern void spi0_init(reg_spi0_t *spi0);
extern void spi0_begin(spi_mode_t mode, spi_clock_t clock);

#ifdef __cplusplus
}
#endif

#endif /* _SPI0_H_ */
