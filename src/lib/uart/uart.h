/**
 * File:  uart.h
 * Author: ymiyamoto
 *
 * Created on Sun Feb  4 12:35:52 2018
 */

#ifndef _UART_H_
#define _UART_H_

#include "lib/reg/reg.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define UART_EOF -1

typedef enum { UART_BAUD_115200 = 115200 } uart_baud_t;

extern void uart_init(reg_uart_t *addr);
extern void uart_begin(uart_baud_t baud);
extern int32_t uart_putc(char c);
extern int32_t uart_getc(void);
extern void uart_puts(char buf[], size_t len);
extern size_t uart_gets(char buf[], size_t len);

#ifdef __cplusplus
}
#endif

#endif /* _UART_H_ */
