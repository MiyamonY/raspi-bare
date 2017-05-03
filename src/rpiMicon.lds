OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY {
       rom        (rx): ORIGIN = 0x01000000, LENGTH = 1M
       ram        (rwx): ORIGIN = 0x02000000, LENGTH = 1M
       peripheral (rw): ORIGIN = 0x3F000000, LENGTH = 0x01000000

}

SECTIONS {

         .text : { *(.text*) } > rom
         . = ALIGN(4);

         __rodata_start = .;
         .rodata : { *(.data*) } > rom
         . = ALIGN(4);
         __rodata_end = .;

         __data_start = .;
         .data : { *(.data*) } > ram
         . = ALIGN(4);
         __data_end = .;

         __bss_start = .;
         .bss : { *(.bss*) } > ram
         . = ALIGN(4);
         __bss_end = .;

         .peripheral_gpio 0x3F200000 (NOLOAD):
         {
            KEEP(*(.peripheral_gpio*))
         } > peripheral
}
