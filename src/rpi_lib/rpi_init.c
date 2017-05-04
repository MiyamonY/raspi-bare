#include "rpi.h"

void rpi_init(void)
{
  *SYST_CHI = 0;
  *SYST_CLO = 0;

  clearBss();

  rpi_gpio_init(&GPIO);

  return;
}
