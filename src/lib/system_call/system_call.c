/**
 * File:  system_call.c
 * Author: ymiyamoto
 *
 * Created on Mon Feb  5 01:28:26 2018
 */
#include <stdbool.h>
#include <stdint.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#include "lib/uart/uart.h"

extern void *__bss_end;
static uint32_t *heap_end = (uint32_t *)&__bss_end;
static uint32_t *prev_heap_end;

register uint32_t *stack_ptr asm("sp");

caddr_t _sbrk(int incr)
{
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr) {
    return (caddr_t)-1;
  }
  heap_end += incr;
  return (caddr_t)prev_heap_end;
}

int _lseek(int file, int ptr, int dir)
{
  return 0;
}

int _write(int file, char *ptr, int len)
{
  uart_puts(ptr, len);
  return len;
}

int _close(int file)
{
  return 0;
}

int _read(int file, char *ptr, int len)
{
  return uart_gets(ptr, len);
}

int _fstat(int file, struct stat *st)
{
  return 0;
}

int _stat(const char *fname, struct stat *st)
{
  return 0;
}

int _gettimeofday(struct timeval *tp, struct timezone *tzp)
{
  return 0;
}

clock_t _times(struct tms *tp)
{
  return 0;
}

int _isatty(int fd)
{
  return 0;
}

int _system(const char *s)
{
  return 0;
}
