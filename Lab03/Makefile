CC=avra

all: main.hex

# Clean and assemble
rebuild: clean all

# For macOS
USBPORT+=$(shell ls /dev/tty.usbmodem*)

# Assemble the code
main.hex: main.asm delay.inc dice.inc keyboard.inc lcd.inc monitor.inc stat_data.inc stats.inc
	$(CC) main.asm

# Upload to the board
install: main.hex
	avrdude -v -p atmega32u4 -c avr109 -P ${USBPORT} -b 115200 -D -U flash:w:./main.hex:i

clean:
	rm -f *.hex *.obj