/**
 * motor.c
 *
 * Created: 05-01-2021
 */

#include "motor.h"

void motor_init() {
    SET_BIT(DDRC, PC6);
    TCCR3A |= (1 << WGM30);
    TCCR3B |= (1 << WGM32);

    TCCR3A |= (1 << COM3A1) | (0 << COM3A0);
    TCCR3B |= (1 << CS31) | (1 << CS30);
}

void motor_set_speed(uint8_t value) { OCR3A = value * 255 / 100; }