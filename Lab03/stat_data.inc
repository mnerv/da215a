; ---------------------------------------------------------------------
; main.asm
;
; Read keypad and write it the LCD in hex
;
; Authors: Pratchaya Khansomboon, Ademir Zjajo
;
; Created: 08-12-2020
; ---------------------------------------------------------------------

; ---------------------------------------------------------------------
; Set where the memory location begins
; ---------------------------------------------------------------------
  .DSEG
  .ORG  0x100

; ---------------------------------------------------------------------
; Allocate maximum location
; ---------------------------------------------------------------------
max_byte: .BYTE 7
  .CSEG

; ---------------------------------------------------------------------
; Get stat data pointer and store it in the X register
; ---------------------------------------------------------------------
get_stat_pointer_x:
  LDI XL, LOW(max_byte)
  LDI XH, HIGH(max_byte)
  RET

; ---------------------------------------------------------------------
; Store stat subroutine
; ---------------------------------------------------------------------
store_stat:
  RCALL get_stat_pointer_x

  LD R16, X
  INC R16
  ST X, R16

  ADD XL, R24
  LD R24, X
  INC R24
  ST X, R24

  RET

; ---------------------------------------------------------------------
; Get stat
; ---------------------------------------------------------------------
get_stat:
  RCALL get_stat_pointer_x
  ADD XL, R24
  LD R24, X
  RET

; ---------------------------------------------------------------------
; Clear stat
; ---------------------------------------------------------------------
clear_stat:
  RCALL get_stat_pointer_x

  LDI R24, 0x00     ; Roll count
  ST X, R24

  INC XL
  ST X, R24         ; One count

  INC XL
  ST X, R24         ; Two count

  INC XL
  ST X, R24         ; Three count

  INC XL
  ST X, R24         ; Four count

  INC XL
  ST X, R24         ; Five count

  INC XL
  ST X, R24         ; Six count

  RET