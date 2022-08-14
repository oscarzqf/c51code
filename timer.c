/*一个可以调试间闹钟*/

#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table0[]={0xc0,0xf9,0xa4,
                    0xb0,0x99,0x92,0x82,
                    0xf8,0x80,0x90};//0~9
sbit BEEP=P3^6;
sbit rw=P0^6;
sbit rs=P0^7;
sbit lcden=P0^5;//液晶选项
sbit key1=P3^5;
sbit key2=P3^4;
sbit key3=P3^3;
sbit key4=P3^2;//
uchar count,s1number;
char miao,shi,fen;
void delay500() //延时500微秒
{
uchar i;
for(i=230;i>0;i--);
}
uchar code table1[]="    I love study";//16
uchar code table2[]="    00:00:00";//12
void delay_(uint z)	 //延时
{
uint x,y;
for(x=z;x>0;x--)
for(y=110;y>0;y--)
;
}
void write_com(uchar com)//液晶写指令
{
rw=0;
rs=0;
P2=com;
delay_(10);
lcden=1;
delay_(10);
lcden=0;
}
void write_date(uchar date)//液晶写数据
{
rw=0;
rs=1;
P2=date;
delay_(10);
lcden=1;
delay_(10);
lcden=0;
}
void init()
{
uchar num;
lcden=0;
rw=0;
write_com(0x38);
write_com(0x0c);
write_com(0x06);
write_com(0x01);//清屏
write_com(0x80);
for(num=0;num<16;num++)
{
write_date(table1[num]);
delay_(5);
}
write_com(0x80+0x40);
for(num=0;num<12;num++)
{
write_date(table2[num]);
delay_(5);
}
TMOD=0X01;
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;
EA=1;
ET0=1;
TR0=1;
}
void write_sfm(uchar add,uchar date)
{
uchar shi,ge;
shi=date/10;
ge=date%10;
write_com(0x80+0X40+add);
write_date(0x30+shi);
write_date(0x30+ge);
}
void keyscan_()
{
if(key1==0)
{
delay_(5);
if(key1==0)
{
s1number++;
while(!key1);
if(s1number==1)
{
TR0=0;
write_com(0x80+0x40+11);//地址在秒个位
write_com(0x0f); //光标闪烁
}
if(s1number==2)
{
write_com(0x80+0x40+8);//地址在分钟
}
if(s1number==3)
{
write_com(0x80+0x40+5);//小时闪烁
}
if(s1number==4)
{
s1number=0;//清零进行下次
write_com(0x0c);//光标停止闪烁
TR0=1;
}
}
}
if(s1number!=0)
{
if(key2==0)
{
delay_(5);
if(key2==0)
{
while(!key2);
if(s1number==1)
{
miao++;
if(miao==60)
miao=0;
write_sfm(10,miao);
write_com(0x80+0x40+11);
}
if(s1number==2)
{
fen++;
if(fen==60)
fen=0;
write_sfm(7,fen);
write_com(0x80+0x40+7);
}
if(s1number==3)
{
shi++;
if(shi==24)
shi=0;
write_sfm(4,shi);
write_com(0x80+0x40+4);
}
}
}
if(key3==0)
{
delay_(5);
if(key3==0)
{
while(!key3);
if(s1number==1)
{
miao--;
if(miao==-1)
miao=59;
write_sfm(10,miao);
write_com(0x80+0x40+10);
}
if(s1number==2)
{
fen--;
if(fen==-1)
fen=59;
write_sfm(7,fen);
write_com(0x80+0x40+7);
}
if(s1number==3)
{
shi--;
if(shi==-1)
shi=23;
write_sfm(4,shi);
write_com(0x80+0x40+4);
}
}
}
}
}

void main()
{
init();
while(1){
keyscan_();
if(shi==6&&fen==40&&miao==59)
{
uchar j;
  while(1)
  {
    for(j=200;j>0;j--)
	{
	  BEEP=~BEEP;       //输出频率1KHz
	  delay500();       //延时500us
	}

	for(j=200;j>0;j--)
	{
	  BEEP=~BEEP;       //输出频率500Hz
	  delay500();       //延时1ms
	  delay500();
	}
  }

}
}

}
void timer0() interrupt 1
{
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;
count++;
	if(count==18) 
{
count=0;
miao++;
if(miao==60)
{
miao=0;
fen++;
if(fen==60)
{
fen=0;
shi++;
if(shi==24)
{
shi=0;
}
write_sfm(4,shi);
}
write_sfm(7,fen);
}
write_sfm(10,miao);
}
}


