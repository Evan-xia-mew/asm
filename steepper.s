	.module steepper.c
	.area data
_optCount::
	.blkb 2
	.area idata
	.word 0
	.area data
_optEnabled::
	.blkb 2
	.area idata
	.word 0
	.area data
_msg1::
	.blkb 21
	.area idata
	.byte 'e,'n,'g,'i,'n,'e,32,'S,'p,'e,'e,'d,58,32,32,'n
	.byte 'n,32,32,32,0
	.area data
	.area text
;              y -> 0,SP
;              x -> 2,SP
;              n -> 4,SP
_DelayNX::
	pshd
	leas -4,S
; #include "hcs12dp256.h"
; #include <stdio.h>
; 
; 
; int optCount = 0;
; int optEnabled = 0;	   	// Default to false;
; unsigned  char  i;
; unsigned  char  msg1[]="engine Speed:  nn   "          ;
;  
;  
;  void DelayNX(int n)  //   
; {
	bra L5
L4:
; 	int x;
; 	int y;
; 	while(n > 0)
; 	{
; 	  for(y=0; y<0x1; y++)
	movw #0,0,S
L7:
; 	  {
; 		for(x=0; x<0x7FF; x++)
	movw #0,2,S
L11:
; 		{
; 			asm("pshx");
	pshx
; 			asm("pulx");
	pulx
; 			asm("pshx");
	pshx
; 			asm("pulx");
	pulx
; 		}
L12:
	ldy 2,S
	iny
	sty 2,S
	cpy #2047
	blt L11
; 	  }
L8:
	ldy 0,S
	iny
	sty 0,S
	cpy #1
	blt L7
; 		
; 	  n--;
	ldy 4,S
	dey
	sty 4,S
; 	}
L5:
	ldy 4,S
	cpy #0
	bgt L4
L3:
	.dbline 0 ; func end
	leas 6,S
	rts
;              n -> 0,SP
_stepper1::
	pshd
; }
; 
; 
; 
; void stepper1(int n)   //   
;    {     DDRT |= 0x60;
	bset 0x242,#96
; 	 DDRP |= 0x20;
	bset 0x25a,#32
; 	 PTP  |= 0x20;
	bset 0x258,#32
; 	
; 	//Spin Stepper Motor
; 	          
;          PTT = 0x60;      
	movb #96,0x240
; 	for(i = 0; i < 10; i++)     
	clr _i
	bra L19
L16:
; 	{ 
; 		PTT = 0x60; DelayNX(n);
	movb #96,0x240
	ldd 0,S
	jsr _DelayNX
; 		PTT = 0x40; DelayNX(n);
	movb #64,0x240
	ldd 0,S
	jsr _DelayNX
; 		PTT = 0x00; DelayNX(n);
	clr 0x240
	ldd 0,S
	jsr _DelayNX
; 		PTT = 0x20; DelayNX(n);
	movb #32,0x240
	ldd 0,S
	jsr _DelayNX
; 	}
L17:
	inc _i
L19:
	ldab _i
	cmpb #10
	blo L16
L15:
	.dbline 0 ; func end
	leas 2,S
	rts
;              n -> 0,SP
_stepper2::
	pshd
;     }
; 
; void stepper2(int n)  
;    {     
;         DDRT |= 0x60;
	bset 0x242,#96
; 	DDRP |= 0x20;
	bset 0x25a,#32
; 	PTP  |= 0x20;
	bset 0x258,#32
; 	
; 	//Spin Stepper Motor
; 	
;         PTT = 0x20;      
	movb #32,0x240
; 	for(i = 0; i < 10; i++)     
	clr _i
	bra L24
L21:
; 	{ 
; 		PTT = 0x20; DelayNX(n);
	movb #32,0x240
	ldd 0,S
	jsr _DelayNX
; 		PTT = 0x00; DelayNX(n);
	clr 0x240
	ldd 0,S
	jsr _DelayNX
; 		PTT = 0x40; DelayNX(n);
	movb #64,0x240
	ldd 0,S
	jsr _DelayNX
; 		PTT = 0x60; DelayNX(n);
	movb #96,0x240
	ldd 0,S
	jsr _DelayNX
; 	}
L22:
	inc _i
L24:
	ldab _i
	cmpb #10
	blo L21
L20:
	.dbline 0 ; func end
	leas 2,S
	rts
	.area bss
_i::
	.blkb 1
