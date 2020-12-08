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

#define F_CPU 16000000UL
#include <util/delay.h>

// #include "guess_nr.h"
// #include "hmi/hmi.h"
// #include "random/random.h"

int main(void) {
    DDRC = 0x80;

    while (1) {
        PORTC = 0x80;  // 0b10000000 = 128
        _delay_ms(200);
        PORTC = 0x00;
        _delay_ms(250);
    }

    return 0;
}