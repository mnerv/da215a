/**
 * main.c
 *
 * Author: Pratchaya Khansomboon, Ademir Zjajo
 *
 * Created: 2021-01-05
 */

#include <avr/io.h>
#include <stdio.h>

#include "hmi/hmi.h"
#include "regulator/regulator.h"
#include "delay/delay.h"
#include "motor/motor.h"

typedef enum state { MOTOR_OFF, MOTOR_ON, MOTOR_RUNNING } motor_state;

int main() {
    motor_state state = MOTOR_OFF;

    hmi_init();
    regulator_init();
    motor_init();

    char buffer1[16];
    char buffer2[16];

    char prev_key;
    char key;
    uint8_t cur_reg;

    while (1) {
        prev_key = key;
        key = numkey_read();
        cur_reg = read_regulator();

        // Check for button clicked
        if (prev_key != key) {
            if (key == '2' && cur_reg == 0) {
                state = MOTOR_ON;
            } else if (key == '1' && state == MOTOR_ON) {
                state = MOTOR_OFF;
            } else if (key == '1' && state == MOTOR_RUNNING) {
                state = MOTOR_OFF;
            }
        }

        // Determine what state we are in
        switch (state) {
            case MOTOR_OFF:
                sprintf(buffer1, "Motor off");
                motor_set_speed(0);
                break;
            case MOTOR_ON:
                if (cur_reg > 0) state = MOTOR_RUNNING;
                sprintf(buffer1, "Motor on");
                break;
            case MOTOR_RUNNING:
                sprintf(buffer1, "Motor running");
                motor_set_speed(cur_reg);
                break;
        }

        sprintf(buffer2, "%u", cur_reg);
        output_msg(&buffer1, &buffer2, 0);

        // Wait for the screen
        // delay_ms(100);
    }

    return 0;
}
