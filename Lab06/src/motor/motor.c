/**
 * motor.c
 *
 * Created: 2021-01-05
 */

#include "motor.h"

void motor_init() {
    SET_BIT(DDRC, PC6);  // set Digital pin 5 as output

    // Set the mode to Fast PWM 8-bit
    // The bits that needs to be set for these are WGM30 and WGM32
    // WGM31 bit needs to cleared
    TCCR3A |= (1 << WGM30);
    TCCR3A &= ~(1 << WGM31);
    TCCR3B |= (1 << WGM32);

    // Sets when the timer should be cleared
    TCCR3A |= (1 << COM3A1) | (0 << COM3A0);

    // Selects the prescalar for the timer counter
    // This set the mode to clkio/64, 16MHz/256/64 = 976 Hz
    TCCR3B |= (~(1 << CS32) & ((1 << CS31) | (1 << CS30)));
}

void motor_set_speed(uint8_t duty) { OCR3A = duty * 255 / 100; }