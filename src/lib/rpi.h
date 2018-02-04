/**
 * File:  rpi.h
 * Author: ymiyamoto
 *
 * Created on Fri Feb  2 21:49:42 2018
 */

#ifndef _RPI_H_
#define _RPI_H_

#include "gpio/gpio.h"
#include "system_timer/system_timer.h"
#include "uart/uart.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void rpi_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _RPI_H_ */
