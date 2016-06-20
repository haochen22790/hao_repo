include sources.mk

TARGET := project
TARGET_MAP := $(TARGET).map
LDFLAGS := -Wl,-Map=$(TARGET_MAP)
CFLAGS := -g -O0 -Wall -std=c99

ifndef BUILD_TARGET
BUILD_TARGET := native
endif

ifeq ($(BUILD_TARGET),arm)
CC := arm-linux-gnueabihf-gcc
else
CC := gcc
endif

.PHONY: build
build: $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)
	size $(TARGET)

.PHONY: main.o
main.o: main.c project_1.h
	$(CC) -c main.c $(CFLAGS)

.PHONY: memory.o
memory.o: memory.c memory.h
	$(CC) -c memory.c $(CFLAGS)

.PHONY: project_1.o
project_1.o: project_1.c project_1.h
	$(CC) -c project_1.c $(CFLAGS)

.PHONY: compile-all
compile-all: main.c memory.c memory.h project_1.c project_1.h
	$(CC) -c $(SRCS) $(CFLAGS)

.PHONY: %.s
%.s: %.c
	$(CC) -S -o $@ $<

.PHONY: %.asm
%.asm: %.o
	objdump -S --disassemble $< > $@

.PHONY: upload
upload:
	scp $(TARGET) root@192.168.7.2:/home/debian/bin

.PHONY: clean
clean:
	rm $(TARGET) *.o *.asm *.s *.map *.out



