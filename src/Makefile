CROSS = arm-unknown-eabi-

CC = $(CROSS)gcc
LD = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

LINKER_SCRIPT = rpiMicon.lds
STARTUP = startup.o

OBJS = main.o
OBJS += rpi_lib/rpi_init.o rpi_lib/bss/clearbss.o rpi_lib/timer/rpi_timer.o rpi_lib/delay/rpi_delay.o\
	rpi_lib/gpio/rpi_gpio.o rpi_lib/serial/rpi_serial.o syscall.o

LIBS += -L/home/raspi/cross/rpi/arm-unknown-eabi/lib/gcc/arm-unknown-eabi/4.8.1/
LIBS += -L/home/raspi/cross/rpi/arm-unknown-eabi/arm-unknown-eabi/lib

TARGET = kernel

CFLAGS = -mfloat-abi=soft -mlittle-endian
CFLAGS += -fno-builtin
CFLAGS += -O2 -std=gnu99
CFLAGS += -I$(shell pwd)
LDFLAGS = -static

.PHONY: clean tags

all: ${TARGET}.img

${TARGET}.elf : $(STARTUP) $(OBJS)
	$(LD) $(LDFLAGS) -T $(LINKER_SCRIPT) $^ `$(CC) -print-libgcc-file-name` -o $@ \
		$(LIBS) -lc -lgcc

.SUFFIXES: .elf .img

.elf.img:
	$(OBJCOPY) -O binary $< $@

clean:
	$(RM) -f *.o *.img *.elf */*/*.o
	$(RM) -f tags *~

tags:
	ctags *.[chS]
