/*
 * numkey.c
 *
 * This is the device driver for the numeric keyboard.
 *
 * Author:  Mathias Beckius
 *
 * Date:    2014-11-28
 */

#include "numkey.h"
#include "common.h"
#include "delay/delay.h"
#include <avr/io.h>
#include <inttypes.h>

/*
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

/*
 * Initialization of the numeric keyboard.
 * This function configures the ports and pins to be used by the keyboard.
 */
void numkey_init(void) {
    // PE6 (D7) as input (key pressed?)
    DDRE = 0x00;
    // PB4-PB7 (D8-D11) as outputs (MUX and decoder)
    DDRB = 0xF0;
}

/*
 * Read keyboard.
 * If a key is pressed, then the corresponding character
 * is returned:
 *  If '1' is pressed, then the character '1' is returned.
 * Otherwise a NO_KEY character is returned.
 * Important! Due to MUX propagation delay and button bounce, it's necessary
 * to generate a delay (after setting column and row) before reading the pin.
 *
 * return:
 *  If a key is pressed, then a character that represents the key is
 *returned. Otherwise, a NO_KEY character is returned!
 */
char numkey_read(void) {
    uint8_t i;
    /* UPPGIFT: skriv en for-sats som stegar igenom alla tangenter, använd
     * variabeln i. */
    {
        // set column and row
        // UPPGIFT: använd SET_BIT_LEVELS() för att sätta bitar i registret
        // PORTB! wait before reading pin
        delay_ms(1);
        // if key was pressed...
        if (1) { // UPPGIFT: skriv om det logiska uttrycket i if-satsen, så att
                 // uttrycket blir sant om bit 6 i PINE är 1.
            return key_map[i];
        }
    }
    // no key was pressed!
    return NO_KEY;
}