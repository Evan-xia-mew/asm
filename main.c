
#include "hcs12dp256.h"
#include "steepper.h"

#define EnableInterrupt()  asm("CLI")  //�������ж�
#define DisableInterrupt() asm("SEI")  //��ֹ���ж�


#define uint8   unsigned char        //            typedef unsigned char         uint8; //  8 λ�޷�����
#define	uint16  unsigned short int   //            // 16 λ�޷�����
#define	uint32  unsigned long int   //            // 32 λ�޷�����
 


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







