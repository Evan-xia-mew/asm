
#ifndef KBI_I_H
#define KBI_I_H

#define uint8   unsigned char        //            typedef unsigned char         uint8; //  8 位无符号数
#define	uint16  unsigned short int   //            // 16 位无符号数
#define	uint32  unsigned long int   //            // 32 位无符号数


    #define KB_A                       PA   	      //PA口
    #define KB_P                       PP        	   //PTP口
   
    #define EnableKBint()             PIEH |= 0x0F    //开放键盘(PTH0~3)中断
    #define DisableKBint()             PIEH &= ~0x0F //屏蔽键盘(PTPH~3)中断
  

    void  KBInit(void);          

   
    uint8 KBScan1(void); 
    
   
    uint8 KBDef(uint8 valve);  
    
   
    uint8 KBScanN(uint8 N);     
    
#endif     

