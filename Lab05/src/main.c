/**
 * Author: Pratchaya Khansomboon, Ademir Zjajo
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

    output_msg("Hello there", "", 0);

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

        if (current_state != next_state) current_state = next_state;

        switch (current_state) {
            case SHOW_TEMP_C:
                sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
                break;
            case SHOW_TEMP_F:
                sprintf(temp_str, "%u%cF", temp_read_celsius(), 0xDF);
                break;
            case SHOW_TEMP_CF:
                sprintf(temp_str, "%u%cCF", temp_read_celsius(), 0xDF);
                break;
        }

        // if (prev_key == key) continue;

        output_msg("Temp", &temp_str, 0);
    }

    return 0;
}
