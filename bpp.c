#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit beep=P3^6;
void delay(uint z)
{
uint x,y;
for(x=z;x>0;x--)
for(y=110;y>0;y--)
;
}
void main()
{
uchar i=255;
while(i){
beep=~beep;
delay(100);
i++;
}		
}