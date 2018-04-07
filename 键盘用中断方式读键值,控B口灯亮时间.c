/*---------------------------------------------------------*/
/************************************************************
����  MC9S12XS128 
 �ĸ�key1,key2,key3,key4
���жϷ�ʽ����ֵ,���̿�B�ڵ���ʱ��
************************************************************/
/*---------------------------------------------------------*/
#include <MC9S12XS128.h>      /* common defines and macros */
 
#define LED PORTB
#define LED_dir DDRB
#define KEY1 PTIH_PTIH3
#define KEY2 PTIH_PTIH2
#define KEY3 PTIH_PTIH1
#define KEY4 PTIH_PTIH0
#define KEY1_dir DDRH_DDRH3
#define KEY2_dir DDRH_DDRH2
#define KEY3_dir DDRH_DDRH1
#define KEY4_dir DDRH_DDRH0

unsigned char data=0x01;

unsigned char direction=1;   //���õ����ķ���0����1���ҡ�
unsigned char time=5;        //���õ������ٶȡ�

/*************************************************************/
/*                        ��ʱ����                           */
/*************************************************************/
void delay(unsigned int n) 
{
  unsigned int i,j;
  for(j=0;j<n;j++)
  for(i=0;i<40000;i++)
  ;
}

/*************************************************************/
/*                      ��ʼ��LED��                          */
/*************************************************************/
void init_led(void) 
{
  LED_dir=0xff;       //����Ϊ���
  LED=~data;          //����LED1
}

/*************************************************************/
/*                       ��ʼ������                          */
/*************************************************************/
void init_key(void) 
{
     KEY1_dir =0;       //����Ϊ����
     KEY2_dir=0;
     KEY3_dir=0;
     KEY4_dir=0;
     PPSH = 0x00;		      //����ѡ��Ĵ���,ѡ���½���;
     PIFH = 0x0f;					//��PIFH��ÿһλд1�������־λ;
     PIEH = 0x0f;		      //�ж�ʹ�ܼĴ���;
}

/*************************************************************/
/*                    �����жϺ���                           */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_inter(void) 
{
   if(PIFH != 0)     //�ж��жϱ�־
   {
      PIFH = 0xff;     //����жϱ�־
      if(KEY1 == 0)         //����1����
      {
          time-=1;
          if(time==0)
              time=1;
      }
      if(KEY2 == 0) 
      {
          time+=1;
          if(time>10)
              time=10;
      }
      if(KEY3 == 0)
          direction=0;
      if(KEY4 == 0)
          direction=1;
   }
}
#pragma CODE_SEG DEFAULT


/*************************************************************/
/*                         ������                            */
/*************************************************************/
void main(void) {
	DisableInterrupts;
  init_led();
  init_key();
	EnableInterrupts;


  for(;;) 
  {
      delay(time);
      if(direction==1)
      {
          data=data<<1;         //����һλ
          if(data==0)
              data=0x01;
      } 
      else 
      {
          data=data>>1;         //����һλ
          if(data==0)
              data=0x80;
      }
      
      LED = ~data;
  } 
}