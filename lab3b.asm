        org $2000
array dw $15,$12,$20,$7,$0,$3f,$1b,$fe,$f3,$68
N equ 10
max rmb 2
        org $3000
        ldaa array  ; set array[0] as the temporary max max
        staa max
        ldx #array+N-1
        ldab #N-1     ; set loop count to N - 1
loop
        ldaa	max
	cmpa	0,x
	bge	check
	ldaa	0,x
	staa	max
check	
        dex
	dbne	b,loop	   
forever	bra	forever
