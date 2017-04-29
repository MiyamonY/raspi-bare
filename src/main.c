#include "rpi_lib/rpi.h"
#include <stdio.h>

#define SLEEP_MS 1000
#define UART_BAURATE 115200

#define BSC_C_I2CEN_EN (0x01 << 15)
#define BSC_C_ST_EN (0x01 << 7)
#define BSC_C_CLEAR_ALL (0x03 << 4)
#define BSC_C_READ_READ (0x01 << 0)
#define BSC_C_READ_WRITE_MASK (~BSC_C_READ_READ)

#define BSC_S_CLKT (0x01 << 9)
#define BSC_S_ERR (0x01 << 8)
#define BSC_S_RXF (0x01 << 7)
#define BSC_S_TXE (0x01 << 6)
#define BSC_S_RXD (0x01 << 5)
#define BSC_S_TXD (0x01 << 4)
#define BSC_S_RXR (0x01 << 3)
#define BSC_S_TXW (0x01 << 2)
#define BSC_S_DONE (0x01 << 1)
#define BSC_S_TA (0x01 << 0)

#define INTERRUPT_BASE (0x00B200)
#define INTERRUPT_IRQ_BASIC_PENDING PHY_PERI_ADDR(INTERRUPT_BASE + 0x00)
#define INTERRUPT_IRQ_PENDING1 PHY_PERI_ADDR(INTERRUPT_BASE + 0x04)
#define INTERRUPT_IRQ_PENDING2 PHY_PERI_ADDR(INTERRUPT_BASE + 0x08)
#define INTERRUPT_FIQ_CONTROL PHY_PERI_ADDR(INTERRUPT_BASE + 0x0C)
#define INTERRUPT_ENABLE_IRQS1 PHY_PERI_ADDR(INTERRUPT_BASE + 0x10)
#define INTERRUPT_ENABLE_IRQS2 PHY_PERI_ADDR(INTERRUPT_BASE + 0x14)
#define INTERRUPT_ENABLE_BASIC_IRQS PHY_PERI_ADDR(INTERRUPT_BASE + 0x18)
#define INTERRUPT_DISABLE_IRQS1 PHY_PERI_ADDR(INTERRUPT_BASE + 0x1C)
#define INTERRUPT_DISABLE_IRQS2 PHY_PERI_ADDR(INTERRUPT_BASE + 0x20)
#define INTERRUPT_DISABLE_BASIC_IRQS PHY_PERI_ADDR(INTERRUPT_BASE + 0x24)

#define TIMER_BASE (0x00B400)
#define TIMER_LOAD PHY_PERI_ADDR(TIMER_BASE + 0x00)
#define TIMER_VALUE PHY_PERI_ADDR(TIMER_BASE + 0x04)
#define TIMER_CONTROL PHY_PERI_ADDR(TIMER_BASE + 0x08)
#define TIMER_IRQ_CLR PHY_PERI_ADDR(TIMER_BASE + 0x0C)
#define TIMER_RAW_IRQ PHY_PERI_ADDR(TIMER_BASE + 0x10)
#define TIMER_MASKED_IRQ PHY_PERI_ADDR(TIMER_BASE + 0x14)
#define TIMER_RELOAD PHY_PERI_ADDR(TIMER_BASE + 0x18)
#define TIMER_PREDIVIDER PHY_PERI_ADDR(TIMER_BASE + 0x1C)
#define TIMER_FREE_RUNNING_COUNTER PHY_PERI_ADDR(TIMER_BASE + 0x20)

#define SPI0_CS_CSPOL2_HIGH (0x01 << 23)
#define SPI0_CS_CSPOL2_LOW (0x00 << 23)
#define SPI0_CS_CSPOL1_HIGH (0x01 << 22)
#define SPI0_CS_CSPOL1_LOW (0x00 << 22)
#define SPI0_CS_CSPOL0_HIGH (0x01 << 21)
#define SPI0_CS_CSPOL0_LOW (0x00 << 21)
#define SPI0_CS_TA_ACTIVE (0x01 << 7)
#define SPI0_CS_CSPOL_HIGH (0x01 << 6)
#define SPI0_CS_CSPOL_LOW (0x00 << 6)
#define SPI0_CS_CLEAR_TX (0x01 << 4)
#define SPI0_CS_CLEAR_RX (0x02 << 4)
#define SPI0_CS_CLEAR_ALL (SPI0_CS_CLEAR_TX | SPI0_CS_CLEAR_RX)
#define SPI0_CS_MODE_0x (0x00 << 3)
#define SPI0_CS_MODE_1x (0x01 << 3)
#define SPI0_CS_MODE_x0 (0x01 << 2)
#define SPI0_CS_MODE_x1 (0x00 << 2)
#define SPI0_CS_MODE0 (SPI0_CS_MODE_0x | SPI0_CS_MODE_x0)
#define SPI0_CS_MODE1 (SPI0_CS_MODE_0x | SPI0_CS_MODE_x1)
#define SPI0_CS_MODE2 (SPI0_CS_MODE_1x | SPI0_CS_MODE_x0)
#define SPI0_CS_MODE3 (SPI0_CS_MODE_1x | SPI0_CS_MODE_x1)
#define SPI0_CS_CS_CS0 (0x00 << 0)
#define SPI0_CS_CS_CS1 (0x01 << 0)
#define SPI0_CS_CS_CS2 (0x10 << 0)

