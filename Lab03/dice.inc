; dice.in

; ---------------------------------------------------------------------
; Constant definitions
; ---------------------------------------------------------------------
.EQU ROLL_KEY = '2'

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

  RCALL lcd_clear
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
  RET
  DEC R16
roll:
  RCALL lcd_clear
  SET_CURSOR 0x80
  PRINTSTRING rolling_str

  BREQ roll_dice
  RJMP test_dice