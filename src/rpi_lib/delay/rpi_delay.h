/**
 * File:  rpi_delay.h
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:27:51 2017
 */

#ifndef _RPI_DELAY_H_
#define _RPI_DELAY_H_

#include "rpi_lib/rpi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void delay(uint32_t ms);
extern void delayMicroseconds(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* _RPI_DELAY_H_ */
