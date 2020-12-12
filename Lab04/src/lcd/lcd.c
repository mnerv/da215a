/*
 * lcd.c
 *
 * This file contains subroutines for communicating with a Hitachi HD44780
 * LCD controller (or compatible circuit).
 *
 * Author:  Mathias Beckius
 *          Pratchaya Khansomboon
 *
 * Date:    2014-11-28
 */

#include "lcd.h"
#include "common.h"
#include "delay/delay.h"
#include <avr/io.h>

static void write_4bit_msb(uint8_t);

/*
 * Write the 4 MSB's of 'data' to the LCD.
 *
 * parameter:
 *  data: 4 bits of data
 */
static void write_4bit_msb(uint8_t data) {
    // write data
    SET_BIT_LEVELS(PORTF, 0x0F, data);
    // generate pulse on the Enable pin
    SET_BIT(PORTD, 7);
    delay_1_micros();
    CLR_BIT(PORTD, 7);
}

/*
 * Initialization of the LCD:
 *  - configuration of ports and pins
 *  - configuration of LCD communication
 */
void lcd_init(void) {
    // PF4-PF7 (A3-A0) as outputs (LCD D4-D7)
    DDRF = 0xF0;
    // PD6 & PD7 (D12 & D6) as outputs (LCD RS & LCD E)
    DDRD = 0xC0;

    // wait more than 15 ms after power-up!
    delay_ms(20);
    // select Instruction Register
    CLR_BIT(PORTD, 6);

    // Function Set: 8 bit data interface
    write_4bit_msb(0x30);
    delay_ms(10);
    write_4bit_msb(0x30);
    delay_ms(10);
    write_4bit_msb(0x30);
    delay_ms(10);

    // Function Set: switch to 4 bit data interface
    write_4bit_msb(0x20);
    delay_micros(45);

    // Function Set: 4 bit data interface, 2 lines, font 5x10
    lcd_write(INSTRUCTION, 0x28);

    // Display on, no cursor
    lcd_set_cursor_mode(CURSOR_OFF);

    // clear display
    lcd_clear();

    // Entry Mode Set: incremental cursor movement, no display shift
    lcd_write(INSTRUCTION, 0x06);
}

/*
 * Clears the LCD and moves the cursor to position row 0, column 0.
 */
void lcd_clear(void) {
    lcd_write(INSTRUCTION, 0x01);
    delay_ms(2);
}

/*
 * Sets mode of the cursor.
 * The cursor can be set to:
 *	CURSOR_OFF:     cursor is turned off
 *	CURSOR_ON:      cursor is turned on
 *	CURSOR_BLINK:   cursor is blinking
 *
 * parameter:
 *      mode: cursor mode
 */
void lcd_set_cursor_mode(enum lcd_cursor mode) {
    uint8_t cursor_mode;
    cursor_mode = 0x0C | mode;
    lcd_write(INSTRUCTION, cursor_mode);
};

/*
 * Set position of the cursor.
 *
 * parameter:
 *       row: 0 is the first row, 1 is the second row
 *       col: 0 is the first column, 15 is the last visible column
 */
void lcd_set_cursor_pos(uint8_t row, uint8_t col) {
    uint8_t cursor_pos;
    cursor_pos = 0x80 | (row << 6) | col;
    lcd_write(INSTRUCTION, cursor_pos);
}

/*
 * Writes data or instruction to the LCD.
 *
 * parameter:
 *      lcd_reg: register to communicate with (Instruction or Data register)
 *      data: 8-bit instruction or data (character)
 */
void lcd_write(enum lcd_register lcd_reg, uint8_t data) {
    // select register
    if (lcd_reg == INSTRUCTION) {
        CLR_BIT(PORTD, 6);  // Instruction Register
    } else {
        SET_BIT(PORTD, 6);  // Data Register
    }
    // write data
    write_4bit_msb(data);
    write_4bit_msb(data << 4);
    delay_micros(45);
}

/*
 * Write a string of character to the LCD.
 *
 * parameter:
 *      p_str: pointer to the string's first character
 */
void lcd_write_str(char* p_str) {
    while (*p_str) {
        lcd_write(DATA, *p_str);
        p_str++;
    }
}