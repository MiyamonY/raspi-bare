/**
 * File:  spi0.c
 * Author: ymiyamoto
 *
 * Created on Fri Feb  9 19:45:50 2018
 */
#include <stdbool.h>
#include <stdint.h>

#include "lib/reg/reg.h"
#include "spi0.h"

static reg_spi0_t *spi0_p;

#define CLOCK (250000000)

void spi0_init(reg_spi0_t *spi0)
{
  spi0_p = spi0;
}

void spi0_begin(spi_mode_t mode, spi_clock_t clock)
{
  spi0_p->CS = REG_SPI_CS_CLEAR_BOTH | mode << 1 | REG_SPI_CS_CS_CS0;
  spi0_p->CLK = CLOCK / clock;
}

void spi0_tx(byte msg[], size_t len)
{
  spi0_p->CS |= REG_SPI_CS_TA;

  for (uint32_t i = 0; i < len; i++) {
    while ((spi0_p->CS & REG_SPI_CS_TXD) == REG_SPI_CS_TXD_FULL) {
    }
    spi0_p->FIFO = msg[i];
  }

  while ((spi0_p->CS & REG_SPI_CS_DONE) == REG_SPI_CS_DONE_PROGRESS) {
  };

  spi0_p->CS &= ~REG_SPI_CS_TA;
}
