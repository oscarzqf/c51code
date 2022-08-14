#include<reg52.h>
#include<intrins.h>
#define uint unsigned int 
#define	uchar unsigned char
uchar temp; 
sbit beep=P2^3;
void delay_(uint z);
void main()
{ 
temp=0xfe;
while(1)
{
beep=0;
P1=temp;
temp=_crol_(temp,1);
delay_(100);
beep=1;

}

}

void delay_(uint z)
{
uint x,y;
for(x=z;x>0;x--)
for(y=110;y>0;y--)
;
}