
TRUE	= 1
FALSE	= 0

	
; void printHex (char hexNumber)
;   D (in B) is hexNumber, a number from 0..15
;
_printHex::
       andb  #$0f      ; mask off bits
       cmpb  #$09      ; compare to number
       bhi   above9    ; branch if a thru f
       addb  #$30      ; add standard offset
       bra hex
above9:
       addb  #$37      ; change a-f to ascii
hex:
       jsr   _printChar
       rts
	   
REGBS  = $0000 
SC0SR1 = REGBS+$CC
SC0DRL = REGBS+$CF

; void printChar( char character)
;    D (in B) is character.
_printChar::
 	pshd
here:   
    brCLR  SC0SR1,#$80,here
;	LDAB	SC0SR1	; read status
;	BITB	#$80  	; test Transmit Data Register Empty bit
;	BEQ	OUTSCI2	; loop if TDRE=1
;	ANDA	#$7F   	; mask parity
	STAB	SC0DRL	; send character
	puld
    rts
		 
; void printStr( char* string)
;    D contains address of null-terminated string.
_printStr::
     pshd
     pshy
	 xgdy
nextCharInStr:
	 ldab 1,y+
	 cmpb #0x00
	 beq printStrDone
	 jsr _printChar	
	bra nextCharInStr
printStrDone:
    puly
	puld
    rts

_convertToDecimal::
	pshy
	pshx
	leas -4,sp
	movw #0, 0,sp ;initialize local variable to 0
	std 2,sp
	xgdy

;Register Y now contains the adress to the start of the string

	ldx #0 ;prepare reg x to hold the count of digits in the string

countNextDigit:
	ldab 1,y+
	cmpb #0x00
	beq getXMultiplier
	inx
	jmp countNextDigit

;Register X now contains the number of digits in the string

getXMultiplier:
	ldd #1
MultiplyX:
	ldy #10
	cpx #1
	beq doneMultiply
	emul
	dex	
	jmp MultiplyX	
doneMultiply:
	xgdy ; put multiplier in Y
	ldd 2,sp
	xgdx

;Register X now contains the adress to the start of the string
;Register Y now contains the multiplifer for the 1st digit

convertNextChar:
	ldab 1,x+
	cmpb #0x00
	beq convertToDecDone
	subb #$30 ;get the Value that the character represents
	ldaa #0; want d to contain only b	
	pshy
	emul
	puly
	addd 0,sp
	std 0,sp ;The decimal value has gone to the local variable
	xgdy
	xgdx
	xgdy ;swap X and Y, X now has the Multiplier, Y now has the Adress of The next byte 
	xgdx  ;D has multiplier
	ldx #10 
	idiv ; D/X -> X   == Multiplier/10 = New Multiplier	
	xgdy
	xgdx
	xgdy ;swap X and Y, X now has the NEW Multiplier, Y now has the Adress of The next byte 	
	jmp convertNextChar

convertToDecDone:
	ldd 0,sp
	leas 4, sp
	pulx
	puly
	rts

_convertToString::
	
	;char num is in register D

	pshx
	pshy
	pshd

	ldy 8,sp
	ldx #100
	idiv	;D contains the remainder
		;X contains the result
	xgdx	;Swap D,X so D = result, X = remainder
	addd #$30	;add 30 to make the number into a char ascii representation
	stab 0,y ;store b into first char of the string
	xgdx ;swap back so that X = result,  D=remainder

	ldx #10 ;repeat with Divisor =10
	idiv	;D contains the remainder
		;X contains the result
	xgdx	;Swap D,X so D = result, X = remainder
	addd #$30	;add 30 to make the number into a char ascii representation
	stab 1,y ;store b into first char of the string
	xgdx ;swap back so that X = result,  D=remainder

	addd #$30
	stab 2,y ;store last digit in sp

	ldab #0
	stab 3,y ;store terminator in last position of the string
	
	puld
	puly
	pulx
	rts

_getRowColumn::

	pshx
	pshy
	pshd

		
findLow:
	psha
	pshb
	pula
	pulb		;swap a, b   a = code
	anda #$0F	; Optional, depends on following code
	ldab #0		; Location of 1st one, counting from 0 .. 3
	
	ldy #4		; for (y=4;y>0;y--)
nextBit1:		; { Find the 1st bit that is set to one
	lsra		;	Shift RIGHT to inspect the LOW four bits, so that one bit falls into carry
	bcs firstOne1	;	If the carry is set, we have found one set bit.
	incb
	dbne y, nextBit1; }
	ldab #-1	; If we get here, no set bits have been found. Invalid pattern in the low nibble
	bra findHigh
firstOne1:		; Having found the first set bit, are there more ?
	lsra		; Continue shifting the rest of the bits.
	bcs another1	; If find another, invalid pattern in the low nibble.
	dbne y, firstOne1
	bra findHigh
another1:
	ldab #-1

findHigh:		; Repeat the same but for the high nibble. This time, shift LEFT to inspect the HIGH four bits
	ldy 8,sp
	stab 0,y

	ldd 0, sp
	psha
	pshb
	pula
	pulb	;swap a,b  a = code
	anda #$F0	
	ldab #3
	
	ldy #4		
nextBit2:
	lsla		
	bcs firstOne2
	decb
	dbne y, nextBit2
	ldab #-1
	bra doneEx2
firstOne2:
	lsla
	bcs another2
	dbne y, firstOne2
	bra doneEx2
another2:
	ldab #-1	
doneEx2:
	
	ldy 10,sp
	stab 0,y

	puld
	puly
	pulx
	
	rts
	
keypad: .ascii "123a456b789ce0fd"
_getChar::

	pshx
	pshy

	leas -2,sp

	ldaa #0
	xgdy ;Y = Row
	ldd #4 ;D = Col Size
	emul ;D=Row*ColSize
	xgdy ; Y = Row*ColSize
	ldab 9, sp
	ldaa #0 ; D =COLUMN
	sty 0,sp
	addd 0,sp ;D = (rowsize*col)+row
	addd #keypad 

	tfr d,x

	ldab 0,x ;B contains ascii char corresponding to row and col

	leas 2,sp
	puly
	pulx

	rts
EOF