#include "hcs12dp256.h"
#include <stdio.h>


int optCount = 0;
int optEnabled = 0;	   	// Default to false;
unsigned  char  i;
unsigned  char  msg1[]="engine Speed:  nn   "          ;
 
 
 void DelayNX(int n)  //   
{
	int x;
	int y;
	while(n > 0)
	{
	  for(y=0; y<0x1; y++)
	  {
		for(x=0; x<0x7FF; x++)
		{
			asm("pshx");
			asm("pulx");
			asm("pshx");
			asm("pulx");
		}
	  }
		
	  n--;
	}
}



void stepper1(int n)   //   
   {     DDRT |= 0x60;
	 DDRP |= 0x20;
	 PTP  |= 0x20;
	
	//Spin Stepper Motor
	          
         PTT = 0x60;      
	for(i = 0; i < 10; i++)     
	{ 
		PTT = 0x60; DelayNX(n);
		PTT = 0x40; DelayNX(n);
		PTT = 0x00; DelayNX(n);
		PTT = 0x20; DelayNX(n);
	}
    }

void stepper2(int n)  
   {     
        DDRT |= 0x60;
	DDRP |= 0x20;
	PTP  |= 0x20;
	
	//Spin Stepper Motor
	
        PTT = 0x20;      
	for(i = 0; i < 10; i++)     
	{ 
		PTT = 0x20; DelayNX(n);
		PTT = 0x00; DelayNX(n);
		PTT = 0x40; DelayNX(n);
		PTT = 0x60; DelayNX(n);
	}
    }


/*#pragma interrupt_handler pacA_isr()
void pacA_isr(void)
{
	INTR_OFF();
	if (optEnabled) 
	{
	   optCount++;  
	   printf("%x ", optCount);
	}
	PAFLG |= 1;
	INTR_ON();
}

*/