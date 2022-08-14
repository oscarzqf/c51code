#include<reg52.h>
sbit ENA=P1^5;
sbit IN1=P1^4;
sbit IN2=P1^3;
sbit IN3=P1^2;
sbit IN4=P1^1;
sbit ENB=P1^0;
#define uchar unsigned char
uchar flag,date;
void init()
{
TMOD=0X20;//��ʱ��1������ʽ����2
TH1=0xfd;
TL1=0xfd;//T1��ʱ��װ��ֵ
TR1=1;
SM0=0;
SM1=1;//�趨���ڹ�����ʽ1
REN=1;
EA=1;//���ж�
ES=1;//�����ж�
flag=0;
}
void run_()
{
IN1=1;
IN2=0; 
IN3=1;
IN4=0;
}
void back_()
{
 IN1=0;
 IN2=1;
 IN3=0;
 IN4=1;
}
void left_()
{
IN1=0;
IN2=1;
IN3=1;
IN4=0;
}
void right_()
{
IN1=1;
IN2=0;
IN3=0;
IN4=1;
}
void stop_()
{
ENA=0;
ENB=0;
}
void begin_()
{
ENA=1;
ENB=1;
}
void main()
{
init();
ENA=1;
ENB=1;
while(1)
{
if(flag==1)
{
switch(date)
{
	case 1 : run_(); break;
	case 2 : back_(); break;
	case 3 : left_(); break;
	case 4 : right_(); break;
	case 5 : stop_(); break;
	case 6 : begin_();break;
	default: break;
}
flag=0;
}
RI=1;
}
}
void ser() interrupt 4
{
RI=0;
date=SBUF;
flag=1; 
}