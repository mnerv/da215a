;------------------------------------------------------------------------------
; delay_asm.S
; Contains delay routines that can be called in C.
; This delay is for a chip that's using a 16 Mhz clock.
;
; Author:  Pratchaya Khansomboon
;
; Date:    09-12-2020
;------------------------------------------------------------------------------

.GLOBAL delay_1_micros
.GLOBAL delay_micros
.GLOBAL delay_ms
.GLOBAL delay_1_s
.GLOBAL delay_s

;------------------------------------------------------------------------------
; Delay 1 μs
;------------------------------------------------------------------------------
delay_1_micros:
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  NOP
  RET

;------------------------------------------------------------------------------
; Delay of x μs
;
; Parameter:
;        IN: R24 for the amount of delay
;------------------------------------------------------------------------------
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
  DEC      R24             ; 1 cycle
  CPI      R24, 0          ; 1 cycle
  BRNE     delay_micros    ; continue! 1 false, 2 true
  RET                      ; 4 cycles

; -----------------------------------------------------------------------------
; Delay x s
;
; Parameter:
;        IN: R24 amount of delay
; Register used: R24, R18
; -----------------------------------------------------------------------------
delay_ms:
  MOV      R18, R24
loop_dms:
  LDI      R24, 250
  RCALL    delay_micros
  LDI      R24, 250
  RCALL    delay_micros
  LDI      R24, 250
  RCALL    delay_micros
  LDI      R24, 250
  RCALL    delay_micros
  DEC      R18
  CPI      R18, 0          ; more loops to do?
  BRNE     loop_dms        ; continue!
  RET

; -----------------------------------------------------------------------------
; Delay 1 s
;
; Register used: R24, R18
; -----------------------------------------------------------------------------
delay_1_s:
  LDI      R24, 250
  RCALL    delay_ms
  LDI      R24, 250
  RCALL    delay_ms
  LDI      R24, 250
  RCALL    delay_ms
  LDI      R24, 250
  RCALL    delay_ms
  RET

; -----------------------------------------------------------------------------
; Delay some s
;
; Parameter:
;        IN: R24 amount of delay
; Register used: R24, R19, R18
; -----------------------------------------------------------------------------
delay_s: 
  MOV      R19, R24
loop_s:
  LDI      R24, 250
  RCALL    delay_ms
  LDI      R24, 250
  RCALL    delay_ms
  LDI      R24, 250
  RCALL    delay_ms
  LDI      R24, 250
  RCALL    delay_ms
    
  DEC      R19
  CPI      R19, 0          ; more loops to do?
  BRNE     loop_s          ; continue!
  RET