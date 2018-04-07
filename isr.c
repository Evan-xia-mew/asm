
#include "steepper.h"
#include "hcs12dp256.h"
#include         "KBI_I.h"                  

#define uint8   unsigned char        //            typedef unsigned char         uint8; 
#define	uint16  unsigned short int   //           
#define	uint32  unsigned long int   //            
 
 #define EnableInterrupt()  asm("CLI") ; 
#define DisableInterrupt() asm("SEI")  ;

 // #define EnableKBint()  ( PIEH |= 0x0F );   
 //#define DisableKBint() ( PIEH &= ~0x0F);   
   
    
   // #pragma CODE_SEG __NEAR_SEG NON_BANKED
    



    void isr_default(void)//__interrupt void isr_default(void)
    {   
       DisableInterrupt();
       EnableInterrupt();
    }

    void isrKeyBoard(void)//__interrupt void isrKeyBoard(void)
    {   
        
        uint8 valve,dr;
        uint16 i,speed;
        DisableInterrupt();
        DisableKBint();

        speed=5;
	    dr=0;
        for (i=0 ; i<20000; i++);              
        {
		valve = KBScanN(10);
		 }                         
        switch(valve)
	{

		case 1:speed=5; break;
		case 2:speed=10; break;
		case 3:speed=20; break;
		    
        case 'A':dr=(dr+1)&0x01;break;
		 
                default:break;

		
	}
         switch(dr)
		 {

		case 1:stepper1(speed) ; break;
		case 2:stepper2(speed) ;  break;
		          
         }
        KBInit();                                    
        EnableKBint(); 		                            
        EnableInterrupt();                          
    }
    
   // #pragma CODE_SEG DEFAULT

      





