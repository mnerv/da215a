/*
 * temp.c
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:  Mathias Beckius, Pratchaya Khansomboon
 *
 * Date:    2014-12-07
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "temp.h"

/**
 * For storage of ADC value from temperature sensor.
 * Initial value is good to use before A/D conversion is configured!
 */
static volatile uint16_t adc = 221;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect) {
    // read ADC value
    uint8_t low = ADCL;
    uint8_t high = ADCH;

    adc = (high << 8) + low;
}

/*
 * Initialize the ADC and ISR.
 */
void temp_init(void) {
    ADMUX |= ((0 << REFS1) | (1 << REFS0));  // set reference voltage
                                             // (internal 5V)

    ADMUX |= (0 << MUX4) | (1 << MUX3) | (0 << MUX2) | (0 << MUX1) |
             (1 << MUX0);  // select diff.amp 10x on ADC0 & ADC1
                           // right adjustment of ADC value

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

/*
 * @return The temperature in Celcius
 */
uint8_t temp_read_celsius(void) {
    uint16_t adc_correction = adc * 98;
    uint16_t temp = adc_correction / 1000;
    // round up?
    if ((adc_correction % 1000) >= 500) { temp++; }
    return (uint8_t)temp;
}

/*
 * @return The temperature in Fahrenheit.
 */
uint8_t temp_read_fahrenheit(void) {
    uint16_t convert = ((temp_read_celsius() * 90) / 5) + 320;
    uint16_t temp = convert / 10;
    // round up?
    if ((convert % 10) >= 5) { temp++; }
    return (uint8_t)temp;
}