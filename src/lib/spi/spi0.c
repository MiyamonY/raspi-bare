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

static inline void set_cs(reg_t val)
{
  spi0_p->CS = val;
}

static inline void set_clock(spi_clock_t clock)
{
  spi0_p->CLK = CLOCK / clock;
}

static inline void spi_enable(void)
{
  spi0_p->CS |= REG_SPI_CS_TA;
}

static inline void spi_disable(void)
{
  spi0_p->CS &= ~REG_SPI_CS_TA;
}

static inline void wait_tx_done(void)
{
  while ((spi0_p->CS & REG_SPI_CS_DONE) == REG_SPI_CS_DONE_PROGRESS) {
  };
}

static inline byte xfer(byte b)
{
  while ((spi0_p->CS & REG_SPI_CS_TXD) == REG_SPI_CS_TXD_FULL) {
  }
  spi0_p->FIFO = b;

  while ((spi0_p->CS & REG_SPI_CS_RXD) == REG_SPI_CS_RXD_EMPTY) {
  }
  return (byte)spi0_p->FIFO;
}

void spi0_init(reg_spi0_t *spi0)
{
  spi0_p = spi0;
}

void spi0_begin(spi_mode_t mode, spi_clock_t clock)
{
  set_cs(REG_SPI_CS_CLEAR_BOTH | mode << 1 | REG_SPI_CS_CS_CS0);
  set_clock(clock);
}

void spi0_tx(byte msg[], size_t len)
{
  spi_enable();

  for (uint32_t i = 0; i < len; i++) {
    xfer(msg[i]);
  }

  wait_tx_done();

  spi_disable();
}

void spi0_rx(byte msg[], size_t len)
{
  spi_enable();

  for (uint32_t i = 0; i < len; i++) {
    msg[i] = xfer(0x00);
  }

  wait_tx_done();

  spi_disable();
}
