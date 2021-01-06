/*
 * delay.h
 *
 * These delay functions are external assembly subroutines.
 * See 'delay_asm.S' for details.
 *
 * Author:  Mathias Beckius
 *
 * Date:    2014-11-29
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

/**
 * Delay 1 microsecond using the assembly.
 * This only works for 16 MHz clock.
 */
extern void delay_1_micros();

/**
 * Delay x amount of micro seconds using assembly.
 * This only works for 16 MHz clock.
 *
 * @param us Time in microseconds.
 */
extern void delay_micros(uint8_t us);

/**
 * Delay x amount of milliseconds. This function uses delay_micros to achieve ms
 * of delays.
 * This only works for 16 MHz clock.
 *
 * @param ms Time in milliseconds.
 */
extern void delay_ms(uint8_t ms);

/**
 * Delay x amount of seconds. This function uses delay_ms to achive second of
 * delays.
 * This only works for 16 MHz clock.
 *
 * @param s Time in seconds.
 */
extern void delay_s(uint8_t s);

#endif /* DELAY_H_ */