/**
 * motor.h
 *
 * Control the motor speed using PWM
 *
 * Created: 2021-01-05
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
 * @param[in] duty Expects 0 to 100
 */
void motor_set_speed(uint8_t duty);

#endif