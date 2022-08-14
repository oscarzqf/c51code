#include<reg52.h>
#define uchar unsigned char;
#define uint unsigned int;
sbit sda=P2^0;
sbit scl=P2^1;
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
return(a);
}
void main()
{
init();
start();
write_byte(0xa0);//器件地址
response();      //应答
write_byte(3);	 //写入地址
response();
write_byte(0xfe);//写入数据
response();
stop();
start();
write_byte(0xa0);
response();
write_byte(3);
response();
wirte_byte(0xa1);
response();
P1=read_byte();
stop();
while(1);
}