#define SPI0_CS_RXF_MASK (0x01 << 20)
#define SPI0_CS_RXR_MASK (0x01 << 19)
#define SPI0_CS_TXD_MASK (0x01 << 18)
#define SPI0_CS_RXD_MASK (0x01 << 17)
#define SPI0_CS_DONE_MASK (0x01 << 16)

#define AQM0802_ADDR (0x7C)

#define PCF8574_ADDR 0x27 // or 0x3F
#define MPU6050_ADDR ((uint8_t)0x68)

#define ADT7310_ADDR_CONFIG (0x01 << 3)
#define ADT7310_ADDR_STATUS (0x00 << 3)
#define ADT7310_ADDR_TMP (0x02 << 3)

#define ADT7310_CONFIG_MODE_CONTINUOUS 0x00
#define ADT7310_CONFIG_MODE_ONESHOT 0x01
#define ADT7310_CONFIG_MODE_1SPSS 0x10
#define ADT7310_CONFIG_MODE_SHUTDOWN 0x11

#define ADT7310_CMD_READ (0x01 << 6)
#define ADT7310_CMD_WRITE (0x00 << 6)
#define ATD7310_CMD_CONTINUOUS (0x01 << 2)

void timerIRQ_handler(void)
{
  static uint32_t led = 0;
  if (led) {
    printf("LED : ON\n");
    digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);
  } else {
    printf("LED : OFF\n");
    digitalWrite(GPIO_ACT_PIN, GPIO_LOW);
  }
  led = !led;

  return;
}

void IRQ_handler(void)
{
  /* disable_IRQ(); */
  printf("get IRQ in IRQ handler\n");
  /* printf("CPSR (in IRQ handler) = 0x%08x\n", getmode()); */
  if ((*INTERRUPT_IRQ_BASIC_PENDING & 0x01) != 0) {
    timerIRQ_handler();
    *TIMER_IRQ_CLR = 0;
  }
  /* enable_IRQ(); */

  return;
}

