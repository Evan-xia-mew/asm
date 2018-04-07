;Test Program That Tests My Util.Asm Functions

#include "util.asm"

	org $1000

;----------------------------------
stringTEST db 'T','E','S','T',0
stringS12C db 'S','1','2','C',0
;----------------------------------
string1 db '1','2','3',0
string2 db '3','2','1',0
;----------------------------------
stringNum rmb 1
string3 db '9','9','9','9'
;----------------------------------
row1 rmb 1
column1 rmb 1
row2 rmb 1
column2 rmb 1
;----------------------------------
r1 db 2
c1 db 3
getChar1 db 0;If set to 1 at end of test, then the test worked properly. Test failed otherwise
r2 db 0
c2 db 2
getChar2 db 0;If set to 1 at end of test, then the test worked properly. Test failed otherwise
;----------------------------------



	org $4000

	lds #$3dff

	;****************************************************************
	;Note: The print functions must be tested using the board	;
	;	NOT the simulator					;
	;****************************************************************

	;Testing printHex
	
	ldab #15;
	jsr printHex ;should print 'F'

	ldab #11;
	jsr printHex ;should print 'B'

	ldab #0
	jsr printHex ;should print '0'

	;Testing printChar

	ldab #$43
	jsr printChar ;should print 'C'

	ldab #$23
	jsr printChar ;should print '#'

	ldab #$32
	jsr printChar ;should see '2'

	;Test printString

	ldd #stringTEST
	jsr printStr ;should see "TEST"

	ldd #stringS12C
	jsr printStr ;should see "S12C"

	;Testing convertToDecimal Function

	ldd #string1
	jsr convertToDecimal
	cpd #123
	bne doNothing1
	ldab #1
	jsr printHex ;If test passes, print 1

doNothing1:

	ldd #string2
	jsr convertToDecimal
	cpd #321
	bne doNothing2
	ldab #1
	jsr printHex ;If test passes, print 1

doNothing2:

	;Testing convertToString Function

	ldx #string3
	pshx	
	ldaa #0
	movb #3, stringNum
	ldab stringNum
	jsr convertToString
	leas 2, sp
	ldd #string3
	jsr printStr ;Print the string and verify if it is 003

doNothing3:

	ldx #string3
	pshx	
	ldaa #0
	movb #53, stringNum
	ldab stringNum
	jsr convertToString
	leas 2, sp
	ldd #string3
	jsr printStr ;Print the string and verify if it is 053

doNothing4:

	ldx #string3
	pshx	
	ldaa #0
	movb #123, stringNum
	ldab stringNum
	jsr convertToString
	leas 2, sp
	ldd #string3
	jsr printStr ;Print the string and verify if it is 123

doNothing5:

	;Testing getRowColumn


	ldx #column1
	pshx
	ldx #row1
	pshx
	ldab #%10001000 ;Load register B with code for column 3, row 3
	jsr getRowColumn
	leas 4,sp
	cmpb #$ff
	beq doNothing6
	ldab #$50
	jsr printChar; If test passes, print a P
	ldab row1
	jsr printHex ;should print 3
	ldab column1
	jsr printHex ;should print 3

doNothing6:


	ldx #column2
	pshx
	ldx #row2
	pshx
	ldab #%01000010 ;Load register B with code for column 2, row 1
	jsr getRowColumn
	leas 4,sp
	cmpb #$ff
	beq doNothing7
	ldab #$50
	jsr printChar; If test passes, print a P
	ldab row2
	jsr printHex ;should print 1
	ldab column2
	jsr printHex ;should print 2

doNothing7:

	;Testing getChar

	ldab c1
	pshb
	ldab r1
	jsr getChar
	leas 1, sp
	cmpb #'c'
	bne doNothing8
	jsr printChar ;should print 'c'

doNothing8:

	ldab c2
	pshb
	ldab r2
	jsr getChar
	leas 1, sp
	cmpb #'3'
	bne doNothing9
	jsr printChar ;should print '3'


doNothing9:

	swi
