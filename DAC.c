#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar flag,a;
void ser();
void init();
int main(void)
{
 init();
 while(1)
 {
 if(flag==1)
 {
 ES=0;
 SBUF=a;
 while(!TI);	
 ES=1;
 flag=0;

 }
 }
}
void ser() interrupt 4
{
a=SBUF;
flag=1;
RI=0;
}
void init()
{
flag=0;
TMOD=0x20;//定时器工作方式2
TH1=0xfd;
TL1=0xfd;
TR1=1;
EA=1;
ES=1;
SM0=0;
SM1=1;
REN=1;
}