# compiler options
CC = avr-gcc
MCU = atmega32u4
CFLAGS = -Wall -g -Os -mmcu=$(MCU) -I./src

# For macOS
USBPORT += $(shell ls /dev/tty.usbmodem*)

# For Linux only
# USBPORT+=$(shell ls /dev/ttyACM*)

all: main.hex

rebuild: clean all

main.hex: main.elf
	avr-objcopy -O ihex -j .text -j .data $< $@

# Linking
main.elf: main.o guess_nr.o random.o numkey.o lcd.o hmi.o delay_asm.o
	$(CC) $(CFLAGS) $^ -o $@

# ---------------------------------------------------------------- 
# Compile to object file no link
# ---------------------------------------------------------------- 
main.o: ./src/main.c ./src/common.h
	$(CC) $(CFLAGS) -c ./src/main.c

guess_nr.o: ./src/guess_nr.c ./src/guess_nr.h
	$(CC) $(CFLAGS) -c ./src/guess_nr.c

random.o: ./src/random/random.c ./src/random/random.h
	$(CC) $(CFLAGS) -c ./src/random/random.c

numkey.o: ./src/numkey/numkey.c ./src/numkey/numkey.h
	$(CC) $(CFLAGS) -c ./src/numkey/numkey.c

lcd.o: ./src/lcd/lcd.c ./src/lcd/lcd.h
	$(CC) $(CFLAGS) -c ./src/lcd/lcd.c

hmi.o: ./src/hmi/hmi.c ./src/hmi/hmi.h
	$(CC) $(CFLAGS) -c ./src/hmi/hmi.c

# delay.o: ./src/delay/delay.c ./src/delay/delay.h
# 	$(CC) $(CFLAGS) -c ./src/delay/delay.c

delay_asm.o: ./src/delay/delay_asm.S ./src/delay/delay.h
	$(CC) $(CFLAGS) -c ./src/delay/delay_asm.S

# Upload to the board
install: main.hex
	avrdude -v -p atmega32u4 -c avr109 -P ${USBPORT} -b 115200 -D -U flash:w:./main.hex:i

# Get program size
size: main.elf
	@avr-size --mcu=$(MCU) -C $<

clean:
	rm -f *.hex *.o *.elf *.lst