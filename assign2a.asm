; SYSC 2003 Assignment 2
; 
; MM
; February 7, 2014
;
;
; Part A
;
; To convert the analog signal to digital, the following 
; equation will be used. 
;
;       V =  VLow + [(R * A) / (2^n - 1)]
; 
; Where 
; 
; V is the representation of the analog value
; VLow is the minimum value in the intended range of values
; R is the range of values (max - min)
; A is the analog voltage
; n is the number of bits (16 in this case)

	org $800

size equ $FFFF	; This is the 16 bit offset value (2^n - 1)

min rmw 1		; The minimum value in the range
max rmw 1		; The maximum value in the range
range rmw 1		; Stores the range of values between max and min

analogVal rmw 1	; The analog value to convert

result rmw 1	; The representation of the analog value

	
	org $4000
;----------
; Main entry point for this program. It runs
; all of the test cases for this program.
; 
main:
	lds #$3E00

	; Test case 1 
	;
	; Min = -5
	; Max = +5
	; Value = +2
	
	ldd #$FFFB
	std min
	
	ldd #$0005
	std max
	
	ldd #$0002
	std analogVal
	
	jsr convertAD
	
	ldd result
	
	
	; Test case 2 
	;
	; Min = 0
	; Max = +12
	; Value = +20
	
	ldd #$0
	std min
	
	ldd #$000C
	std max
	
	ldd #20
	std analogVal
	
	jsr convertAD
	
	ldd result

	; Test case 3
	;
	; Min = -40
	; Max = +50
	; Value = -10
	
	ldd #$FFD8
	std min
	
	ldd #$0032	
	std max
	
	ldd #$FFF6
	std analogVal
	
	jsr convertAD
	
	ldd result

	bra quit


;---------
; Converts analog signal to digital
; All values are passed as global variables
;
; param min - The minimum value in the range
; param max - The maximum value in the range
; param analogVal - The analog value to convert
;
; The return will be stored in the global result variable
; and will contain the digital representation of the analog value
;
convertAD:
	pshd
	pshx
	pshy

	; Calculate the range
	ldd max
	subd min
	std range
	
	
	; Range * Analog Value
	ldy analogVal
	emul			; Signed multiply D * Y. Result in Y:D
	
	; Division by the maximum size of the result
	ldx #size
	ediv			; Signed divide (Y:D) / X. Result in Y
	tfr y, d		; Put the result in D
	
	; Add the minimum value
	addd min	
	
	; Store the result
	std result


	puly
	pulx
	puld
	
	rts





;---------
; Quits the program
; 
quit:
	swi
	end