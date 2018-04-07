
#include "hcs12dp256.h"
#include "steepper.h"

#define EnableInterrupt()  asm("CLI")  //开放总中断
#define DisableInterrupt() asm("SEI")  //禁止总中断


#define uint8   unsigned char        //            typedef unsigned char         uint8; //  8 位无符号数
#define	uint16  unsigned short int   //            // 16 位无符号数
#define	uint32  unsigned long int   //            // 32 位无符号数
 


void main(void)
{
        
 
    DisableInterrupt();  
       
   
    KBInit();                                      

   
    //    EnableKBint();                               
    EnableInterrupt();                            
    
  
    while(1)
     { 
     }


}







