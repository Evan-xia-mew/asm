/*---------------------------------------------------------*/
/************************************************************
����������ѯ��ʽ����ֵ��B�ڵ�  MC9S12XS128 
KEY1��H��3  KEY1���µ���
KEY2��H��2  KEY2���µ���
************************************************************/
/*---------------------------------------------------------*/
#include <MC9S12XS128.h>      /* common defines and macros */
 
#define LED PORTB
#define LED_dir DDRB
#define KEY1 PTIH_PTIH3
#define KEY2 PTIH_PTIH2
#define KEY1_dir DDRH_DDRH3
#define KEY2_dir DDRH_DDRH2

unsigned char data=0x01;
unsigned char mode=1;
unsigned char KEY1_last=1;
unsigned char KEY2_last=1;


/*************************************************************/
/*                        ��ʱ����                           */
/*************************************************************/
void delay(void) 
{
  unsigned int i,j;
  for(j=0;j<2;j++)
  for(i=0;i<60000;i++)
  ;
}

/*************************************************************/
/*                      ��ʼ���ƺͰ���                       */
/*************************************************************/
void init_led_key(void) 
{
  LED_dir=0xff;       //����Ϊ���
  LED=~data;          //����LED1
  KEY1_dir=0;           //����Ϊ����
  KEY2_dir=0;           //����Ϊ����
}


/*************************************************************/
/*                          ������                           */
/*************************************************************/
void main(void) {
	DisableInterrupts;   //  #define DisableInterrupts  asm("sei") 
  init_led_key();	
        EnableInterrupts;    //  #define EnableInterrupts   asm("cli") 


  for(;;) 
  {
      delay();
      data=data<<1;         //����һλ
      if(data==0)
          data=0x01;
      if(KEY1==0&&KEY1_last==1)   //����F1����
          mode=1;
      if(KEY2==0&&KEY2_last==1)   //����F2����
          mode=2;          
      KEY1_last=KEY1;             //����F1��״̬
      KEY2_last=KEY2;             //����F2��״̬
      if(mode==1)
          LED = ~data;
      else
          LED = data;
  } 
}