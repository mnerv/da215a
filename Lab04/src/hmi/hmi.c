/*
 * hmi.c
 *
 * Functions for user interactions:
 *  - let the user enter numbers with the numeric keyboard
 *  - show messages on the LCD
 *
 * Author:  Mathias Beckius
 *
 * Date:    2014-11-28
 */

#include "hmi.h"
#include "delay/delay.h"
#include "lcd/lcd.h"
#include "numkey/numkey.h"
#include <string.h>

static void str_to_uint16(char*, uint8_t, uint16_t*);

/*
 * Convert a string of number characters to a integer number.
 * Important! Error handling is NOT implemented!
 *
 * @param p_str: pointer to the string's first character
 * @param length: length of the string (excluding termination character)
 * @param p_nr: pointer to number variable, where converted number is written.
 */
static void str_to_uint16(char* p_str, uint8_t length, uint16_t* p_nr) {
    uint16_t result = 0;
    uint16_t multiplier = 1;
    uint8_t ascii;
    uint8_t nr;
    uint8_t pos = length - 1;
    while (1) {
        // determine ascii code
        ascii = (uint8_t) * (p_str + pos);
        // determine number (0-9)
        nr = ascii - 48;
        // convert number and add to result
        result += nr * multiplier;

        multiplier *= 10;
        if (pos > 0) {
            pos--;
        } else {
            break;
        }
    }
    // return result from conversion
    *p_nr = result;
}

/*
 * Initialization of the HMI functions:
 *  - init numeric keyboard
 *  - init LCD
 */
void hmi_init(void) {
    numkey_init();
    lcd_init();
}

/*
 * Let the user enter a 3-digit integer number.
 * The user enters a digit (0-9) and confirms the number with '#'.
 * A digit can be erased by pressing '*'.
 *
 * @param p_msg: Pointer to the frist character of the mssage
 * @param p_int_nr: pointer to number variable, where the entered number is
 * written
 *
 * @return number of digits (0-3)
 */
uint8_t input_int(char* p_msg, uint16_t* p_int_nr) {
    uint8_t length = 0;
    const uint8_t max_length = 3;
    char numbers[max_length + 1];  // UPPGIFT: Varför måste man dimensionera
                                   // arrayen för ett extra tecken?
    uint8_t key;

    lcd_clear();
    lcd_write_str(p_msg);
    lcd_set_cursor_mode(CURSOR_BLINK);
    lcd_set_cursor_pos(1, 0);

    while (1) {
        do {  // read keyboard....
            key = numkey_read();
        } while (key == NO_KEY);  // ...until a key is pressed!

        if (key == '#') {  // confirmation of the number?
            break;
        } else if (key == '*') {  // erase digit?
            if (length > 0) {
                // UPPGIFT: skriv kod så att tecknet suddas från displayen!
                length--;
            }
        } else if (length < max_length) {  // enter digit?
            lcd_write(DATA, key);
            numbers[length] = key;
            length++;
        }

        // continue when key is released!
        // UPPGIFT: Skriv kod så att koden stannar/"loopar" tills att
        // numkey_read() inte längre detekterar en knapptryckning!
    };
    // terminate string
    numbers[length] = '\0';

    // if a number was entered...
    if (length > 0) {
        // convert number!
        str_to_uint16(numbers, length, p_int_nr);
    }
    // return the number of digits
    return length;
}

/*
 * Show a message on the LCD (for a number of seconds).
 * The first string is written on the first row,
 * the second string is written on the second row.
 *
 * @param p_str1: pointer to first character of the string.
 * @param p_ptr2: pointer to first character of the string.
 * @param delay_after_msg: number of seconds to wait after message is shown.
 */
void output_msg(char* p_str1, char* p_str2, uint8_t delay_after_msg) {
    lcd_set_cursor_mode(CURSOR_OFF);
    lcd_clear();
    lcd_write_str(p_str1);
    lcd_set_cursor_pos(1, 0);
    lcd_write_str(p_str2);
    delay_s(delay_after_msg);
}