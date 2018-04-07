/*---------------------------------------------------------*/
/************************************************************
键盘  MC9S12XS128 
 四个key1,key2,key3,key4
用中断方式读键值,键盘控B口灯亮时间
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

unsigned char direction=1;   //设置灯亮的方向，0向左，1向右。
unsigned char time=5;        //设置灯闪的速度。

/*************************************************************/
/*                        延时函数                           */
/*************************************************************/
void delay(unsigned int n) 
{
  unsigned int i,j;
  for(j=0;j<n;j++)
  for(i=0;i<40000;i++)
  ;
}

/*************************************************************/
/*                      初始化LED灯                          */
/*************************************************************/
void init_led(void) 
{
  LED_dir=0xff;       //设置为输出
  LED=~data;          //点亮LED1
}

/*************************************************************/
/*                       初始化按键                          */
/*************************************************************/
void init_key(void) 
{
     KEY1_dir =0;       //设置为输入
     KEY2_dir=0;
     KEY3_dir=0;
     KEY4_dir=0;
     PPSH = 0x00;		      //极性选择寄存器,选择下降沿;
     PIFH = 0x0f;					//对PIFH的每一位写1来清除标志位;
     PIEH = 0x0f;		      //中断使能寄存器;
}

/*************************************************************/
/*                    按键中断函数                           */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt void PTH_inter(void) 
{
   if(PIFH != 0)     //判断中断标志
   {
      PIFH = 0xff;     //清除中断标志
      if(KEY1 == 0)         //按键1按下
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
/*                         主函数                            */
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
          data=data<<1;         //左移一位
          if(data==0)
              data=0x01;
      } 
      else 
      {
          data=data>>1;         //右移一位
          if(data==0)
              data=0x80;
      }
      
      LED = ~data;
  } 
}