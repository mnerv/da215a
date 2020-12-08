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

max_byte:  .BYTE 7
  .CSEG

store_stat:
  RET

get_stat:
  RET

clear_stat:
  RET