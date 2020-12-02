;*
;* lcd.inc
;* This file contains subroutines for communicating with a Hitachi HD44780
;* LCD controller (or compatible circuit).
;* These subroutines are created for the course Datateknik DA215A at
;* Malmö University.
;*
;* Author: Mathias Beckius
;*
;* Date: 2014-11-24
;*

; * ---------------------------------------------------------------------------
; *  Avaiable MACROS
; * -------------------------------
; *  LCD_WRITE_CHAR
; *  SET_CURSOR
; *
; * ===============================
; *  Avaiable SUBROUTNES
; * -------------------------------
; *  lcd_write_nibble 
; *  lcd_write_instr 
; *  lcd_write_chr
; *  lcd_clear
; *  cursor_no_blink
; *  cursor_off
; *  cursor_blinking
; *  lcd_init
; * ---------------------------------------------------------------------------

;==============================================================================
; Defines of ports and pins used by the LCD
;==============================================================================
  .EQU E_PORT  = PORTD      ; port for Enable pin
  .EQU E       = 7          ; Enable pin, bit 7
  .EQU RS_PORT = PORTD      ; port for RS pin
  .EQU RS      = 6          ; RS pin, bit 6
  .EQU D_PORT  = PORTF      ; port for data/instructions

str_1:  
  .DB "Welcome!"
  .EQU sz_str1 = 8          ; Size of ”str_1”

; * ---------------------------------------------------------------------------
; MACRO definitions
; * ---------------------------------------------------------------------------

; * ---------------------------------------------------------------------------
; LCD_WRITE_CHAR
; Write character to the LCD
; Parameter: IN
;            R24
; * ---------------------------------------------------------------------------
.MACRO LCD_WRITE_CHAR
  LDI R24, @0
  RCALL lcd_write_chr
.ENDMACRO

; * ---------------------------------------------------------------------------
; SET_CUSOR
; Set the cursor
; * ---------------------------------------------------------------------------
.MACRO SET_CURSOR
  LDI R24, @0
  RCALL lcd_write_instr
.ENDMACRO

; * ---------------------------------------------------------------------------
; Write the most significant nibble (of the content in R24) to the LCD.
; * ---------------------------------------------------------------------------
lcd_write_nibble:
  OUT D_PORT, R24           ; write data
  SBI E_PORT, E             ; set Enable pin for...
  RCALL delay_1_micros      ; ...1 μs!
  CBI E_PORT, E             ; clear Enable pin
  RET

; * ---------------------------------------------------------------------------
; Write to the Instruction Register.
; Instruction is stored in R24.
; A minimum of 39 μs delay must be generated after each instruction!
; * ---------------------------------------------------------------------------
lcd_write_instr:
  CBI RS_PORT, RS           ; select Instruction Register
  RCALL lcd_write_nibble    ; write MSB's
  SWAP R24
  RCALL lcd_write_nibble    ; write LSB's
  LDI R24, 45
  RCALL delay_micros
  RET

; * ---------------------------------------------------------------------------
; Write a character to the Data Register.
; Character is stored in R24.
; After the character has been written, a delay of 43 μs is generated! 
; * ---------------------------------------------------------------------------
lcd_write_chr:
  SBI RS_PORT, RS           ; select Data Register
  RCALL lcd_write_nibble    ; write MSB's
  SWAP R24
  RCALL lcd_write_nibble    ; write LSB's
  LDI R24, 45
  RCALL delay_micros
  RET

;==============================================================================
; Clear the LCD display
;==============================================================================
lcd_clear:
  LDI R24, 0x01
  RCALL lcd_write_instr
  LDI R24, 2
  RCALL delay_ms
  RET

;==============================================================================
; Set cursor on but not blinking and display on
;==============================================================================
cursor_no_blink:
  LDI R24, 0x0E
  RCALL lcd_write_instr
  LDI R24, 2
  RCALL delay_ms
  RET

;==============================================================================
; Set cursor off and display on
;==============================================================================
cursor_off:
  LDI R24, 0x0C 
  RCALL lcd_write_instr
  LDI R24, 2
  RCALL delay_ms
  RET

;==============================================================================
; Set cursor to blinking and display on
;==============================================================================
cursor_blinking:
  LDI R24, 0x0F             ; Display on, Cursor On, Blinking Cursor
  RCALL lcd_write_instr
  LDI R24, 2
  RCALL delay_ms
  RET

; * ---------------------------------------------------------------------------
; * ---------------------------------------------------------------------------
write_welcome:
  LDI ZH, HIGH(str_1<<1)
  LDI ZL, LOW(str_1<<1)
  CLR R16
nxt1:
  LPM R24, Z+
  RCALL lcd_write_chr
  INC  R16
  CPI  R16, sz_str1
  BRLT nxt1
  RET

;==============================================================================
; Initialize the LCD.
;==============================================================================
lcd_init:
  LDI R24, 20               ; wait more than 15 ms after power-up!
  RCALL delay_ms
  CBI RS_PORT, RS           ; select Instruction Register
  LDI R24, 0x30             ; Function Set: 8 bit data interface
  RCALL lcd_write_nibble
  LDI R24, 10               ; wait 10 ms
  RCALL delay_ms
  LDI R24, 0x30             ; Function Set: 8 bit data interface
  RCALL lcd_write_nibble
  LDI R24, 10               ; wait 10 ms
  RCALL delay_ms
  LDI R24, 0x30             ; Function Set: 8 bit data interface
  RCALL lcd_write_nibble
  LDI R24, 10               ; wait 10 ms
  RCALL delay_ms

  LDI R24, 0x20             ; Function Set: switch to 4 bit data interface
  RCALL lcd_write_nibble
  LDI R24, 45               ; must be followed by a minimum
  RCALL delay_micros        ; delay of 39 μs

  LDI R24, 0x28             ; Function Set: 4 bit data interface, 2 lines,
  RCALL lcd_write_instr     ; Font 5x10

  RCALL cursor_blinking

  LDI R24, 0x01             ; Clear Display
  RCALL lcd_write_instr
  LDI R24, 2                ; must be followed by a minimum
  RCALL delay_ms            ; delay of 1.53 ms

  LDI R24, 0x06             ; Entry Mode Set: incremental cursor movement,
  RCALL lcd_write_instr     ;                 no display shift
  RET