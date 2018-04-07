
/* 广州手之创电子科技有限公司
公司网址首页：http://www.soochange.com
              http://www.sochange.cn
公司淘宝网店：http://sochange.taobao.com/
联系电话（传真）：020-62199826
联系电话：020-28991152
公司官方qq(添加好友者请写上贵公司名称，本q只对企业客户开发):779827265
技术qq1:956626567
技术qq2:974205767

步进电机同点阵都是比较耗电，使用步进电机前请取下点阵
*/

#include <reg52.h>
sbit A1=P1^4; //定义步进电机连接端口
sbit B1=P1^3;
sbit C1=P1^2;
sbit D1=P1^1;


void qudong1();



#define Dy_A1 {A1=1;B1=0;C1=0;D1=0;}//A相通电，其他相断电
#define Dy_B1 {A1=0;B1=1;C1=0;D1=0;}//B相通电，其他相断电
#define Dy_C1 {A1=0;B1=0;C1=1;D1=0;}//C相通电，其他相断电
#define Dy_D1 {A1=0;B1=0;C1=0;D1=1;}//D相通电，其他相断电	   //采用1相励磁


#define Dy_OFF {A1=0;B1=0;C1=0;D1=0;}//全部断电


unsigned char Speed;
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS 
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //大致延时1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{




 Dy_OFF


 for(;;)
 {
   qudong1();
 
  }
}

void qudong1()
{

 unsigned int i=470;//旋转一周时间
  Speed=5;
  while(i--)  //正向
  {         
     Dy_A1                //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
     DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
                             //数字越小，转速越大,力矩越小
     Dy_B1					 //顺序从A1--D1相通电如果为正转，那么顺序从D1--A1相通电则为反转
     DelayMs(Speed);
     Dy_C1
     DelayMs(Speed);
     Dy_D1
     DelayMs(Speed);
  }
 Dy_OFF
  i=512;
  while(i--)//反向
  {
     Dy_D1                //遇到Coil_A1  用{A1=1;B1=0;C1=0;D1=0;}代替
     DelayMs(Speed);         //改变这个参数可以调整电机转速 ,
	                         //数字越小，转速越大,力矩越小
     Dy_C1
     DelayMs(Speed);
     Dy_B1
     DelayMs(Speed);
     Dy_A1
     DelayMs(Speed); 
  }	    
}



