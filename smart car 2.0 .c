#include<reg52.h>
#include <stdio.h>              //printfͷ�ļ�  
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
    TMOD=0x20;    //��ʱ��������ʽ��ѡ���˶�ʱ��1��������ʽ2 ��λ��ֵ�Զ���װ��8λ��ʱ����          
    TH1=0xfd;     //��ʱ��1��ֵ  ,���ò�����Ϊ9600 ����11.0529MHZ?  
    TL1=0xfd;  
    TR1=1;        //������ʱ��1  
  
    SM0=0;  
    SM1=1;        //10λ�첽���գ���8λ���ݣ������ʿɱ�  
    REN=1;        //�����пڽ���λ  
    EA=1;         //�����жϣ���բ��  
    ES=1;         //�������ж�  
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


	receiveData=SBUF; //��ȥ���յ�������
	RI = 0;           //��������жϱ�־λ
	SBUF=receiveData; //�����յ������ݷ��뵽���ͼĴ���
	while(!TI);		  //�ȴ������������
	TI=0;			  //���������ɱ�־λ
 
}  
