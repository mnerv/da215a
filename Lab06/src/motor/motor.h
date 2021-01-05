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

/**
 * Set the motor speed
 *
 * @param[in] value 0 to 100
 */
void motor_set_speed(uint8_t value);

#endif