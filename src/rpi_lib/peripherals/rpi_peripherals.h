/**
 * File:  rpi_peripherals.h
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 03:43:31 2017
 */

#ifndef _RPI_PERIPHERALS_H_
#define _RPI_PERIPHERALS_H_

#include "rpi_lib/rpi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef vuint32_t *rpi_peripheral_addr_t;
typedef uint32_t rpi_peripheral_register_t;

#define PHY_PERI_ADDR(addr) ((rpi_peripheral_addr_t)(0x3F000000 + addr))

typedef struct __attribute__((packed)) {
  rpi_peripheral_register_t GPFSEL0;
  rpi_peripheral_register_t GPFSEL1;
  rpi_peripheral_register_t GPFSEL2;
  rpi_peripheral_register_t GPFSEL3;
  rpi_peripheral_register_t GPFSEL4;
  rpi_peripheral_register_t GPFSEL5;
  rpi_peripheral_register_t reserved0;
  rpi_peripheral_register_t GPSET0;
  rpi_peripheral_register_t GPSET1;
  rpi_peripheral_register_t reserved1;
  rpi_peripheral_register_t GPCLR0;
  rpi_peripheral_register_t GPCLR1;
  rpi_peripheral_register_t reserved2;
  rpi_peripheral_register_t GPLEV0;
  rpi_peripheral_register_t GPLEV1;
  rpi_peripheral_register_t reserved3;
  rpi_peripheral_register_t GPEDS0;
  rpi_peripheral_register_t GPEDS1;
  rpi_peripheral_register_t reserved4;
  rpi_peripheral_register_t GPFEN0;
  rpi_peripheral_register_t GPFEN1;
  rpi_peripheral_register_t reserved5;
  rpi_peripheral_register_t GPHEN0;
  rpi_peripheral_register_t GPHEN1;
  rpi_peripheral_register_t reserved6;
  rpi_peripheral_register_t GPLEN0;
  rpi_peripheral_register_t GPLEN1;
  rpi_peripheral_register_t reserved7;
  rpi_peripheral_register_t GPAREN0;
  rpi_peripheral_register_t GPAREN1;
  rpi_peripheral_register_t reserved8;
  rpi_peripheral_register_t GPAFEN0;
  rpi_peripheral_register_t GPAFEN1;
  rpi_peripheral_register_t reserved9;
  rpi_peripheral_register_t GPPUD;
  rpi_peripheral_register_t GPPUDCLK0;
  rpi_peripheral_register_t GPPUDCLK1;
  rpi_peripheral_register_t reserved10;
  rpi_peripheral_register_t reserved11;
} rpi_peripheral_gpio_t;

extern rpi_peripheral_gpio_t GPIO;

#define SYST_BASE (0x003000)
#define SYST_CLO PHY_PERI_ADDR(SYST_BASE + 0x04)
#define SYST_CHI PHY_PERI_ADDR(SYST_BASE + 0x08)

#define UART0_BASE (0x201000)
#define UART0_DR PHY_PERI_ADDR(UART0_BASE + 0x00)
#define UART0_FR PHY_PERI_ADDR(UART0_BASE + 0x18)
#define UART0_IBRD PHY_PERI_ADDR(UART0_BASE + 0x24)
#define UART0_FBRD PHY_PERI_ADDR(UART0_BASE + 0x28)
#define UART0_LCRH PHY_PERI_ADDR(UART0_BASE + 0x2c)
#define UART0_CR PHY_PERI_ADDR(UART0_BASE + 0x30)

#define BSC1_BASE (0x804000)
#define BSC1_C PHY_PERI_ADDR(BSC1_BASE + 0x00)
#define BSC1_S PHY_PERI_ADDR(BSC1_BASE + 0x04)
#define BSC1_DLEN PHY_PERI_ADDR(BSC1_BASE + 0x08)
#define BSC1_A PHY_PERI_ADDR(BSC1_BASE + 0x0C)
#define BSC1_FIFO PHY_PERI_ADDR(BSC1_BASE + 0x10)
#define BSC1_DIV PHY_PERI_ADDR(BSC1_BASE + 0x14)
#define BSC1_DEL PHY_PERI_ADDR(BSC1_BASE + 0x18)
#define BSC1_CLKT PHY_PERI_ADDR(BSC1_BASE + 0x1C)

#define SPI0_BASE (0x204000)

#define SPI0_CS PHY_PERI_ADDR(SPI0_BASE + 0x00)
#define SPI0_FIFO PHY_PERI_ADDR(SPI0_BASE + 0x04)
#define SPI0_CLK PHY_PERI_ADDR(SPI0_BASE + 0x08)
#define SPI0_DLEN PHY_PERI_ADDR(SPI0_BASE + 0x0C)
#define SPI0_LTOH PHY_PERI_ADDR(SPI0_BASE + 0x10)
#define SPI0_DC PHY_PERI_ADDR(SPI0_BASE + 0x14)

#define INTERRUPT_BASE (0x00B200)
#define INTERRUPT_IRQ_BASIC_PENDING PHY_PERI_ADDR(INTERRUPT_BASE + 0x00)
#define INTERRUPT_IRQ_PENDING1 PHY_PERI_ADDR(INTERRUPT_BASE + 0x04)
#define INTERRUPT_IRQ_PENDING2 PHY_PERI_ADDR(INTERRUPT_BASE + 0x08)
#define INTERRUPT_FIQ_CONTROL PHY_PERI_ADDR(INTERRUPT_BASE + 0x0C)
#define INTERRUPT_ENABLE_IRQS1 PHY_PERI_ADDR(INTERRUPT_BASE + 0x10)
#define INTERRUPT_ENABLE_IRQS2 PHY_PERI_ADDR(INTERRUPT_BASE + 0x14)
#define INTERRUPT_ENABLE_BASIC_IRQS PHY_PERI_ADDR(INTERRUPT_BASE + 0x18)
#define INTERRUPT_DISABLE_IRQS1 PHY_PERI_ADDR(INTERRUPT_BASE + 0x1C)
#define INTERRUPT_DISABLE_IRQS2 PHY_PERI_ADDR(INTERRUPT_BASE + 0x20)
#define INTERRUPT_DISABLE_BASIC_IRQS PHY_PERI_ADDR(INTERRUPT_BASE + 0x24)

#define TIMER_BASE (0x00B400)
#define TIMER_LOAD PHY_PERI_ADDR(TIMER_BASE + 0x00)
#define TIMER_VALUE PHY_PERI_ADDR(TIMER_BASE + 0x04)
#define TIMER_CONTROL PHY_PERI_ADDR(TIMER_BASE + 0x08)
#define TIMER_IRQ_CLR PHY_PERI_ADDR(TIMER_BASE + 0x0C)
#define TIMER_RAW_IRQ PHY_PERI_ADDR(TIMER_BASE + 0x10)
#define TIMER_MASKED_IRQ PHY_PERI_ADDR(TIMER_BASE + 0x14)
#define TIMER_RELOAD PHY_PERI_ADDR(TIMER_BASE + 0x18)
#define TIMER_PREDIVIDER PHY_PERI_ADDR(TIMER_BASE + 0x1C)
#define TIMER_FREE_RUNNING_COUNTER PHY_PERI_ADDR(TIMER_BASE + 0x20)

#ifdef __cplusplus
}
#endif

#endif /* _RPI_PERIPHERALS_H_ */
