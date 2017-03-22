/**
 * File:  sbrk.c
 * Author: ymiyamoto
 *
 * Created on Wed Mar 22 09:26:52 2017
 */

#include "rpi_lib/rpi.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <sys/types.h>

#define SYSCALL_DEF_INT(name, ...)                                                                                                         \
  int name(__VA_ARGS__)                                                                                                                    \
  {                                                                                                                                        \
    return 0;                                                                                                                              \
  }
#define SYSCALL_DEF_VOID(name, ...)                                                                                                        \
  void name(__VA_ARGS__)                                                                                                                   \
  {                                                                                                                                        \
    return;                                                                                                                                \
  }

extern void *__bss_end;
uint32_t heap_end = (uint32_t)&__bss_end;
uint32_t prev_heap_end;
register char *stack_ptr asm("sp");

SYSCALL_DEF_INT(_lseek, int file, int ptr, int dir)
SYSCALL_DEF_INT(_open, const char *path, int flags, ...)
SYSCALL_DEF_INT(_close, int files)
SYSCALL_DEF_VOID(_exit, int n)
SYSCALL_DEF_INT(_kill, int n, int m)
SYSCALL_DEF_INT(_getpid, int n)
SYSCALL_DEF_INT(_fstat, int file, struct stat *st)
SYSCALL_DEF_INT(_link, void)
SYSCALL_DEF_INT(_unlink, void)
SYSCALL_DEF_VOID(_raise, void)
SYSCALL_DEF_INT(_isatty, int fd)
SYSCALL_DEF_INT(_system, const char *s)
SYSCALL_DEF_INT(_rename, const char *oldpath, const char *newpath)

caddr_t _sbrk(int incr)
{
  prev_heap_end = heap_end;
  if ((heap_end + incr) > (uint32_t)stack_ptr) {
    return (caddr_t)-1;
  }
  heap_end += incr;

  return (caddr_t)prev_heap_end;
}

int _write(int file, char *ptr, int len)
{
  for (uint32_t r = 0; r < len; r++) {
    uart0_putc(ptr[r]);
  }

  return len;
}

int _read(int file, char *ptr, int len)
{
  uint32_t r;
  for (r = 0; r < len; r++) {
    ptr[r] = uart0_getc();
  }

  return r;
}

int _gettimeofday(struct timeval *tp, struct timezone *tzp)
{
  if (tp) {
    tp->tv_usec = micros();
    tp->tv_sec = tp->tv_usec / 1000 / 1000;
  }

  if (tzp) {
    tzp->tz_minuteswest = 0;
    tzp->tz_dsttime = 0;
  }

  return 0;
}

clock_t _times(struct tms *tp)
{
  clock_t timeval = millis() / 1000;
  if (tp) {
    tp->tms_utime = timeval;
    tp->tms_stime = 0;
    tp->tms_cutime = 0;
    tp->tms_cstime = 0;
  }

  return timeval;
}
