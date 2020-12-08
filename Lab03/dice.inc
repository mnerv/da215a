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

welcome_dice_str:
  .DB "Welcome to dice!",0

press_2_str:
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

  ; 2 s of delay
  ; LDI R24, 2
  RCALL delay_1_s

  RCALL print_press_2

  RET

; ---------------------------------------------------------------------
; Print Welcome to the screen
; ---------------------------------------------------------------------
print_welcome:
  PRINTSTRING welcome_dice_str
  RET

print_press_2:
  RCALL lcd_clear_display
  PRINTSTRING press_2_str
  RET

; ---------------------------------------------------------------------
; Roll Dice subroutine
; ---------------------------------------------------------------------
roll_dice:
  LDI R16, 6
test_dice:
  NOP
  NOP
  RCALL read_keyboard
  RCALL to_ASCII

  CPI RVAL, ROLL_KEY
  BREQ roll

  RET
roll:
  DEC R16
  BREQ roll_dice
  RJMP test_dice