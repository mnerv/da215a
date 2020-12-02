;* main.asm
; ---------------------------------------------------------------------
;*  Read keypad and write it the LCD in hex
; ---------------------------------------------------------------------
;*
;* Author: Pratchaya Khansomboon
;*
;* Created: 24-11-2020
;*

  .INCLUDE "m32u4def.inc"

; ---------------------------------------------------------------------
; Definitions of registers, etc. ("constants")
; ---------------------------------------------------------------------
  .EQU RESET      = 0x0000
  .EQU PM_START   = 0x0056
  ; .EQU NO_KEY     = 0xFF

  .EQU ASCII_NUM_START  = 0x30
  .EQU ASCII_A_START    = 0x41
  .EQU HEX_A_START      = 0x0A

  .EQU CURSOR_ROW0 = 0x80
  .EQU CURSOR_ROW1 = 0xC0

  .DEF TEMP      = R16     ; Temporary value

  .DEF RVAL      = R24     ; Return value
  .DEF PREV_KEY  = R25     ; Previous value

; ---------------------------------------------------------------------
; Start of program
; ---------------------------------------------------------------------
  .CSEG
  .ORG RESET
  RJMP init
  .ORG PM_START

  .INCLUDE "delay.inc"
  .INCLUDE "lcd.inc"
  .INCLUDE "keyboard.inc"

; ---------------------------------------------------------------------
; Initializations of stack pointer, I/O pins
; ---------------------------------------------------------------------
init:
  ; Set stack pointer to point at the end of RAM.
  LDI R16, LOW(RAMEND)
  OUT SPL, R16
  LDI R16, HIGH(RAMEND)
  OUT SPH, R16

  CALL init_pins

  CALL lcd_init ; Init the LCD
  RCALL cursor_no_blink  
  RCALL lcd_clear


  ; RCALL draw_text ; Draw the word "KEY:"
  ; RCALL write_welcome

  ; SET_CURSOR CURSOR_ROWh
  SET_CURSOR CURSOR_ROW1

  LDI PREV_KEY, 0x00
  LDI RVAL, 0x00

  RJMP main

; ---------------------------------------------------------------------
; Initializations I/O pins
; ---------------------------------------------------------------------
init_pins:
  ; Set output
  LDI TEMP, 0xF0
  OUT DDRB, TEMP
  OUT DDRD, TEMP
  OUT DDRF, TEMP

  ; Set input
  LDI TEMP, 0x00
  OUT DDRE, TEMP

  RET

; ---------------------------------------------------------------------
; Draw the text: "KEY:" on the LCD display on ROW0, COLUMN0
; ---------------------------------------------------------------------
draw_text:
  SET_CURSOR CURSOR_ROW0

  LCD_WRITE_CHAR 'K'
  LCD_WRITE_CHAR 'E'
  LCD_WRITE_CHAR 'Y'
  LCD_WRITE_CHAR ':'

  RET

; ---------------------------------------------------------------------
; Draw the currently pressed key on the LCD
; Paramter:
;          R24: Key value
;          0 < R24 < 16
; ---------------------------------------------------------------------
draw:
  PUSH RVAL
  RCALL lcd_write_chr
  POP RVAL
  RET

; ---------------------------------------------------------------------
; Main loop
; Read key and print pressed key
; ---------------------------------------------------------------------
main:
  MOV PREV_KEY, RVAL
  RCALL read_keyboard
  NOP
  NOP
  CP RVAL, PREV_KEY
  BREQ main

  CPI RVAL, NO_KEY
  BREQ main

  RCALL draw
  RJMP main