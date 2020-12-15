/*
 * random.c
 *
 * These are functions for generating pseudo-number numbers, which depends on
 * standard C libraries and the ADC. The ADC (analog pin A5) is used to provide
 * a seed number, since the noise from an unconnected pin is naturally random.
 * IMPORTANT! Don't connect anything to analog pin A5!!!
 *
 * To generate a random number:
 *  1. run random_seed() - no more than once!
 *  2. run random_get_nr() each time you want a new random number
 *
 * Author:  Mathias Beckius
 *
 * Date:    2014-11-28
 */

#include "random.h"
#include <avr/io.h>
#include <stdlib.h>

static void init_adc(void);
static uint16_t read_adc(void);

/**
 * Initialize the ADC.
 */
static void init_adc(void) {
    // set reference voltage (internal 5V), select ADC0 channel (A5)
    ADMUX = (1 << REFS0);
    // right adjustment of ADC result, prescaler 128
    ADCSRA = 7;
    // enable ADC
    ADCSRA = (1 << ADEN);
    // disable digital input on ADCO
    DIDR0 = 1;
}

/**
 * Read the ADC to get a random number.
 *
 * @return The analog value
 */
static uint16_t read_adc(void) {
    // start conversion
    ADCSRA |= (1 << ADSC);
    // wait until conversion is finished
    while ((ADCSRA & (1 << ADIF)) == 0)
        ;
    // read and return ADC value
    return ((ADCH << 8) | ADCL);
}

/**
 * Generates a seed for the pseudo-random number generator.
 * This function should only be run once!
 */
void random_seed(void) {
    init_adc();
    srandom(read_adc());
}

/**
 * Generate a pseudo-random number.
 *
 * @param max specifies the range of integers
 *
 * @return random number between 0-(max-1)
 */
uint16_t random_get_nr(uint16_t max) {
    if (max == 0) { return 0; }

    return (random() % max);
}