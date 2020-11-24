  .INCLUDE "m32u4def.inc"

  .EQU RESET    = 0x0000
  .EQU PM_START = 0x0056
  .EQU NO_KEY   = 0xFF
  .DEF TEMP     = R16     ; Temporary value
  .DEF RVAL     = R24     ; Return value

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
  LDI R18, 0x00       ; reset counter
scan_key:
  MOV R19, R18
  LSL R19
  LSL R19
  LSL R19
  LSL R19
  OUT PORTB, R19      ; set column and row
  NOP                 ; a minimum of 2 NOP's is necessary!
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
  SBIC PINE, 6
  RJMP return_key_val
  INC R18
  CPI R18, 16
  BRNE scan_key
  LDI R18, NO_KEY     ; no key was pressed!
return_key_val:
  MOV RVAL, R18
  RET

; main:
;   CALL read_keyboard
;   LSL RVAL
;   LSL RVAL
;   LSL RVAL
;   LSL RVAL

;   OUT PORTF, RVAL
;   NOP                 ; 1 cycle
;   NOP
;   RJMP main           ; 2 cycles

main:
  LCD_WRITE_CHAR 'H'
  LCD_WRITE_CHAR 'H'
  LCD_WRITE_CHAR 'E'
  LCD_WRITE_CHAR 'L'
  LCD_WRITE_CHAR 'L'
  LCD_WRITE_CHAR 'O'
  LCD_WRITE_CHAR ','
  LCD_WRITE_CHAR ' '
  LCD_WRITE_CHAR 'W'
  LCD_WRITE_CHAR 'O'
  LCD_WRITE_CHAR 'R'
  LCD_WRITE_CHAR 'L'
  LCD_WRITE_CHAR 'D'
  LCD_WRITE_CHAR '!'

loop:
  RJMP loop