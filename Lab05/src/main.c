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

    while (1) {
        prev_key = key;
        key = numkey_read();

        if (prev_key == key) continue;

        if (key == NO_KEY || key == '1') {
            sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
        } else if (key == NO_KEY || key == '2') {
            sprintf(temp_str, "%u%cF", temp_read_celsius(), 0xDF);
        } else if (key == NO_KEY || key == '3') {
            sprintf(temp_str, "%u%cCF", temp_read_celsius(), 0xDF);
        }

        output_msg("Temp", &temp_str, 0);
    }

    return 0;
}
