/**
 * main.c
 *
 * Author: Pratchaya Khansomboon, Ademir Zjajo
 *
 * Created: 05-01-2021
 */

#include <avr/io.h>
#include <stdio.h>

#include "hmi/hmi.h"
#include "regulator/regulator.h"
#include "delay/delay.h"

int main() {
    // TODO: Sate machine, MOTOR_OFF, MOTOR_ON, MOTOR_RUNNING
    // key == 1 = motor off
    // key == 2 && regulator == 0  = motor on.

    hmi_init();
    regulator_init();

    char buffer[16];

    uint8_t prev_reg, cur_reg;

    while (1) {
        // prev_key = key;
        // key = numkey_read();
        prev_reg = cur_reg;
        cur_reg = read_regulator();

        sprintf(buffer, "%u", read_regulator());

        if (prev_reg != cur_reg) {
            output_msg("Value:", &buffer, 0);
            delay_ms(100);
        }

        // if (prev_key != key) {
        //     switch (key) {
        //         case '2':  // 2 && regulator == 0
        //             next_state = SHOW_MOTOR_ON;
        //             break;
        //         case '1':
        //             next_state = SHOW_MOTOR_OFF;
        //          case '1'    // regulator > 0
        //              next_state = SHOW_MTOR_RUNNING
        //         default:
        //             break;
        //     }
        // }
    }
    return 0;
}
