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

#define PHY_PERI_ADDR(addr) ((rpi_peripheral_addr_t)(0x3F000000 + addr))

#define GPIO_BASE (0x200000)
#define GPIO_GPFSEL0 PHY_PERI_ADDR(GPIO_BASE + 0x00)
#define GPIO_GPFSEL1 PHY_PERI_ADDR(GPIO_BASE + 0x04)
#define GPIO_GPFSEL2 PHY_PERI_ADDR(GPIO_BASE + 0x08)
#define GPIO_GPFSEL3 PHY_PERI_ADDR(GPIO_BASE + 0x0C)
#define GPIO_GPFSEL4 PHY_PERI_ADDR(GPIO_BASE + 0x10)
#define GPIO_GPFSEL5 PHY_PERI_ADDR(GPIO_BASE + 0x14)

#define GPIO_GPSET0 PHY_PERI_ADDR(GPIO_BASE + 0x1C)
#define GPIO_GPSET1 PHY_PERI_ADDR(GPIO_BASE + 0x20)
#define GPIO_GPCLR0 PHY_PERI_ADDR(GPIO_BASE + 0x28)
#define GPIO_GPCLR1 PHY_PERI_ADDR(GPIO_BASE + 0x2C)
#define GPIO_GPLEV0 PHY_PERI_ADDR(GPIO_BASE + 0x34)
#define GPIO_GPLEV1 PHY_PERI_ADDR(GPIO_BASE + 0x38)

#define GPIO_GPPUD PHY_PERI_ADDR(GPIO_BASE + 0x94)
#define GPIO_GPPUDCLK0 PHY_PERI_ADDR(GPIO_BASE + 0x98)
#define GPIO_GPPUDCLK1 PHY_PERI_ADDR(GPIO_BASE + 0x9c)

#define SYST_BASE (0x003000)
#define SYST_CLO PHY_PERI_ADDR(SYST_BASE + 0x04)
#define SYST_CHI PHY_PERI_ADDR(SYST_BASE + 0x08)

#ifdef __cplusplus
}
#endif

#endif /* _RPI_PERIPHERALS_H_ */
