; ---------------------------------------------------------------------
; main.asm
;
; Read keypad and write it the LCD in hex
;
; Author: Pratchaya Khansomboon
;
; Created: 24-11-2020
; ---------------------------------------------------------------------

  .INCLUDE "m32u4def.inc"

; ---------------------------------------------------------------------
; Definitions of registers, etc. ("constants")
; ---------------------------------------------------------------------
  .EQU RESET      = 0x0000
  .EQU PM_START   = 0x0056

  .EQU CURSOR_ROW0 = 0x80
  .EQU CURSOR_ROW1 = 0xC0

  .DEF TEMP      = R16     ; Temporary value
  .DEF RVAL      = R24     ; Return value

  .EQU ROLL_KEY = '2'
  .EQU SHOW_STAT_KEY = '3'
  .EQU CLEAR_STAT_KEY = '8'
  .EQU MONITOR_KEY = '9'

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

  .INCLUDE "monitor.inc"
  .INCLUDE "stats.inc"
  .INCLUDE "dice.inc"
  .INCLUDE "stat_data.inc"

hello_str:
  .DB "Hello!",0

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

  CALL lcd_init
  CALL cursor_off
  CALL lcd_clear_display

  CALL init_stat
  CALL init_monitor

  LDI PREV_KEY, 0x00
  LDI RVAL, 0x00

  RCALL init_dice

  RJMP main

; ---------------------------------------------------------------------
; Initializations I/O pins
; ---------------------------------------------------------------------
init_pins:
  ; SET OUTPUT
  LDI TEMP, 0xF0
  OUT DDRB, TEMP
  OUT DDRD, TEMP
  OUT DDRF, TEMP

  ; SET INPUT
  LDI TEMP, 0x00
  OUT DDRE, TEMP

  RET

; ---------------------------------------------------------------------
; Draw the currently pressed key on the LCD
; Paramter:
;          R24: Key value
;          R24 > 0
; ---------------------------------------------------------------------
draw_press_2:
  RCALL print_press_2
; ---------------------------------------------------------------------
; Main loop
; ---------------------------------------------------------------------
main:
  ; Read key and convert to ASCII
  RCALL read_keyboard

  ; CP RVAL, PREV_KEY
  ; BRNE draw_press_2
  ; RCALL print_press_2

  RCALL to_ASCII

  CPI RVAL, ROLL_KEY
  BREQ call_roll_dice

  CPI RVAL, SHOW_STAT_KEY
  BREQ call_showstat

  CPI RVAL, CLEAR_STAT_KEY
  BREQ call_clearstat

  CPI RVAL, MONITOR_KEY
  BREQ call_monitor

  CPI RVAL, NO_KEY
  BRNE draw_press_2

  RJMP main

call_roll_dice:
  RCALL roll_dice
  RJMP main

call_showstat:
  RCALL showstat
  RJMP main

call_clearstat:
  RCALL clearstat
  RJMP main

call_monitor:
  RCALL monitor
  RJMP main