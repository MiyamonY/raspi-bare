#include "rpi.h"

static const rpi_peripheral_gpio_t *GPIO = (rpi_peripheral_gpio_t *)PHY_PERI_ADDR(GPIO_BASE);

void rpi_init(void)
{
  *SYST_CHI = 0;
  *SYST_CLO = 0;

  clearBss();

  return;
}
