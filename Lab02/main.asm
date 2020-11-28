;* main.asm
;* ----------------------------------------------
;*  Read keypad and write it the LCD in hex
;* ----------------------------------------------
;*
;* Author: Pratchaya Khansomboon
;*
;* Created: 24-11-2020
;*

  .INCLUDE "m32u4def.inc"

  .EQU RESET      = 0x0000
  .EQU PM_START   = 0x0056
  .EQU NO_KEY     = 0xFF

  .EQU NUM_START  = 0x30
  .EQU ABC_START  = 0x41
  .EQU NUM_OFFSET = 0x0A

  .EQU CURSOR_ROW0 = 0x80
  .EQU CURSOR_ROW1 = 0xC0

  .EQU MAX_CHAR = 0x02

  .DEF TEMP     = R16     ; Temporary value

  .DEF RVAL     = R24     ; Return value
  .DEF PREV     = R30     ; Previous value
  .DEF KEY_COUNT = R31

  .CSEG
  .ORG RESET
  RJMP init
  .ORG PM_START

  .INCLUDE "delay.inc"
  .INCLUDE "lcd.inc"

init:
  ; Set stack pointer to point at the end of RAM.
  LDI R16, LOW(RAMEND)
  OUT SPL, R16
  LDI R16, HIGH(RAMEND)
  OUT SPH, R16

  CALL init_pins

  CALL lcd_init ; Init the LCD
  ; CALL cursor_off

  CALL draw_key ; Draw the word "KEY:"

  SET_CURSOR CURSOR_ROW0
  LDI RVAL, 0x00
  SET_CURSOR CURSOR_ROW1
  ; RCALL draw
  ; LDI KEY_COUNT, 0x00 ; reset key count
  ; INC KEY_COUNT


  RJMP main

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

read_keyboard:
  LDI R18, 0x00           ; reset counter
scan_key:
  MOV R19, R18
  LSL R19                 ; Shift 4x to the left
  LSL R19                 ; This is because the multiplexer are connected
  LSL R19                 ; to the most significant nibble on PORT group B
  LSL R19
  OUT PORTB, R19          ; set column and row
  NOP
  NOP

  NOP                     ; 12 NOP needed to achieve 750 ns of delay for 16 MHz clock
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP

  NOP                     ; Needed more NOP to wait
  NOP                     ; 12 NOP doesn't work as intended
  NOP
  NOP
  NOP
  NOP
  NOP
  SBIC PINE, 6            ; Skip next instruction if PINE.6 is cleared
  RJMP return_key_val     ; Runs when a button is pressed
  INC R18
  CPI R18, 16
  BRNE scan_key
  LDI R18, NO_KEY         ; no key was pressed!
return_key_val:
  MOV RVAL, R18
  RET

draw_key:
  SET_CURSOR CURSOR_ROW0

  LCD_WRITE_CHAR 'K'
  LCD_WRITE_CHAR 'E'
  LCD_WRITE_CHAR 'Y'
  LCD_WRITE_CHAR ':'

  RET

draw:
  PUSH RVAL

  CPI RVAL, NUM_OFFSET
  BRSH draw_abc
draw_num:
  LDI TEMP, NUM_START
  ADD RVAL, TEMP
  RCALL lcd_write_chr

  POP RVAL
  RET

draw_abc:
  LDI TEMP, ABC_START
  LDI R18, NUM_OFFSET
  SUB RVAL, R18
  ADD RVAL, TEMP
  RCALL lcd_write_chr 

  POP RVAL
  RET

reset_keycount:
  LDI KEY_COUNT, 0x00
  PUSH RVAL
  SET_CURSOR CURSOR_ROW1
  POP RVAL
main:
  MOV PREV, RVAL
  RCALL read_keyboard
  CP RVAL, PREV
  BREQ main

  CPI RVAL, NO_KEY
  BREQ main

  RCALL draw
  INC KEY_COUNT
  CPI KEY_COUNT, MAX_CHAR
  BRSH reset_keycount
  RJMP main