int main(void)
{
  rpi_init();

  pinMode(GPIO_ACT_PIN, GPIO_MODE_OUTPUT);
  pinMode(GPIO_BSC1_SDA1_PIN, GPIO_MODE_ALT0);
  pinMode(GPIO_BSC1_SCL1_PIN, GPIO_MODE_ALT0);

  digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);
  Serial_begin(UART_BAURATE);
  printf("PROGRAM START\n");

  /* default *BSC1_DIV = 0; */

  /* *BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE; */
  /* *BSC1_A = MPU6050_ADDR; */
  /* *BSC1_C &= BSC_C_READ_WRITE_MASK; */
  /* *BSC1_C |= BSC_C_CLEAR_ALL; */
  /* *BSC1_DLEN = 1; */
  /* *BSC1_FIFO = 0x75; /\* who am i *\/ */

  /* *BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN; */

  /* delay(250); */

  /* printf("write addr...\n"); */

  /* while (!(*BSC1_S & BSC_S_DONE)) */
  /*   ; */
  /* printf("BSC1 Status:0x%08x\n", *BSC1_S); /\* 0x0252 *\/ */

  /* *BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE; */
  /* *BSC1_A = MPU6050_ADDR; */
  /* *BSC1_C |= BSC_C_READ_READ; */
  /* *BSC1_C |= BSC_C_CLEAR_ALL; */
  /* *BSC1_DLEN = 1; */
  /* *BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN; */

  /* while (!(*BSC1_S & BSC_S_DONE)) */
  /*   ; */
  /* printf("BSC1 Status:0x%08x\n", *BSC1_S); /\* 0x0232 *\/ */

  /* printf("received data is 0x%08x\n", *BSC1_FIFO); */

  /* *BSC1_DIV = 0; */
  /* *BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE; */

  /* *BSC1_A = AQM0802_ADDR >> 1; */

  /* *BSC1_C &= BSC_C_READ_WRITE_MASK; */
  /* *BSC1_C |= BSC_C_CLEAR_ALL; */
  /* *BSC1_DLEN = 2 * 9; */

  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x38; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x39; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x14; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x70; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x56; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x6C; */

  /* *BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN; */

  /* delay(250); */

  /* printf("wait1...\n"); */

  /* while (!(*BSC1_S & BSC_S_TXW)) */
  /*   ; */

  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x38; */

  /* printf("wait2...\n"); */

  /* while (!(*BSC1_S & BSC_S_TXW)) */
  /*   ; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x0C; */

  /* printf("wait3...\n"); */

  /* while (!(*BSC1_S & BSC_S_TXW)) */
  /*   ; */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x01; */

  /* printf("wait4...\n"); */

  /* while (!(*BSC1_S & BSC_S_DONE)) */
  /*   ; */
  /* delay(200); */

  /* *BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE; */

  /* *BSC1_A = AQM0802_ADDR >> 1; */

  /* *BSC1_C &= BSC_C_READ_WRITE_MASK; */
  /* *BSC1_C |= BSC_C_CLEAR_ALL; */
  /* *BSC1_DLEN = 8; */

  /* printf("print lcd...\n"); */
  /* *BSC1_FIFO = 0x80; */
  /* *BSC1_FIFO = 0x80 | 0x00; */
  /* *BSC1_FIFO = 0x40; */
  /* *BSC1_FIFO = 'h'; */
  /* *BSC1_FIFO = 'e'; */
  /* *BSC1_FIFO = 'l'; */
  /* *BSC1_FIFO = 'l'; */
  /* *BSC1_FIFO = 'o'; */

  /* *BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN; */

  /* while (!(*BSC1_S & BSC_S_DONE)) */
  /*   ; */

  /* *BSC1_C &= ~BSC_C_I2CEN_EN; */

  /* *INTERRUPT_DISABLE_BASIC_IRQS = 0xffffffff; */
  /* *INTERRUPT_DISABLE_IRQS1 = 0xffffffff; */
  /* *INTERRUPT_DISABLE_IRQS2 = 0xffffffff; */
  /* *INTERRUPT_FIQ_CONTROL = 0; */

  // *INTERRUPT_ENABLE_BASIC_IRQS = 0x01;

  /* *TIMER_CONTROL &= 0xffffff00; */

  /* *TIMER_PREDIVIDER = 0x000000F9; */
  /* *TIMER_LOAD = 4000000 - 1; */
  /* *TIMER_RELOAD = 4000000 - 1; */
  /* *TIMER_IRQ_CLR = 0; */
  /* *TIMER_CONTROL |= 0x00000A2; */

  /* *INTERRUPT_ENABLE_BASIC_IRQS = 0x01; */
  /* enable_IRQ(); */

  pinMode(GPIO_SPI0_CE0, GPIO_MODE_ALT0);
  pinMode(GPIO_SPI0_MISO, GPIO_MODE_ALT0);
  pinMode(GPIO_SPI0_MOSI, GPIO_MODE_ALT0);
  pinMode(GPIO_SPI0_SCLK, GPIO_MODE_ALT0);

  printf("gpio settting GPIO_GPFSEL0:%08x\n", *GPIO_GPFSEL0); /* 00000 */
  printf("gpio settting GPIO_GPFSEL1:%08x\n", *GPIO_GPFSEL1); /* 24000 */

  *SPI0_CS = 0;
  *SPI0_CS |= SPI0_CS_CSPOL0_LOW | SPI0_CS_CS_CS0;
  *SPI0_CS |= SPI0_CS_CLEAR_ALL;
  *SPI0_CLK = 0;
  *SPI0_CS |= SPI0_CS_MODE2;

  /* printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /\* 50084 *\/ */

  /* while (!(*SPI0_CS & SPI0_CS_TXD_MASK)) { */
  /* }; */
  /* *SPI0_FIFO = 0x54; */

  /* while (!(*SPI0_CS & SPI0_CS_DONE_MASK)) { */
  /* }; */
  /* printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /\* 50084 *\/ */

  /* *SPI0_CS &= ~SPI0_CS_TA_ACTIVE; */

  /* delay(50); */

  *SPI0_CS |= SPI0_CS_TA_ACTIVE;

  while (!(*SPI0_CS & SPI0_CS_TXD_MASK)) {
  };
  *SPI0_FIFO = 0xFF;
  *SPI0_FIFO = 0xFF;
  *SPI0_FIFO = 0xFF;
  *SPI0_FIFO = 0xFF;

  while (!(*SPI0_CS & SPI0_CS_DONE_MASK)) {
  };
  printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /* 50084 */

  *SPI0_CS &= ~SPI0_CS_TA_ACTIVE;

  delay(50);

  *SPI0_CS |= SPI0_CS_TA_ACTIVE;

  while (!(*SPI0_CS & SPI0_CS_TXD_MASK)) {
  };
  printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /* 50084 */

  *SPI0_FIFO = ADT7310_ADDR_CONFIG | ADT7310_CMD_WRITE;
  *SPI0_FIFO = 0x80;

  while (!(*SPI0_CS & SPI0_CS_DONE_MASK)) {
  };
  printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /* 50084 */

  *SPI0_CS &= ~SPI0_CS_TA_ACTIVE;

  delay(500);

  *SPI0_CS |= SPI0_CS_TA_ACTIVE;

  while (!(*SPI0_CS & SPI0_CS_TXD_MASK)) {
  };
  printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /* 50084 */

  printf("SEND DATA:0x%02x\r\n", ADT7310_ADDR_TMP | ADT7310_CMD_READ | ATD7310_CMD_CONTINUOUS);

  *SPI0_FIFO = ADT7310_ADDR_TMP | ADT7310_CMD_READ | ATD7310_CMD_CONTINUOUS;

  while (!(*SPI0_CS & SPI0_CS_DONE_MASK))
    ;
  printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /* 50084 */

  *SPI0_CS &= ~SPI0_CS_TA_ACTIVE;

  delay(500);

  printf("START@%s:%s\n", __DATE__, __TIME__);

  while (1) {
    int8_t str[256];
    uint64_t t = micros();
    sprintf(str, "sysclock %lld (us)\n", t);
    printf("%s", str);
    delay(SLEEP_MS);

    printf("SPI0 CS register(%p) 0x%08x\n", SPI0_CS, *SPI0_CS); /* 50084 */

    /* printf("SPI0 CS register 0x%08x\n", *SPI0_CS); /\* 50084 *\/ */

    *SPI0_CS |= SPI0_CS_CLEAR_ALL;

    *SPI0_CS |= SPI0_CS_TA_ACTIVE;

    /* *SPI0_FIFO = 0; */
    /* while (!(*SPI0_CS & SPI0_CS_RXD_MASK)) */
    /*   ; */
    /* uint8_t ret = *SPI0_FIFO; */
    /* printf("RECEIVED %d\r\n", (int)ret); */
    /* uint32_t rawtemp = ret; */
    /* rawtemp <<= 8; */

    /* *SPI0_FIFO = 0; */
    /* while (!(*SPI0_CS & SPI0_CS_RXD_MASK)) */
    /*   ; */
    /* ret = *SPI0_FIFO; */
    /* rawtemp |= ret; */
    /* double temp = (int)rawtemp / 128.0; */
    /* printf("hex 0x%04x\r\n", rawtemp); */
    /* printf("Temp %f\r\n", temp); */

    *SPI0_FIFO = 0;
    while (!(*SPI0_CS & SPI0_CS_RXD_MASK))
      ;
    printf("SPI0 CS register(%p) 0x%08x\n", SPI0_CS, *SPI0_CS); /* 50084 */

    uint8_t ret = *SPI0_FIFO;
    printf("RECEIVED %d\r\n", (int)ret);
    uint32_t rawtemp = ret;

    rawtemp <<= 8;

    *SPI0_FIFO = 0;
    while (!(*SPI0_CS & SPI0_CS_RXD_MASK))
      ;
    printf("SPI0 CS register(%p) 0x%08x\n", SPI0_CS, *SPI0_CS); /* 50084 */

    ret = *SPI0_FIFO;
    printf("RECEIVED %d\r\n", (int)ret);
    rawtemp |= ret;
    printf("SPI0 CS register(%p) 0x%08x\n", SPI0_CS, *SPI0_CS); /* 50084 */

    while (!(*SPI0_CS & SPI0_CS_DONE_MASK))
      ;

    *SPI0_CS &= ~SPI0_CS_TA_ACTIVE;

    double temp = (int)rawtemp / 128.0;
    printf("hex 0x%04x\r\n", rawtemp);
    printf("Temp %f\r\n", temp);
  }

  return 0;
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_vector(void)
{
  while (1) {
    printf("undefined\n");
  }
}

void __attribute__((interrupt("SWI"))) software_interrupt_vector(void)
{
  while (1) {
    printf("swi\n");
  }
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_vector(void)
{
  printf("prefech abort\n");
}

void __attribute__((interrupt("ABORT"))) data_abort_vector(void)
{
  printf("abort\n");
}

void __attribute__((interrupt("IRQ"))) interrupt_vector(void)
{
  printf("irq\n");
  IRQ_handler();
  return;
}

void __attribute__((interrupt("FIQ"))) fast_interrupt_vector(void)
{
  printf("fiq\n");
}
