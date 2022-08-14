//整屏左移
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]={"I love you!"};
uchar code table1[]={"I love study!"};
void delay(uint);
void init();
uchar i;
void write_com(uchar com_);
void write_date(uchar date);
sbit lcden=P3^4;
sbit lcdrs=P3^5;
sbit dula=P2^6;
sbit  wela=P2^7;
void main()
{
init();
for(i=0;i<11;i++)
{
write_date(table[i]);
delay(5);
}
write_com(0x80+0x53);//第二行屏外第三位开始写
for(i=0;i<13;i++)
{
write_date(table1[i]);
delay(5);
}
for(i=0;i<16;i++)
{
write_com(0x18);
delay(200);
}
while(1);

}
void delay(uint z)
{
 uint x,y;
 for(x=z;x>0;x--)
 for(y=110;y>0;y++); 
}
void init()
{
dula=0;
wela=0;
lcden=0; //使能信号起始为低
write_com(0x38);//模式
write_com(0x04);	  //开显示，光标
write_com(0x06);//顺写
write_com(0x01);//数据指针清零，清屏
write_com(0x80+0x10);//指针指向第一行屏外
}
void write_com(uchar com_) //送指令函数
{
lcdrs=0;//上电时为1,0开启指令
P0=com_;
delay(5);
lcden=1; //高脉冲读指令
delay(5);
lcden=0;
}
void write_date(uchar date)//写数据函数
{
lcdrs=1;
P0=date;
delay(5);
lcden=1; //高脉冲读数据
delay(5);
lcden=0;
}