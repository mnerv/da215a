/*
 * numkey.c
 *
 * This is the device driver for the numeric keyboard.
 *
 * Author:  Mathias Beckius, Pratchaya Khansomboon
 *
 * Date:    2014-11-28
 */

#include "numkey.h"
#include "common.h"
#include "delay/delay.h"
#include <avr/io.h>
#include <inttypes.h>

/**
 * Key mapping table for the numeric keyboard.
 * The positions are defined a 4-bit address. The 4 MSB's represents the
 * keyboard's columns, the 4 LSB's represents the keyboards rows:
 * Example:
 *    col 0, row 0 (binary 0000, decimal 0) is mapped to '1',
 *    col 1, row 0 (binary 0100, decimal 4) is mapped to '2'
 * The address corresponds to a position in the mapping table.
 */
static const char key_map[12] = {'1', '4', '7', '*', '2', '5',
                                 '8', '0', '3', '6', '9', '#'};

/**
 * Initialization of the numeric keyboard.
 * This function configures the ports and pins to be used by the keyboard.
 */
void numkey_init(void) {
    // PE6 (D7) as input (key pressed?)
    DDRE = 0x00;
    // PB4-PB7 (D8-D11) as outputs (MUX and decoder)
    DDRB = 0xF0;
}

/**
 * Read keyboard.
 *
 * @return If a key is pressed, then the corresponding character
 * is returned:
 *  If '1' is pressed, then the character '1' is returned.
 * Otherwise a NO_KEY character is returned.
 * Important! Due to MUX propagation delay and button bounce, it's necessary
 * to generate a delay (after setting column and row) before reading the pin.
 *
 * If a key is pressed, then a character that represents the key is
 * returned. Otherwise, a NO_KEY character is returned!
 */
char numkey_read(void) {
    uint8_t i;

    for (i = 0; i < 16; i++) {
        SET_BIT_LEVELS(PORTB, 0b00001111, i << 4);
        delay_ms(1);

        if (PINE & 0b01000000) {
            if (i < 12)
                return key_map[i];
            else
                return i;
        }
    }

    // no key was pressed!
    return NO_KEY;
}