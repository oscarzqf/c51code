#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar num;
void delay(uint z);  
uchar code table[]={  0x3f,0x06,0x5b,0x4f,
  					  0x66,0x6d,0x7d,0x07,
					  0x7f,0x6f,0x77,0x7c,
					  0x39,0x5e,0x79,0x71};
sbit d1=P1^0;
sbit key1=P3^4;	//按键1
sbit dula=P2^6;
sbit wela=P2^7;

void main()
{
P3=0xff;
num=0;
wela=1;
P0=0xfe;
wela=0;
while(1)
{
if(key1==0)	//按键检测
{
delay(5);// 消除按下抖动
if(key1==0)	 //再次检测防误触
{
d1=0;
num++;
if(num==10)	//10次回零
num=0;
}
while(!key1);//松手等待按键释放
delay(5); //松手消抖
}																	
else
{
d1=1;
}
dula=1;
P0=table[num];
dula=0;
}
}		
void delay(uint z)
{uint x,y;
for(x=z;x>0;x++)
for(y=110;y>0;y++);
}
