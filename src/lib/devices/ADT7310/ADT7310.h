/**
 * File:  ADT7310.h
 * Author: ymiyamoto
 *
 * Created on Sat Feb 10 16:04:05 2018
 */

#ifndef _ADT7310_H_
#define _ADT7310_H_

#include <stdint.h>

#include "lib/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  ATD7310_13BIT = 0,
  ATD7310_16BIT = 1,
} adt7310_resolution_t;

typedef enum {
  ATD7310_MODE_CONTINUOUS = 0b00,
  ATD7310_MODE_ONE_SHOT = 0b01,
  ATD7310_MODE_1SPS = 0b10,
  ATD7310_MODE_SHUTDOWN = 0b11
} adt7310_mode_t;

void ADT7310_init(void);
void ADT7310_configure(adt7310_resolution_t res, adt7310_mode_t mode, bool continuous);
double ADT7310_temperature(void);
byte ADT7310_id(void);

#ifdef __cplusplus
}
#endif

#endif /* _ADT7310_H_ */
