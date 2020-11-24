;*
;* delay.inc
;*
;* Author: Pratchaya Khansomboon
;*
;* Date: 2020-11-24
;*

;==============================================================================
; Delay of 1 μs (including RCALL)
;==============================================================================
delay_1_micros:       ; UPPGIFT: komplettera med ett antal NOP-instruktioner!!!
  RET

;==============================================================================
; Delay of X μs
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_micros:         ; UPPGIFT: komplettera med ett antal NOP-instruktioner!!!
  DEC R24
  CPI R24, 0          ; more loops to do?
  BRNE delay_micros   ; continue!
  RET

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