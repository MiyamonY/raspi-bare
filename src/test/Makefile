TARGET = test
VPATH := ../rpi_lib/gpio
objs := $(patsubst %.c,%.o,$(wildcard *.c))
objs += rpi_gpio.o
LDFLAGS += -lcriterion
CFLAGS += -I..
CC = gcc

.PHONY:test

test: $(objs)
	$(CC) -o $(TARGET) $(CFLAGS) $(LDFLAGS) $^
