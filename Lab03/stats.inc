; /*
;  * stats.inc
;  *
;  *  Created: 2016-11-16 20:03:40
;  *   Author: Magnus Krampell
;  */ 


clearstring:
	.DB "Clearing...",0 
totalstring:
	.DB "Total throws:",0
countones:
	.DB "Nbr of 1's:",0
counttwos:
	.DB "Nbr of 2's:",0
countthrees:
	.DB "Nbr of 3's:",0
countfours:
	.DB "Nbr of 4's:",0
countfives:
	.DB "Nbr of 5's:",0
countsixs:
	.DB "Nbr of 6's:",0


; init statistics module
init_stat:
	RCALL clear_stat	; clear data structure
	RET

; print content of RVAL on display

hexconv: .DB "0123456789ABCDEF"
printhex:
	LDI		ZH, HIGH(hexconv<<1)
	LDI		ZL, LOW(hexconv<<1)
	MOV		R5, RVAL		; save content
	SWAP	RVAL			; 
	ANDI	RVAL, 0x0F		; mask out low nibble
	ADD		ZL, RVAL
	CLR		R6
	ADC		ZH, R6			; handle carry, if needed		
	LPM		RVAL, Z			; convert number to ASCII
	RCALL	lcd_write_chr	; write to LCD
	MOV		RVAL, R5		; retrieve content
	ANDI	RVAL, 0x0F		; mask out low nibble
	LDI		ZL, LOW(hexconv<<1) ; reset ZL to start
	LDI		ZH, HIGH(hexconv<<1)
	ADD		ZL, RVAL
	CLR		R6
	ADC		ZH, R6			; handle carry, if needed		
	LPM		RVAL, Z			; convert number to ASCII
	RCALL lcd_write_chr		; write to LCD
	RET

showstat:
	RCALL lcd_clear_display
	PRINTSTRING totalstring
	LDI RVAL, 0
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	PRINTSTRING countones
	LDI RVAL, 1
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	PRINTSTRING counttwos
	LDI RVAL, 2
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	PRINTSTRING countthrees
	LDI RVAL, 3
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	PRINTSTRING countfours
	LDI RVAL, 4
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	PRINTSTRING countfives
	LDI RVAL, 5
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	PRINTSTRING countsixs
	LDI RVAL, 6
	RCALL get_stat			; get total number of throws	
	RCALL printhex			; print as 2 hex numbers
	RCALL delay_1_s

	RCALL lcd_clear_display
	RET

clearstat:
	RCALL lcd_clear_display
	PRINTSTRING clearstring
	RCALL clear_stat
	RET
