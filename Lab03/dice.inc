; ---------------------------------------------------------------------
; dice.inc
; Dice handle dice and keyboard read
;
; Author: Pratchaya Khansomboon
;
; Created: 02-12-2020
; ---------------------------------------------------------------------

; ---------------------------------------------------------------------
; Constant definitions
; ---------------------------------------------------------------------
  .EQU ROLL_KEY = '2'
  .EQU SHOW_STAT_KEY = '3'
  .EQU CLEAR_STAT_KEY = '8'
  .EQU MONITOR_KEY = '9'

welcome_dice_str:
  .DB "Welcome to dice!",0

press_1_str:
  .DB "Press 2 to roll",0

rolling_str:
  .DB "Rolling...",0

value_str:
  .DB "Value: ",0

; ---------------------------------------------------------------------
; Init dice
; ---------------------------------------------------------------------
init_dice:
  RCALL print_welcome

  ; 2 s of 
  LDI R24, 2
  RCALL delay_s

  RCALL lcd_clear_display
  PRINTSTRING press_1_str

  RET

print_welcome:
  PRINTSTRING welcome_dice_str
  RET

roll_dice:
  LDI R16, 6
test_dice:
  NOP
  NOP
  RCALL read_keyboard
  CPI RVAL, ROLL_KEY
  BREQ roll

  ; CPI RVAL, SHOW_STAT_KEY
  ; BREQ show_stat

  ; CPI RVAL, CLEAR_STAT_KEY
  ; BREQ clear_stat

  CPI RVAL, MONITOR_KEY
  BREQ show_monitor

  RET

roll:
  RCALL lcd_clear_display

  SET_CURSOR 0x80
  PRINTSTRING rolling_str

  DEC R16
  BREQ roll_dice
  RJMP test_dice

; show_stat:
;   RCALL showstat
;   RJMP test_dice

; clear_stat:
;   RCALL clearstat
;   RJMP test_dice

show_monitor:
  CALL monitor
  RJMP test_dice