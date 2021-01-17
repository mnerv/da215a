/**
 * main.c
 *
 * Measure the temperature and display it on the LCD
 *
 * Author: Pratchaya Khansomboon, Ademir Zjajo
 *
 * Created: 15-12-2020
 */

#include <avr/io.h>
#include <stdio.h>

#include "numkey/numkey.h"
#include "temp/temp.h"
#include "hmi/hmi.h"

int main() {
    state_t current_state = SHOW_TEMP_C, next_state = SHOW_TEMP_C;

    char temp_str[16];  // String for temperature output

    char prev_key;
    char key;

    hmi_init();
    temp_init();

    while (1) {
        prev_key = key;
        key = numkey_read();

        if (prev_key != key) {
            switch (key) {
                case '1':
                    next_state = SHOW_TEMP_C;
                    break;
                case '2':
                    next_state = SHOW_TEMP_F;
                    break;
                case '3':
                    next_state = SHOW_TEMP_CF;
                    break;
            }
        }

        // Update the state
        current_state = next_state;

        switch (current_state) {
            case SHOW_TEMP_C:
                sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
                break;
            case SHOW_TEMP_F:
                sprintf(temp_str, "%u%cF", temp_read_fahrenheit(), 0xDF);
                break;
            case SHOW_TEMP_CF:
                sprintf(temp_str, "%u%cC, %u%cF", temp_read_celsius(), 0xDF,
                        temp_read_fahrenheit(), 0xDF);
                break;
        }

        output_msg("Temp", &temp_str, 0);
    }

    return 0;
}
