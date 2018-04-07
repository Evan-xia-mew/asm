//#include <stdio.h>
#include <hcs12dp256.h>

void delay(long int n){
long int i;
for(i=0;i<n;i++){
		asm("pshx");
		asm("pulx");
		asm("pshx");
		asm("pulx");
	}
}

void main()
{

DDRK = 0x0F;
PORTK = 0x00;
PORTK = PORTK | 0x01;
delay(100000);
PORTK = PORTK | 0x02;
delay(100000);
PORTK = 0x0C;
delay(100000);
PORTK = 0x00; 
 }
 