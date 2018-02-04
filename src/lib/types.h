/**
 * File:  types.h
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 18:26:35 2018
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined UNITTEST
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#else
typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
#endif

typedef volatile int *addr_t;
typedef volatile uint32_t reg_t;
#ifdef __cplusplus
}
#endif

#endif /* _TYPES_H_ */
