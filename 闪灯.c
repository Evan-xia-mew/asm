/*---------------------------------------------------------*/
/************************************************************
иа╣ф   MC9S12XS128
************************************************************/
/*---------------------------------------------------------*/
#include <MC9S12XS128.h>     
      

#define LEDCPU PORTK_PK4
#define LEDCPU_dir DDRK_DDRK4

void delay(void) 
{
   unsigned int i;
   for(i=0;i<50000;i++);
}

void main(void) 
{
  LEDCPU_dir=1;
	EnableInterrupts;
  for(;;) 
  {
      LEDCPU=1;
      delay();
      LEDCPU=0;
      delay();
  } 
}
