/*
 * random.h
 *
 * These are functions for generating pseudo-number numbers.
 *
 * Author: Mathias Beckius
 *
 * Date: 2014-11-28
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <inttypes.h>

void random_seed(void);
uint16_t random_get_nr(uint16_t);

#endif /* RANDOM_H_ */