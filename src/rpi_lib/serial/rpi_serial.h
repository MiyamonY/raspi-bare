/**
 * File:  rpi_serial.h
 * Author: ymiyamoto
 *
 * Created on Mon Mar 20 10:03:08 2017
 */

#ifndef _RPI_SERIAL_H_
#define _RPI_SERIAL_H_
#include "rpi_lib/rpi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int32_t Serial_begin(uint32_t baurate);
extern void Serial_end(void);
extern int32_t Serial_available(void);
extern void setSerialTimeout(int32_t read_ms, int32_t write_ms);
extern int32_t Serial_write(int8_t *buf, uint32_t len);
extern int32_t Serial_read(void);
extern int32_t uart0_getc(void);
extern int32_t uart0_putc(int32_t c);
extern uint32_t uart0_puts(int8_t *s);
extern int8_t *uart0_gets(int8_t *s, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif /* _RPI_SERIAL_H_ */
