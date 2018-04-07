
#ifndef KBI_I_H
#define KBI_I_H

#define uint8   unsigned char        //            typedef unsigned char         uint8; //  8 λ�޷�����
#define	uint16  unsigned short int   //            // 16 λ�޷�����
#define	uint32  unsigned long int   //            // 32 λ�޷�����


    #define KB_A                       PA   	      //PA��
    #define KB_P                       PP        	   //PTP��
   
    #define EnableKBint()             PIEH |= 0x0F    //���ż���(PTH0~3)�ж�
    #define DisableKBint()             PIEH &= ~0x0F //���μ���(PTPH~3)�ж�
  

    void  KBInit(void);          

   
    uint8 KBScan1(void); 
    
   
    uint8 KBDef(uint8 valve);  
    
   
    uint8 KBScanN(uint8 N);     
    
#endif     

