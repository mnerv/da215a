# compiler options
CC = avr-gcc
MCU = atmega32u4
CFLAGS = -Wall -g -Os -mmcu=$(MCU) -I./src

# Get OS, only for macOS and Linux
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	USBPORT+=$(shell ls /dev/ttyACM*)
endif
ifeq ($(UNAME_S),Darwin)
	USBPORT+=$(shell ls /dev/tty.usbmodem*)
endif

all: main.hex size

rebuild: clean all

main.hex: main.elf
	avr-objcopy -O ihex -j .text -j .data $< $@

# Linking
main.elf: main.o 
	$(CC) $(CFLAGS) $^ -o $@

# ---------------------------------------------------------------- 
# Compile to object file no link
# ---------------------------------------------------------------- 
main.o: ./src/main.c
	$(CC) $(CFLAGS) -c ./src/main.c

# Upload to the board
install: main.hex
	avrdude -v -p atmega32u4 -c avr109 -P ${USBPORT} -b 115200 -D -U flash:w:$<:i

force_install:
	avrdude -v -p atmega32u4 -c avr109 -P ${USBPORT} -b 115200 -D -U flash:w:main.hex:i

# Get program size
size: main.elf
	@avr-size --format=avr --mcu=$(MCU) -C $<

clean:
	rm -f *.hex *.o *.elf *.lst