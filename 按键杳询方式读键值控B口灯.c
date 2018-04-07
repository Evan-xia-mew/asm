/*---------------------------------------------------------*/
/************************************************************
独立按键杳询方式读键值控B口灯  MC9S12XS128 
KEY1接H口3  KEY1按下灯亮
KEY2接H口2  KEY2按下灯灭
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
/*                        延时函数                           */
/*************************************************************/
void delay(void) 
{
  unsigned int i,j;
  for(j=0;j<2;j++)
  for(i=0;i<60000;i++)
  ;
}

/*************************************************************/
/*                      初始化灯和按键                       */
/*************************************************************/
void init_led_key(void) 
{
  LED_dir=0xff;       //设置为输出
  LED=~data;          //点亮LED1
  KEY1_dir=0;           //设置为输入
  KEY2_dir=0;           //设置为输入
}


/*************************************************************/
/*                          主函数                           */
/*************************************************************/
void main(void) {
	DisableInterrupts;   //  #define DisableInterrupts  asm("sei") 
  init_led_key();	
        EnableInterrupts;    //  #define EnableInterrupts   asm("cli") 


  for(;;) 
  {
      delay();
      data=data<<1;         //左移一位
      if(data==0)
          data=0x01;
      if(KEY1==0&&KEY1_last==1)   //按键F1按下
          mode=1;
      if(KEY2==0&&KEY2_last==1)   //按键F2按下
          mode=2;          
      KEY1_last=KEY1;             //保存F1的状态
      KEY2_last=KEY2;             //保存F2的状态
      if(mode==1)
          LED = ~data;
      else
          LED = data;
  } 
}