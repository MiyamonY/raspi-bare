#include "rpi_lib/rpi.h"

volatile int dataVal = 1;
volatile int bssVal;

void main(void)
{
  volatile const char const *rodataVal = "HogeHoge!";

  rpi_init();

  return;
}
