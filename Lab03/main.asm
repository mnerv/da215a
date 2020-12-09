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

; ---------------------------------------------------------------------
; Main loop
; ---------------------------------------------------------------------
main:
  ; Read key and convert to ASCII
  ; MOV PREV_KEY, RVAL
  RCALL read_keyboard

  CPI RVAL, NO_KEY
  BRNE select_mode

draw_press_2:
  ; CP RVAL, PREV_KEY
  ; BREQ select_mode
  RCALL print_press_2

select_mode:
  RCALL to_ASCII

  CPI RVAL, ROLL_KEY
  BREQ call_roll_dice

  CPI RVAL, SHOW_STAT_KEY
  BREQ call_showstat

  CPI RVAL, CLEAR_STAT_KEY
  BREQ call_clearstat

  CPI RVAL, MONITOR_KEY
  BREQ call_monitor

  RJMP main

call_roll_dice:
  RCALL lcd_clear_display
  SET_CURSOR 0x80
  PRINTSTRING rolling_str

  RCALL roll_dice

  MOV R24, R16
  RCALL store_stat

  RCALL lcd_clear_display
  SET_CURSOR 0x80
  PRINTSTRING value_str

  MOV R24, R16
  RCALL printhex

  ; 2 s of delay
  LDI R24, 2
  RCALL delay_s

  RJMP main

call_showstat:
  RCALL showstat
  RJMP main

call_clearstat:
  RCALL clearstat

  RCALL delay_1_s
  RJMP main

call_monitor:
  RCALL monitor
  RJMP main