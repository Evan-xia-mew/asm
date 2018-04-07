; SYSC 2003 Assignment 2
; 
; Matt M.
; February 11, 2014
; 
; Part B



	org $1000

; Sample strings for testing

str1 db "1234", 0
str2 db "255", 0
str3 db "Hello, World!", 0

successMsg db "Function generated the expected output", $0A, 0
failMsg	db "Function did not get the expected output", $0A, 0

	org $4000

main:
	; Load the SP
	lds #$3E00
	
	; Test printStr with str1
	ldd #str1
	jsr printStr
	
	; Test printChar by printing a linefeed character
	ldab #$0A
	jsr printChar
	
	; Test printStr with str3
	ldd #str3
	jsr printStr
	
	; Print a line feed character
	ldab #$0A
	jsr printChar

	; Test printHex with a number 5
	ldab #5
	jsr printHex
	
	; Print a line feed character
	ldab #$0A
	jsr printChar
	
	; Test printHex with a letter C
	ldab #$C
	jsr printHex
	
	; Print a line feed character
	ldab #$0A
	jsr printChar
	
	
	; ------------
	;
	; Testing convertToDecimal
	; 
	; ------------
	; 
	; Test 1:
	; 	Input str1 - "1234"
	; 	Expected return in register D 0x4D2
	;	
	; ------------
	
CTDT1:
	
	ldd #str1
	jsr convertToDecimal
	
	; Check the output
	cpd #$04D2
	bne CTDT1F
	
CTDT1S:
	ldd #successMsg
	jsr printStr
	bra CTDT2
CTDT1F:
	ldd #failMsg
	jsr printStr


	; ------------
	; 
	; Test 2:
	; 	Input str2 - "255"
	; 	Expected return in register D 0xFF
	;	
	; ------------
CTDT2:
	
	ldd #str2
	jsr convertToDecimal
	
	; Check the output
	cpd #$FF
	bne CTDT2F
	
CTDT2S:
	ldd #successMsg
	jsr printStr
	bra CTST1
CTDT2F:
	ldd #failMsg
	jsr printStr


	; ------------
	;
	; Testing convertToString
	; 
	; ------------
	; 
	; Test 1:
	; 	Input 
	;			num 	- 12
	; 			*string -  $1000 [Location of str1 will be overwritten]
	; 	Expected return in memory locations 1000 - 1003: "012"
	;	
	; ------------

CTST1:

	ldab #12
	ldx #$1000
	pshx
	jsr convertToString
	pulx

	; Check the output
	ldab #'0'
	cmpb $1000
	bne CTST1F
	
	ldab #'1'
	cmpb $1001
	bne CTST1F
	
	ldab #'2'
	cmpb $1002
	bne CTST1F
	
CTST1S:
	ldd #successMsg
	jsr printStr
	bra CTST2
CTST1F:
	ldd #failMsg
	jsr printStr
	

	; ------------
	; 
	; Test 2:
	; 	Input 
	;			num 	- 128
	; 			*string -  $1000 [Location of str1 will be overwritten]
	; 	Expected return in memory locations 1000 - 1003: "128"
	;	
	; ------------

CTST2:

	ldab #128
	ldx #$1000
	pshx
	jsr convertToString
	pulx

	; Check the output
	ldab #'1'
	cmpb $1000
	bne CTST2F
	
	ldab #'2'
	cmpb $1001
	bne CTST2F
	
	ldab #'8'
	cmpb $1002
	bne CTST2F
	
CTST2S:
	ldd #successMsg
	jsr printStr
	bra GRCT1
CTST2F:
	ldd #failMsg
	jsr printStr
	
	
	; ------------
	;
	; Testing getRowColumn
	; 
	; ------------
	; 
	; Test 1:
	; 	Input 
	;			code 	 - 0x42 - 0100 0010
	; 			*row	 - $1000 [Location of str1 will be overwritten]
	;			*column  - $1001 [Location of str1 will be overwritten]
	; 	Expected return 
	; 			In register B : 0
	;			In memory location 1001 : 2
	; 			in memory location 1000 : 1
	;	
	; ------------

GRCT1:
	; The row/column locations will remain the same for all tests
	
	; Column location
	ldx #$1001
	pshx
	
	; Row location
	ldx #$1000
	pshx
	
	
	ldab #$42
	jsr getRowColumn
	
	cmpb #0
	bne GRCT1F
	
	ldab $1001
	cmpb #2
	bne GRCT1F
	
	ldab $1000
	cmpb #1
	bne GRCT1F
	
GRCT1S:
	ldd #successMsg
	jsr printStr
	bra GRCT2
GRCT1F:
	ldd #failMsg
	jsr printStr
	
	
	; ------------
	; 
	; Test 2:
	; 	Input 
	;			code 	 - 0xFF - 1111 1111
	; 			*row	 - $1000 [Location of str1 will be overwritten]
	;			*column  - $1001 [Location of str1 will be overwritten]
	; 	Expected return 
	; 			In register B : 0xFFFF
	;			In memory location 1000 : ?
	; 			in memory location 1001 : ?
	;	
	; ------------

GRCT2:	
	ldab #$FF
	jsr getRowColumn
	
	cmpb #$FF
	bne GRCT1F
	
	
GRCT2S:
	ldd #successMsg
	jsr printStr
	bra GRCT3
GRCT2F:
	ldd #failMsg
	ldab #$FF	
	jsr getRowColumn
	
	
	; ------------
	; 
	; Test 3:
	; 	Input 
	;			code 	 - 0x00 - 0000 0000

	; 			*row	 - $1000 [Location of str1 will be overwritten]
	;			*column  - $1001 [Location of str1 will be overwritten]
	; 	Expected return 
	; 			In register B : 0xFFFF
	;			In memory location 1000 : ?
	; 			in memory location 10001 : ?
	;	
	; ------------

GRCT3:	
	ldab #0
	jsr getRowColumn
	
	pulx
	pulx	
	
	cmpb #$FF
	bne GRCT1F
	
	
GRCT3S:
	ldd #successMsg
	jsr printStr
	bra GCT1
GRCT3F:
	ldd #failMsg
	
	

	; ------------
	;
	; Testing getChar
	; 
	; ------------
	; 
	; Test 1:
	; 	Input 
	; 			row	 	- 2
	;			column  - 2
	; 	Expected return 
	; 			In register B : '9'
	;	
	; ------------
GCT1:
	ldab #2
	pshb
	ldab #2
	jsr getChar

	cmpb #'9'
	bne GCT1F
	
	
GCT1S:
	ldd #successMsg
	jsr printStr
	bra GCT2
GCT1F:
	ldd #failMsg

	; ------------
	; 
	; Test 2:
	; 	Input 
	; 			row	 	- 1
	;			column  - 1
	; 	Expected return 
	; 			In register B : '5'
	;	
	; ------------
GCT2:
	puld
	
	
	ldab #1
	pshb
	ldab #1
	jsr getChar
	
	
	cmpb #'5'
	bne GCT2F
	
	
GCT2S:
	ldd #successMsg
	jsr printStr
	bra GCT3
GCT2F:
	ldd #failMsg
	
	
	; ------------
	; 
	; Test 3:
	; 	Input 
	; 			row	 	- 3
	;			column  - 3
	; 	Expected return 
	; 			In register B : 'F'
	;	
	; ------------
GCT3:
	puld
	
	ldab #3	
	pshb
	ldab #3
	jsr getChar
	
	cmpb #'F'
	bne GCT3F
	
		
GCT3S:
	ldd #successMsg
	jsr printStr
	bra quit
GCT3F:
	ldd #failMsg

quit:
	puld
	swi


#include util.asm
