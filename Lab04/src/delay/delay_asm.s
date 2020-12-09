﻿; #include <avr/io.h>
#include <avr/io.h>

.GLOBAL delay_1_micros
.GLOBAL delay_micros
.GLOBAL delay_ms
.GLOBAL delay_1_s
.GLOBAL delay_s

; #include <delay.h>

;---------------------------------------------------------------- 
; delay_asm.s
;
; Author:  Pratchaya Khansomboon
;
; Date:    09-12-2020
;---------------------------------------------------------------- 

;==============================================================================
; Delay of 1 μs (including RCALL)
;==============================================================================
delay_1_micros:       ; UPPGIFT: komplettera med ett antal NOP-instruktioner!!!
  NOP                 ; 
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  RET                 ; 4 cycles

;==============================================================================
; Delay of X μs
; LDI + RCALL = 4 cycles
; R24 can't be more than 0xFF
;==============================================================================
delay_micros:         ; UPPGIFT: komplettera med ett antal NOP-instruktioner!!!
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
  NOP
  DEC R24             ; 1 cycle
  CPI R24, 0          ; 1 cycle
  BRNE delay_micros   ; continue! 1 false, 2 true
  RET                 ; 4 cycles

;==============================================================================
; Delay of X ms
; LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
  MOV R18, R24
loop_dms:
  LDI R24, 250
  RCALL delay_micros
  LDI R24, 250
  RCALL delay_micros
  LDI R24, 250
  RCALL delay_micros
  LDI R24, 250
  RCALL delay_micros
  DEC R18
  CPI R18, 0          ; more loops to do?
  BRNE loop_dms       ; continue!
  RET

delay_1_s:
  LDI R24, 250
  RCALL delay_ms
  LDI R24, 250
  RCALL delay_ms
  LDI R24, 250
  RCALL delay_ms
  LDI R24, 250
  RCALL delay_ms
  RET

delay_s: 
  MOV R19, R24
loop_s:
  LDI R24, 250
  RCALL delay_ms
  LDI R24, 250
  RCALL delay_ms
  LDI R24, 250
  RCALL delay_ms
  LDI R24, 250
  RCALL delay_ms

  DEC R19
  CPI R19, 0        ; more loops to do?
  BRNE loop_s       ; continue!
  RET