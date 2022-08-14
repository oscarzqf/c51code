#include<reg52.h>
#define uint unsigned int																	  dula=1;
P0=table[num-1];
dula=0;
#define uchar unsigned char
sbit dula=P2^6;
sbit wela=P2^7;
uchar temp,num;
uchar code table[]={  0x3f,0x06,0x5b,0x4f,
  					  0x66,0x6d,0x7d,0x07,
					  0x7f,0x6f,0x77,0x7c,
					  0x39,0x5e,0x79,0x71};
void delay(uint z);
void main()
{
wela=1;
P0=0xc0;
wela=0;
while(1)
{
P3=0xfe;
temp=P3;
temp=temp&0xf0;
while(temp!=0xf0)//按下检测第一行
{
delay(5);
temp=P3;
temp=temp&0xf0;
while(temp!=0xf0)
{
temp=P3;
switch(temp)
{
           case 0xee : num=1;  break;
		   case 0xde : num=2;  break;
		   case 0xbe : num=3;  break;
		   case 0x7e : num=4;  break;
}
while(temp!=0xf0)	 //松手检测第一行
{
temp=P3;
temp=temp&0xf0;
}
dula=1;
P0=table[num-1];
dula=0;
}
}
}
}

void delay(uint z)
{uint x,y;
for(x=z;x>0;x++)
for(y=110;y>0;y++);
}