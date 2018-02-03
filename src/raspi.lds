OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
  rom        (rx): ORIGIN = 0x00008000, LENGTH = 1M
  ram        (rw): ORIGIN = 0x01008000, LENGTH = 1M
  peripheral (rw): ORIGIN = 0x3F000000, LENGTH = 0x01000000
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

  .peripheral 0x3F200000 (NOLOAD): {
    *(.peripheral_gpio)
  } > peripheral
}
