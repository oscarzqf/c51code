#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table0[]="tempture:";
uchar code table1[]="    00.0";
uchar bai,shi,ge;//装三位温度
sbit  rs=P0^7;//LCD引脚定义
sbit rw=P0^6;
sbit en=P0^5;
sbit ds=P3^7;//温度传感器传输口
uchar i;
uint warnh=450;	//警告温度*10；
uint warnl=110;//


void delay(uint k)//ms
{
uint x,y;
for(x=k;x>0;x--)
for(y=110;y>0;y--);
}
void write_com(uchar comand)//对LCD写指令
{
rw=0;
rs=0;
P2=comand;
delay(10);
en=1;
delay(10);
en=0;
}
void write_date(uchar date_)//对LCD写入数据
{
rw=0;
rs=1;
P2=date_;
delay(10);
en=1;
delay(10);
en=0;
}
void init()
{
rw=0;
en=0;
write_com(0x38);//16*2显示
write_com(0x0c);//无光标显示
write_com(0x06);
write_com(0x01);//清屏
write_com(0x80);//指向一排第一位
for(i=0;i<9;i++)  //初始显示
{
write_date(table0[i]);
delay(5);
}
write_com(0x80+0x40);//第二行开始显示
for(i=0;i<8;i++)
{
write_date(table1[i]);
delay(5);
}

}
//DS18B20初始化
uchar begin()
{
ds=0;
i=70;
while(i--);
ds=1;
i=0;
while(ds)
{
delay(1);
i++;
if(i>5)//等待超过5毫秒
{
return 0;//初始化失败
}
else 
{
return 1;
}//初始化成功
}
}
//写时序
void write_type(uchar dat)
{
uint k,y;
for(y=0;y<8;y++)
{
ds=0;//每写一位拉低一微秒
k++;   
ds=dat&0x01;//写入低一位
k=6;//延时初值
while(i--);
ds=1;//释放总线
dat>>=1;//右移一位
}
}
//读时序
uchar read_type()
{
uchar date,bi;
uint x,y;
for(x=8;x>0;x--)
{
ds=0;
y++;
ds=1;
y++;
y++;
bi=ds;
date=(date>>1)|(bi<<7);
i=4;
while(i--);
}
return date;
}
//转换温度指令
void begintempturecom()
{
begin();//初始化
delay(1);//延时
write_type(0xcc);//一个直接忽略ROM地址
write_type(0x44);
//delay(100);
}
//读取温度命令
void readtempturecom()
{
begin();
delay(1);
write_type(0xcc);
write_type(0xbe);
}
//读取温度
int read_tempture()
{
int temp=0;
uchar tml,tmh;
begintempturecom();
readtempturecom();
tml=read_type();//读取低八位
tmh=read_type();//读取高八位
temp=tmh;
temp<<=8;
temp=temp|tml;
return temp;
}
void datapros(int temp)
{
float tp;
if(temp<0)//温度为负时
{
write_com(0x80+0x40+3);//第二行起始第3个位置
write_date('-');
temp=temp-1;//温度为实际温度补码-1，再取反得原码
temp=~temp;
tp=temp;
temp=tp*0.0625*10+0.5;//四舍五入，小数点后取一位故*10
}
else
{
tp=temp;
temp=tp*0.0625*10+0.5;
}
bai=(temp/100);
shi=(temp%100)/10;
ge=temp%10;
}
void disply_()
{
write_com(0x80+0x40+5);
write_date(bai);
write_com(0x80+0x40+6);
write_date(shi);
write_com(0x80+0x40+8);
write_date(ge);
delay(5);
} 

void main()
{
init();
while(1)
{
datapros(read_tempture);
disply_();
}
}