/**
 * regulator.c
 *
 * Created: 05-01-2021
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"

/**
 * For storage of ADC value from temperature sensor.
 * Initial value is good to use before A/D conversion is configured!
 */
static volatile uint8_t adc = 117;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect) {
    // read ADC value
    adc = ADCH;
}

void regulator_init() {
    ADMUX |= ((0 << REFS1) | (1 << REFS0));  // set reference voltage
                                             // (internal 5V

    ADMUX |=
        (0 << MUX4) | (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (1 << MUX0);

    ADMUX |= (1 << ADLAR);  // Set to 8-bit reading mode

    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // prescaler 128
    ADCSRA |= (1 << ADATE);  // enable Auto Trigger
    ADCSRA |= (1 << ADIE);   // enable Interrupt
    ADCSRA |= (1 << ADEN);   // enable ADC

    // disable digital input on ADC0 and ADC1
    DIDR0 = 3;

    // disable USB controller (to make interrupts possible)
    USBCON = 0;

    // enable global interrupts
    sei();

    // start initial conversion
    ADCSRA |= (1 << ADSC);
}

uint8_t read_regulator() { return adc * 100 / 255; }