;*
;* delay_routines.asm
;* 
;* This is a program for testing delay routines, made for the course DA215A
;* at Malmö University.
;* A test of a delay routine can be performed as follows:
;*    1. Set D13 pin (PORTC, bit 7) HIGH
;*    2. Call delay routine
;*    3. Set D13 pin LOW
;*    4. Call delay routine
;*    5. loop (jump to step 1)
;* The result can be measured as a square wave on a oscilloscope. Measure
;* the length of the duty cycle and compare with the desired delay.
;*
;* Author:	Mathias Beckius
;*
;* Date:	2014-11-11
;* 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
  .INCLUDE "m32u4def.inc"
  .EQU RESET     = 0x0000
  .EQU PM_START  = 0x0056

;==============================================================================
; Start of program
;==============================================================================
  .CSEG
  .ORG RESET
  RJMP init

  .ORG PM_START
  .INCLUDE "delay.inc"
;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
  ; Set stack pointer to point at the end of RAM.
  LDI R16, LOW(RAMEND)
  OUT SPL, R16
  LDI R16, HIGH(RAMEND)
  OUT SPH, R16
  ; Initialize pins
  RCALL init_pins
  ; Jump to main part of program
  RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	
  LDI R16, 0b10000000
  OUT DDRC, R16
  RET

;==============================================================================
; Main part of program
;==============================================================================
main:		
  SBI PORTC, 7          ; set pin HIGH (2 cycles)

  ; /***********************/
  ; /* test 1 microsecond  */ 
  ; /***********************/
  ; RCALL delay_1_micros ; 3 cycles

  ; /***********************/
  ; /* test microseconds   */ 
  ; /***********************/
  ; LDI R24, 1
  ; RCALL delay_micros

  ; /***********************/
  ; /* test milliseconds   */ 
  ; /***********************/
  LDI R24, 2
  RCALL delay_ms

  CBI PORTC, 7          ; set pin LOW (2 cycles)

  ; /***********************/
  ; /* test 1 microsecond  */ 
  ; /***********************/
  ; RCALL delay_1_micros

  ; /***********************/
  ; /* test microseconds   */ 
  ; /***********************/
  ; LDI R24, 1
  ; RCALL delay_micros

  ; /***********************/
  ; /* test milliseconds   */ 
  ; /***********************/
  LDI R24, 2
  RCALL delay_ms

  RJMP main             ; 2 cycles