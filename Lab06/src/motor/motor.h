/**
 * motor.h
 *
 * Control the motor speed using PWM
 *
 * Created: 05-01-2021
 */
#ifndef MOTOR_H_
#define MOTOR_H_

#include "avr/io.h"
#include "common.h"

/**
 * Intialize the PWM for the motor
 */
void motor_init();

#endif