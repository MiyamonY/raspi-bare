OUTPUT_ARCH(arm)
ENTRY(vector)

MEMORY
{
  rom        (rx): ORIGIN = 0x00008000, LENGTH = 1M
  ram        (rw): ORIGIN = 0x01008000, LENGTH = 1M
  peripheral (rw): ORIGIN = 0x3F000000, LENGTH = 10M
}

SECTIONS
{
  .text : {
    *(.text*)
  } > rom

  .rodata : {
    *(.data*)
  } > rom

  .data : {
    *(.data*)
  } > ram

  __bss_start = LOADADDR(.bss);
  .bss : {
    *(.bss*)
  } > ram
  __bss_end = LOADADDR(.bss) + SIZEOF(.bss);

  .peripheral_system_timer 0x3F003000 (NOLOAD):{
    *(.peripheral_system_timer)
  } > peripheral

  .peripheral_interrupt 0x3F00B200 (NOLOAD):{
    *(.peripheral.interrupt)
  } > peripheral

  .peripheral.timer0 0x3F00B400 (NOLOAD):{
    *(.peripheral.timer)
  } > peripheral

  .peripheral_gpio 0x3F200000 (NOLOAD): {
    *(.peripheral_gpio)
  } > peripheral

  .peripheral_uart 0x3F201000 (NOLOAD):{
    *(.peripheral_uart)
  } > peripheral

  .peripheral_spi 0x3F204000 (NOLOAD):{
    *(.peripheral_spi0)
  } > peripheral
}
