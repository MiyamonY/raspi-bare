CROSS = arm-unknown-eabi-

CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

LINKER_SCRIPT = rpiMicon.lds
STARTUP = startup.o
OBJS = main.o

OBJS += rpi_lib/rpi_init.o rpi_lib/bss/clearbss.o
TARGET = kernel

CFLAGS = -mfloat-abi=soft -mlittle-endian
CFLAGS += -nostdinc -fno-builtin
CFLAGS += -O2
CFLAGS += -I$(shell pwd)
LDFLAGS = -static -nosdtlib

.PHONY: clean tags

all: ${TARGET}.img

${TARGET}.elf : $(STARTUP) $(OBJS)
	$(LD) $(LDFLAGS) -T $(LINKER_SCRIPT) $^ `$(CC) -print-libgcc-file-name` -o $@

.SUFFIXES: .elf .img

.elf.img:
	$(OBJCOPY) -O binary $< $@

clean:
	$(RM) -f *.o *.img *.elf */*/*.o
	$(RM) -f tags *~

tags:
	ctags *.[chS]
