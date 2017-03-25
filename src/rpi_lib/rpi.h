/**
 * File:  rpi.h
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 01:19:13 2017
 */

#ifndef _RPI_H_
#define _RPI_H_

#include "rpi_lib/delay/rpi_delay.h"
#include "rpi_lib/gpio/rpi_gpio.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"
#include "rpi_lib/rpi_types.h"
#include "rpi_lib/serial/rpi_serial.h"
#include "rpi_lib/timer/rpi_timer.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void rpi_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _RPI_H_ */
