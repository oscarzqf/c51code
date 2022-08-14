#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar temp,numdu,aa,numwe;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code tabledu[]={  0x3f,0x06,0x5b,0x4f,
  					  0x66,0x6d,0x7d,0x07,
					  0x7f,0x6f,0x77,0x7c,
					  0x39,0x5e,0x79,0x71};
uchar code tablewe[]={ 
						0xfe,0xfd,0xfb,0xf7,0xef,0xdf
					}  ;
void main()
{
aa=0;
numwe=0;
numdu=0;
TMOD=0x01;
TH0=(65556-50000)/256;
TL0=(65556-50000)%256;
EA=1;
ET0=1;
TR0=1;
while(1)
{
	if(aa==20)
{
aa=0;
dula=1;
P0=tabledu[numdu];
dula=0;
numdu++;
if(numdu==8)
numdu=0;
wela=1;
P0=tablewe[numwe];
wela=0;
numwe++;
if(numwe==6)
numwe=0;
}

}


}

void timer() interrupt 1
{
TH0=(65556-50000)/256;
TL0=(65556-50000)%256;
aa++;
}