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

  .DEF TEMP      = R16    ; Temporary value
  .DEF RVAL      = R24    ; Return value

  .EQU ROLL_KEY       = 0x04      ; '2' on the keypad
  .EQU SHOW_STAT_KEY  = 0x08      ; '3' on the keypad
  .EQU CLEAR_STAT_KEY = 0x06      ; '8' on the keypad
  .EQU MONITOR_KEY    = 0x0A      ; '9' on the keypad

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
; Main loop
; ---------------------------------------------------------------------
main:
  RCALL read_keyboard

  CPI RVAL, NO_KEY
  BRNE select_mode

draw_press_2:
  RCALL print_press_2

; ---------------------------------------------------------------------
; Select mode
; Determine which mode to use
; ---------------------------------------------------------------------
select_mode:
  CPI RVAL, ROLL_KEY
  BREQ call_roll_dice

  CPI RVAL, SHOW_STAT_KEY
  BREQ call_showstat

  CPI RVAL, CLEAR_STAT_KEY
  BREQ call_clearstat

  CPI RVAL, MONITOR_KEY
  BREQ call_monitor

  RJMP main

; -----------------------------------------------------------------------------
; Call roll_dice subroutine
; Print rolling... and storing value in the memory
; -----------------------------------------------------------------------------
call_roll_dice:
  RCALL lcd_clear_display
  SET_CURSOR 0x80
  PRINTSTRING rolling_str

  RCALL roll_dice

  MOV R24, R16
  PUSH R16
  RCALL store_stat

  RCALL lcd_clear_display
  SET_CURSOR 0x80
  PRINTSTRING value_str

  POP R16
  MOV R24, R16
  RCALL printhex

  ; 2 s of delay
  LDI R24, 2
  RCALL delay_s

  RJMP main

; -----------------------------------------------------------------------------
; Call the showstat subroutine
; -----------------------------------------------------------------------------
call_showstat:
  RCALL showstat
  RJMP main

; -----------------------------------------------------------------------------
; Call the clearstat subroutine
; -----------------------------------------------------------------------------
call_clearstat:
  RCALL clearstat

  RCALL delay_1_s
  RJMP main

; -----------------------------------------------------------------------------
; Call the monitor subroutine
; -----------------------------------------------------------------------------
call_monitor:
  RCALL monitor
  RJMP main