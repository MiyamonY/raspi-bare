/**
 * File:  reg.h
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 21:21:30 2018
 */

#ifndef _REG_H_
#define _REG_H_

#include "lib/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  reg_t GPFSEL0;
  reg_t GPFSEL1;
  reg_t GPFSEL2;
  reg_t GPFSEL3;
  reg_t GPFSEL4;
  reg_t GPFSEL5;
  reg_t reserved1;
  reg_t GPSET0;
  reg_t GPSET1;
  reg_t reserved2;
  reg_t GPCLR0;
  reg_t GPCLR1;
  reg_t reserved3;
  reg_t GPLEV0;
  reg_t GPLEV1;
  reg_t reserved4;
  reg_t GPEDS0;
  reg_t GPEDS1;
  reg_t reserved5;
  reg_t GPREN0;
  reg_t GPREEN1;
  reg_t reserved6;
  reg_t GPFEN0;
  reg_t GPFEN1;
  reg_t reserved7;
  reg_t GPHEN0;
  reg_t GPHEN1;
  reg_t reserved8;
  reg_t GPAREN0;
  reg_t GPAREN1;
  reg_t reserved9;
  reg_t GPAFEN0;
  reg_t GPAFEN1;
  reg_t reserved10;
  reg_t GPPUD;
  reg_t GPPUDCLK0;
  reg_t GPPUDCLK1;
} reg_gpio_t;

typedef struct {
  reg_t CS;
  reg_t CLO;
  reg_t CHI;
} reg_system_timer_t;

typedef struct {
  reg_t DR;           /* 0x00 */
  reg_t RSRECR;       /* 0x04 */
  reg_t reserved1[4]; /* 0x08 */
  reg_t FR;           /* 0x18 */
  reg_t reserved2;    /* 0x1C */
  reg_t ILPR;         /* 0x20 */
  reg_t IBRD;         /* 0x24 */
  reg_t FBRD;         /* 0x28 */
  reg_t LCRH;         /* 0x2C */
  reg_t CR;           /* 0x30 */
} reg_uart_t;

typedef struct {
  reg_t CS;   /* 0x00 */
  reg_t FIFO; /* 0x04 */
  reg_t CLK;  /* 0x08 */
  reg_t DLEN; /* 0x0C */
  reg_t LTOH; /* 0x10 */
  reg_t DC;   /* 0x14 */
} reg_spi0_t;

#define REG_UART_LCRH_WLEN_8BITS (0x03 << 5)
#define REG_UART_LCRH_FEN (0x01 << 4)
#define REG_UART_CR_RXE (0x01 << 9)
#define REG_UART_CR_TXE (0x01 << 8)
#define REG_UART_CR_UARTEN (0x01 << 0)
#define REG_UART_FR_TXFF (0x01 << 5)
#define REG_UART_FR_RXFE (0x01 << 4)

#define REG_SPI_CS_CS_CS0 (0b00 << 0)
#define REG_SPI_CS_CS_CS1 (0b01 << 0)
#define REG_SPI_CS_CS_CS2 (0b10 << 0)
#define REG_SPI_CS_CLEAR_TX (0b01 << 4)
#define REG_SPI_CS_CLEAR_RX (0b10 << 4)
#define REG_SPI_CS_CLEAR_BOTH (0b11 << 4)
#define REG_SPI_CS_TA (1 << 7)
#define REG_SPI_CS_REN (1 << 12)
#define REG_SPI_CS_REN_ENABLE (1 << 12)
#define REG_SPI_CS_DONE (1 << 16)
#define REG_SPI_CS_DONE_PROGRESS (0 << 16)
#define REG_SPI_CS_DONE_DONE (1 << 16)
#define REG_SPI_CS_RXD (1 << 17)
#define REG_SPI_CS_RXD_EMPTY (0 << 17)
#define REG_SPI_CS_RXD_CONTAIN (1 << 17)
#define REG_SPI_CS_TXD (1 << 18)
#define REG_SPI_CS_TXD_FULL (0 << 18)
#define REG_SPI_CS_TXD_EMPTY (1 << 18)

extern reg_gpio_t reg_gpio;
extern reg_system_timer_t reg_system_timer;
extern reg_uart_t reg_uart;
extern reg_spi0_t reg_spi0;

#ifdef __cplusplus
}
#endif

#endif /* _REG_H_ */
