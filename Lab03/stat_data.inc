;----------------------------------------------------------------
; Space in the RAM to save the results from dice throws.
; The following functions are provided:
;         store_stat (R24 contains the dice value)
;               The function will increment the
;               Total number of throws and the
;               number of throws with results equals R24.
;         get_stat (R24 gives the value for which the
;               result is retrieved. If R24 = 0, the
;               total number of throws shall be returned.
;               The result is returned in R24.
;         clear_stat (no parameters in nor out)
;               Clears all data.
;----------------------------------------------------------------

  .DSEG
  .ORG  0x100

max_byte: .BYTE 7
  .CSEG

get_stat_pointer_x:
  LDI XL, LOW(max_byte)
  LDI XH, HIGH(max_byte)
  RET

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

get_stat:
  RCALL get_stat_pointer_x
  ADD XL, R24
  LD R24, X
  RET

clear_stat:
  RCALL get_stat_pointer_x

  LDI R24, 0x00     ; Roll Count
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