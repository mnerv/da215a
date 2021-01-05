/**
 * motor.c
 *
 * Created: 05-01-2021
 */

#include "motor.h"

void motor_init() {
    SET_BIT(DDRC, 1);

    // TCCR3A
    // TCCR3B
    //
}