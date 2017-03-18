/**
 * File:  rpi_timer.h
 * Author: ymiyamoto
 *
 * Created on Sun Mar 19 04:26:45 2017
 */

#ifndef _RPI_TIMER_H_
#define _RPI_TIMER_H_
#include "rpi_lib/rpi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern uint64_t millis(void);
extern uint64_t micros(void);

#ifdef __cplusplus
}
#endif

#endif /* _RPI_TIMER_H_ */
