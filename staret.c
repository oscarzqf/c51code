#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit sda=P2^0;
sbit scl=P2^1;
void delay1(uint z)
{
uint x,y;
for(x=z;x>0;x--)
for(y=110;y>0;y--)
;
}
void delay()
{
 ;;	//不用太长
}
void start()
{
sda=1;
delay();
scl=1;
delay();
sda=0;
delay();
}
void stop()
{
sda=0;
delay();
scl=1;
delay();
sda=1;
delay();
}
void response()//应答信号
{
uchar i=0;
scl=1;
while((sda==1)&&(i<255))//应答或超时应答
{i++;}
scl=0;
delay();
}
void init()
{
sda=1;
scl=1;
}
void write_byte(uchar date)
{
uchar i,temp;
scl=0;
temp=date;
delay();
for(i=0;i<8;i++)
{
temp=temp<<1;
sda=CY;
delay();
scl=1;
delay();
scl=0;
}
sda=1;
delay();
}  
uchar read_byte()
{
uchar i,j,k;
scl=0;
delay();
sda=1;
delay();
for(i=0;i<8;i++)
{
scl=1;
delay();
j=sda;
k=(k<<1)|j;
scl=0;
delay();
}
return(k);
}
	  void write_add(uchar adress,uchar date)
{
start();
write_byte(0xa0);//器件地址
response();      //应答
write_byte(adress);	 //写入地址
response();
write_byte(date);//写入数据
response();
stop();
}
uchar read_add(uchar address)
{
uchar date;
start();
write_byte(0xa0);
response();
write_byte(address);
response();
write_byte(0xa1);
response();
date=read_byte();
stop();
return date;
}
void main()
{
init();
write_add(23,125);
delay1(100);//读写间应该隔时间
P1=read_add(23);
while(1);
}
