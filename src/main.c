#include "rpi_lib/rpi.h"
#include <stdio.h>

#define SLEEP_MS 1000
#define UART_BAURATE 115200

#define BSC1_BASE (0x00804000)
#define BSC1_C PHY_PERI_ADDR(BSC1_BASE + 0x00)
#define BSC1_S PHY_PERI_ADDR(BSC1_BASE + 0x04)
#define BSC1_DLEN PHY_PERI_ADDR(BSC1_BASE + 0x08)
#define BSC1_A PHY_PERI_ADDR(BSC1_BASE + 0x0C)
#define BSC1_FIFO PHY_PERI_ADDR(BSC1_BASE + 0x10)
#define BSC1_DIV PHY_PERI_ADDR(BSC1_BASE + 0x14)
#define BSC1_DEL PHY_PERI_ADDR(BSC1_BASE + 0x18)
#define BSC1_CLKT PHY_PERI_ADDR(BSC1_BASE + 0x1C)

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

#define PCF8574_ADDR 0x27 // or 0x3F
#define MPU6050_ADDR 0x68

#define BSC1_SDA1_PIN 2
#define BSC1_SCL1_PIN 3

int main(void)
{
  rpi_init();

  pinMode(GPIO_ACT_PIN, GPIO_MODE_OUTPUT);
  pinMode(BSC1_SDA1_PIN, GPIO_MODE_ALT0);
  pinMode(BSC1_SCL1_PIN, GPIO_MODE_ALT0);

  digitalWrite(GPIO_ACT_PIN, GPIO_HIGH);
  Serial_begin(UART_BAURATE);
  printf("PROGRAM START\n");

  *BSC1_DIV = 0;

  *BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
  *BSC1_A = MPU6050_ADDR;
  *BSC1_C &= ~BSC_C_READ_READ;
  *BSC1_C |= BSC_C_CLEAR_ALL;
  *BSC1_DLEN = 1;
  *BSC1_FIFO = 0x75; /* who am i */

  *BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;

  delay(250);

  printf("write addr...\n");

  while (!(*BSC1_S & BSC_S_DONE))
    ;

  *BSC1_S = BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE;
  *BSC1_A = MPU6050_ADDR;
  *BSC1_C |= BSC_C_READ_READ;
  *BSC1_C |= BSC_C_CLEAR_ALL;
  *BSC1_DLEN = 1;
  *BSC1_C |= BSC_C_I2CEN_EN | BSC_C_ST_EN;

  while (!(*BSC1_S & BSC_S_DONE))
    ;
  printf("received data is %u\n", (uint8_t)*BSC1_FIFO);
  /* *BSC1_A = PCF8574_ADDR; */

  /* *BSC1_C &= ~BSC_C_READ_READ; */
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

  /* *BSC1_A = PCF8574_ADDR; */

  /* *BSC1_C &= ~BSC_C_READ_READ; */
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

  while (1) {
    int8_t str[256];
    uint64_t t = micros();
    sprintf(str, "sysclock %lld (us)\n", t);
    printf("%s", str);
    delay(SLEEP_MS);
  }

  return 0;
}
