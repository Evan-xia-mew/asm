
// KBI_I.c                                                           *

#include "hcs12dp256.h"
     #include         "KBI_I.h"                  
#define uint8   unsigned char        //            typedef unsigned char         uint8; //  
#define	uint16  unsigned short int   //            //
#define	uint32  unsigned long int   //            // 
	
	

    void KBInit(void)
    {
    
        PTH=0X00;     
        DDRH=0XFF;     
                
        DDRP=0X00; 
        PTP=0X00;         
                        
               
        PPSH=0X00;     
        
        PIEH &= ~0x0F     ; //DisableKBint();                   
        PIFH=0X0F ;        
		
		EnableKBint();                                 
    }

   
    uint8 KBScan1(void) 
    {
        uint8 line,i,tmp;
        
        line=0b00000001;            
        for (i = 1; i <= 4; i++)    
        {
            
            PTP=line;

            asm("NOP");
            asm("NOP");
            

            
            tmp  = PTH;
            
           
            if ((tmp & 0xF0)!= 0x00)     
    	    {
                break;            
            }
            else                  
                line = (line << 1); 
        }
        if (i == 5)        
            tmp = 0xff;
        return (tmp);  
    }
    
	
    const uint8 KBTable[] =
    {
        0x11,'1',0x21,'2',0x41,'3',0x81,'A',
        0x12,'4',0x22,'5',0x42,'6',0x82,'B',
        0x14,'7',0x24,'8',0x44,'9',0x84,'C',
        0x18,'E',0x28,'0',0x48,'F',0x88,'D',
        0x00
    };
    uint8 KBDef(uint8 valve)
    {
        uint8 KeyPress;            
        uint8 i;
        i = 0;
        KeyPress = 0xff;
        while (KBTable[i] != 0x00) 
        {
            if(KBTable[i] == valve) 
            {
                KeyPress = KBTable[i+1];  
                break;
            }
            i += 2;                       
        }
        return KeyPress;
    }

  
    uint8 KBScanN(uint8 KB_count)
    {
        uint8 i,KB_value_last,KB_value_now;
        
        if (0 == KB_count || 1 == KB_count)
            return KBScan1();   
        KB_value_now = KB_value_last = KBScan1();   
        
        for (i=0; i<KB_count-1; i++)
        {               
            KB_value_now = KBScan1();
            if (KB_value_now == KB_value_last)
                return KB_value_now;                      
            else
                KB_value_last = KB_value_now;
                
        }
      
        return 0xFF;
    }
