/**
 * File:  types.h
 * Author: ymiyamoto
 *
 * Created on Sat Feb  3 18:26:35 2018
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef volatile uint32_t reg_t;
typedef volatile reg_t *addr_t;

#ifdef __cplusplus
}
#endif

#endif /* _TYPES_H_ */
