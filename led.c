#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar temp;
void delay(uint z);
void main()
{
temp=0xfe;
while(1)
{
P1=temp;
temp=_crol_(temp,1);
delay(20);
}
}
void delay(uint z)
{
uint x,y;
for(x=z;x>0;x--)
for(y=110;y>0;y--)
;
}