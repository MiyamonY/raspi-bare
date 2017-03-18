#include "rpi.h"
#include "rpi_lib/bss/rpi_bss.h"
#include "rpi_lib/peripherals/rpi_peripherals.h"

void rpi_init(void)
{
  *SYST_CHI = 0;
  *SYST_CLO = 0;

  clearBss();

  return;
}
