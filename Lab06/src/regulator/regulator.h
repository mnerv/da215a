/**
 * regulator.h
 *
 * Read the potentiometer using ADC
 *
 * Created: 05-01-2021
 */

#ifndef REGULATOR_H_
#define REGULATOR_H_

#include <inttypes.h>

/**
 * Initialize the ADC to read the potentiometer values.
 */
void regulator_init();

/**
 * Read the value from the regulator
 *
 * @return Value from 0 - 100.
 */
uint8_t read_regulator();

#endif /* REGULATOR_H_ */