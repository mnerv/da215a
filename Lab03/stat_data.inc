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

get_stat_pointer_y:
  LDI YL, LOW(max_byte)
  LDI YH, HIGH(max_byte)
  RET

store_stat:
  RCALL get_stat_pointer_y

  LD R16, Y
  INC R16
  ST Y, R16

  ADD YL, R24
  LD R24, Y
  INC R24
  ST Y, R24

  RET

get_stat:
  RCALL get_stat_pointer_y
  ADD YL, R24
  LD R24, Y
  RET

clear_stat:
  RCALL get_stat_pointer_y

  LDI R24, 0x00     ; Roll Count
  ST Y, R24

  INC YL
  ST Y, R24         ; One count

  INC YL
  ST Y, R24         ; Two count

  INC YL
  ST Y, R24         ; Three count

  INC YL
  ST Y, R24         ; Four count

  INC YL
  ST Y, R24         ; Five count

  INC YL
  ST Y, R24         ; Six count

  RET