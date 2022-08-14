#include<reg52.h>
#include <stdio.h>              //printf头文件  
#define uchar unsigned char   
#define uint unsigned int  
unsigned char receiveData;         
sbit ENA=P1^5;
sbit IN1=P1^4;
sbit IN2=P1^3;
sbit IN3=P1^2;
sbit IN4=P1^1;
sbit ENB=P1^0;  
void init()  
{  
    TMOD=0x20;    //定时器工作方式，选择了定时器1，工作方式2 八位初值自动重装的8位定时器。          
    TH1=0xfd;     //定时器1初值  ,设置波特率为9600 晶振11.0529MHZ?  
    TL1=0xfd;  
    TR1=1;        //开启定时器1  
  
    SM0=0;  
    SM1=1;        //10位异步接收，（8位数据）波特率可变  
    REN=1;        //允许串行口接收位  
    EA=1;         //允许中断（总闸）  
    ES=1;         //允许串口中断  
} 
void go_()
{
ENA=1;
ENB=1;
IN1=1;
IN2=0;
IN3=1;
IN4=0;
}
void back_()
{
ENA=1;
ENB=1;
IN1=0;
IN2=1;
IN3=0;
IN4=1;
} 
void left_()
{
ENA=1;
IN1=0;
IN2=1;
ENB=1;
IN3=1;
IN4=0;
}
void right_()
{
ENA=1;
IN1=1;
IN2=0;
ENB=1;
IN3=0;
IN4=1;
}
void main()  
{  
	init();     
	while(1)  
{  


	 if(receiveData=='G')
	 { go_(); }
	 if(receiveData=='B')
	 { back_(); }
	 if(receiveData=='L')
	 {left_();}
	 if(receiveData=='R')
	 {right_();}
	 }  
}  
  
void ser() interrupt 4  
{  	 


	receiveData=SBUF; //出去接收到的数据
	RI = 0;           //清除接收中断标志位
	SBUF=receiveData; //将接收到的数据放入到发送寄存器
	while(!TI);		  //等待发送数据完成
	TI=0;			  //清除发送完成标志位
 
}  
