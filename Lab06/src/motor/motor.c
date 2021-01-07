/**
 * motor.c
 *
 * Created: 2021-01-05
 */

#include "motor.h"

void motor_init() {
    SET_BIT(DDRC, PC6);  // set Digital pin 5 as output

    TCCR3A |= (1 << WGM30);
    TCCR3B |= (1 << WGM32);

    TCCR3A |= (1 << COM3A1) | (0 << COM3A0);
    TCCR3B |= (~(1 << CS32) & ((1 << CS31) | (1 << CS30)));
}

void motor_set_speed(uint8_t duty) { OCR3A = duty * 255 / 100; }