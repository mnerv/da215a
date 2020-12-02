;---------------------------------------------------------------- 
; keyboard.inc
; Read keyboard subroutine and map it to the keypad
; 
; Author: Pratchaya Khansomboon
;----------------------------------------------------------------

;----------------------------------------------------------------
; Definitions of registers, etc. ("constants")
;----------------------------------------------------------------
  .EQU NO_KEY     = 0xFF
map_table: 
  .DB "147*2580369#"            ; 12 charactes

;---------------------------------------------------------------- 
; read_keyboard
;
; OUT: R24 currently pressed key
;----------------------------------------------------------------
read_keyboard:
  LDI R18, 0x00                 ; reset counter
scan_key:
  MOV R19, R18
  LSL R19                       ; Shift 4x to the left
  LSL R19                       ; This is because the multiplexer are connected
  LSL R19                       ; to the most significant nibble on PORT group B
  LSL R19
  OUT PORTB, R19                ; set column and row

  PUSH R18
  LDI R24, 5
  RCALL delay_ms
  POP R18

  SBIC PINE, 6                  ; Skip next instruction if PINE.6 is cleared
  RJMP return_key_val           ; Runs when a button is pressed
  INC R18
  CPI R18, 16
  BRNE scan_key
  LDI R18, NO_KEY               ; no key was pressed!
return_key_val:
  MOV RVAL, R18
  CPI RVAL, NO_KEY
  BRNE map_key 
  RET

map_key:
  LDI ZH, HIGH(map_table << 1)  ; Initialize Z pointer
  LDI ZL, LOW(map_table << 1)
  ADD ZL, RVAL                  ; Add index
  LDI RVAL, 0x00
  ADC ZH, RVAL                  ; Add 0 to catch Carry, if present
  LPM RVAL, Z

  RET
