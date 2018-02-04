CROSS=arm-unknown-eabi-

CC=$(CROSS)gcc
LD=$(CROSS)ld
OBJCOPY=$(CROSS)objcopy
LINKER_SCRIPT=raspi.lds

STARTUP=startup.o

FILES = * lib/* lib/bss/* lib/gpio/* lib/reg/* lib/system_timer/* lib/uart/*
OBJS= $(foreach files, $(FILES), $(patsubst %.c, %.o, $(filter %.c ,$(wildcard $(files)))))
CFLAGS=-mfloat-abi=soft -mlittle-endian
CFLAGS+=-I. -nostdinc -fno-builtin
CFLAGS+=-O2

LDFLAGS=-static -nostdlib -T $(LINKER_SCRIPT)

all: kernel.img

kernel.elf: $(STARTUP) $(OBJS) $(LINKER_SCRIPT)
	$(LD) $(LDFLAGS) $^ `$(CC) -print-libgcc-file-name` -o $@

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
