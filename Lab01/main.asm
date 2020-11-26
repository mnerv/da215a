;* lab1.asm
;* ----------------------------------------------
;*  Read keypad and write it into 4 LEDs t
;*  display currently pressed number
;* ----------------------------------------------
;*
;* Author: Pratchaya Khansomboon
;*
;* Created: 24-11-2020
;*

  .INCLUDE "m32u4def.inc"

  .EQU RESET    = 0x0000
  .EQU PM_START = 0x0056
  .EQU NO_KEY   = 0x0F
  .DEF TEMP     = R16     ; Temporary value
  .DEF RVAL     = R24     ; Return value

  .CSEG                   ; Specify start of the code
  .ORG RESET              ; Define the address of the next instruction
  RJMP init
  .ORG PM_START           ; Define the address of the next instruction

init:
  ; Set stack pointer to point at the end of RAM.
  LDI R16, LOW(RAMEND)
  OUT SPL, R16
  LDI R16, HIGH(RAMEND)
  OUT SPH, R16

  CALL init_pins

  RJMP main

init_pins:
  ; SET OUTPUT
  LDI TEMP, 0xF0
  OUT DDRB, TEMP
  OUT DDRF, TEMP

  ; SET INPUT
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
  SBIC PINE, 6            ; Skip next instruction if PINE.6 is cleared
  RJMP return_key_val     ; Runs when a button is pressed
  INC R18
  CPI R18, 16
  BRNE scan_key
  LDI R18, NO_KEY         ; no key was pressed!
return_key_val:
  MOV RVAL, R18
  RET

main:
  CALL read_keyboard
  ; LDI RVAL, 0x03
  LSL RVAL                ; Shift to the left 4x
  LSL RVAL                ; This is because the LEDs are connected
  LSL RVAL                ; to the most significant nibble on PORT group F
  LSL RVAL
  OUT PORTF, RVAL
  NOP                     ; 1 cycle
  NOP
  RJMP main               ; 2 cycles