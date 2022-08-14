#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
uchar code table[]={  0x3f,0x06,0x5b,0x4f,
  					  0x66,0x6d,0x7d,0x07,
					  0x7f,0x6f,0x77,0x7c,
					  0x39,0x5e,0x79,0x71
				   };
uchar  code helo[]={0x36,0x79,0x38,0x3f};
void init();
void delay(uint z);

sbit wela=P2^7;
sbit dula=P2^6;
uchar a0,a1,temp,bai,shi,ge,flag,flag1;
uint shu;
void display1(uchar aa,uchar bb,uchar cc) ;
void display2(uchar bai,uchar shi,uchar ge);
void main()
{
 init();//初始化并打开T0，T1
while(1){
if(flag1!=1)
{display1(bai,shi,ge);
display2(7,8,9);}
else
{
display1(18,19,20);
display2(16,17,18);
}

}
}
	 void init()
   {
   	flag=0;
	flag1=0;
   P1=temp;
   shu=432;
   temp=0xfe;
   a0=0;
   a1=0;
   TMOD=0x11;             //定时器T0与T1模式1
   TH0=(65536-50000)/256; //定时器初始化为约50毫秒每次中断
   TL0=(65536-50000)/256;
   TH1=(65536-50000)/256;
   TL1=(65536-50000)/256;
   EA=1;				  //总中断打开
   ET0=1;				  //定时器T0中断打卡
   TR0=1;                 //定时器T0打开
   ET1=1;
   TR1=1;
   
   }

   void time0() interrupt 1
   {
   	  TH0=(65536-50000)/256;
      TL0=(65536-50000)/256;
	  a0++;
	  if(flag!=1)
	  {
	  if(a0==10)
	  {
	  a0=1;
	  temp=_crol_(temp,1);
	  P1=temp;
	  }
	  }
	  else{
	  	if(a0%4==0)
		{
		P1=~P1;
		if(a0==60)
		{TR0=0;
		flag1=1;
		P1=0xff;}
		}
	  }

   }
   void timer1() interrupt 3
   {
   	TH1=(65536-50000)/256;
    TL1=(65536-50000)/256;
	a1++;
	if(a1==2)
	{
	a1=0;
	shu--;
	bai=shu/100;
	shi=shu%100/10;
	ge=shu%10;
	if(shu==398)
	{
	TR0=0;
    TH0=(65536-50000)/256;
    TL0=(65536-50000)/256;
	TR0=1;
	a0=0;
	P1=0xff;
	flag=1;
	TR1=0;
	}
	display1(bai,shi,ge);
	}


   }	 
	 
	 
	 
	 void delay(uint z)
{
uint x,y;
for(x=z;x>0;x--)
for(y=110;y>=0;y--)
;
}
  void display1(uchar aa,uchar bb,uchar cc)
{
P0=0xff;//消隐
wela=1;
P0=0xf7;
wela=0;
dula=1;
P0=table[aa];
dula=0;
delay(1);

P0=0xff;//
wela=1;
P0=0xef;
wela=0;
dula=1;
P0=table[bb];
dula=0;
delay(1);

P0=0xff;//
wela=1;
P0=0xdf;
wela=0;
dula=1;
P0=table[cc];
dula=0;
delay(1);
}

		void display2(uchar bai,uchar shi,uchar ge)
{
P0=0xff;//消隐
wela=1;
P0=0xfe;
wela=0;
dula=1;
P0=table[bai];
dula=0;
delay(1);

P0=0xff;//
wela=1;
P0=0xfd;
wela=0;
dula=1;
P0=table[shi];
dula=0;
delay(1);

P0=0xff;//
wela=1;
P0=0xfb;
wela=0;
dula=1;
P0=table[ge];
dula=0;
delay(1);
}
