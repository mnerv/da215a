/*
 * This lab assignment is an introduction to C programming for
 * embedded systems. The purpose of this assignment is to learn:
 *  - how to mix C and Assembly code
 *  - how device drivers can be written in C
 *  - how a simple user interface (HMI) can be implemented
 *  - the benefits of following a consistent way of programming
 *  - etc....
 *
 * The final goal of this assignment is to complete a little game
 * called "Guess the number", where the player shall guess a random
 * number between 1-100.
 *
 * Author: Mathias Beckius
 *
 * Date: 2014-12-01
 */

#include <avr/io.h>

// #include "common.h"
// #include "guess_nr.h"
// #include "hmi/hmi.h"
// #include "random/random.h"
#include "lcd/lcd.h"
#include "numkey/numkey.h"

int main(void) {
    numkey_init();
    lcd_init();
    lcd_write_str("Hello, World!");
    lcd_set_cursor_pos(1, 0);

    char prev_key;
    char key;

    while (1) {
        prev_key = key;
        key = numkey_read();
        if (key != NO_KEY && key != prev_key) lcd_write(DATA, key);
    }

    return 0;
}