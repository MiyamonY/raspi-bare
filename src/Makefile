CROSS=arm-unknown-eabi-

CC=$(CROSS)gcc
LD=$(CROSS)ld
OBJCOPY=$(CROSS)objcopy
LINKER_SCRIPT=raspi.lds

STARTUP=startup.o

FILES = * lib/* lib/bss/* lib/gpio/* lib/reg/* lib/system_timer/* lib/uart/* lib/system_call/* lib/spi/*
OBJS= $(foreach files, $(FILES), $(patsubst %.c, %.o, $(filter %.c ,$(wildcard $(files)))))
CFLAGS=-mfloat-abi=soft -mlittle-endian
CFLAGS+=-I. -nostartfiles -Wall
CFLAGS+=-O2

LD_LIBRARY = -L/home/raspi/cross/rpi/arm-unknown-eabi/arm-unknown-eabi/lib
LD_LIBRARY += -L/home/raspi/cross/rpi/arm-unknown-eabi/lib/gcc/arm-unknown-eabi/6.3.0/
LDFLAGS=-static -nostartfiles -T $(LINKER_SCRIPT)
LIBS = -lc -lgcc

all: kernel.img

kernel.elf: $(STARTUP) $(OBJS) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) $^ -o $@ $(LD_LIBRARY) $(LIBS)

.SUFFIXES: .elf .img

%.img: %.elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC)	$(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f *.img *.elf
	$(RM) -f $(OBJS)
tags:
	gtags *.[chS]
