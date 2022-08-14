#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table0[]="tempture:";
uchar code table1[]="    00.0";
uchar bai,shi,ge;//װ��λ�¶�
sbit  rs=P0^7;//LCD���Ŷ���
sbit rw=P0^6;
sbit en=P0^5;
sbit ds=P3^7;//�¶ȴ����������
uchar i;
uint warnh=450;	//�����¶�*10��
uint warnl=110;//


void delay(uint k)//ms
{
uint x,y;
for(x=k;x>0;x--)
for(y=110;y>0;y--);
}
void write_com(uchar comand)//��LCDдָ��
{
rw=0;
rs=0;
P2=comand;
delay(10);
en=1;
delay(10);
en=0;
}
void write_date(uchar date_)//��LCDд������
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
write_com(0x38);//16*2��ʾ
write_com(0x0c);//�޹����ʾ
write_com(0x06);
write_com(0x01);//����
write_com(0x80);//ָ��һ�ŵ�һλ
for(i=0;i<9;i++)  //��ʼ��ʾ
{
write_date(table0[i]);
delay(5);
}
write_com(0x80+0x40);//�ڶ��п�ʼ��ʾ
for(i=0;i<8;i++)
{
write_date(table1[i]);
delay(5);
}

}
//DS18B20��ʼ��
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
if(i>5)//�ȴ�����5����
{
return 0;//��ʼ��ʧ��
}
else 
{
return 1;
}//��ʼ���ɹ�
}
}
//дʱ��
void write_type(uchar dat)
{
uint k,y;
for(y=0;y<8;y++)
{
ds=0;//ÿдһλ����һ΢��
k++;   
ds=dat&0x01;//д���һλ
k=6;//��ʱ��ֵ
while(i--);
ds=1;//�ͷ�����
dat>>=1;//����һλ
}
}
//��ʱ��
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
//ת���¶�ָ��
void begintempturecom()
{
begin();//��ʼ��
delay(1);//��ʱ
write_type(0xcc);//һ��ֱ�Ӻ���ROM��ַ
write_type(0x44);
//delay(100);
}
//��ȡ�¶�����
void readtempturecom()
{
begin();
delay(1);
write_type(0xcc);
write_type(0xbe);
}
//��ȡ�¶�
int read_tempture()
{
int temp=0;
uchar tml,tmh;
begintempturecom();
readtempturecom();
tml=read_type();//��ȡ�Ͱ�λ
tmh=read_type();//��ȡ�߰�λ
temp=tmh;
temp<<=8;
temp=temp|tml;
return temp;
}
void datapros(int temp)
{
float tp;
if(temp<0)//�¶�Ϊ��ʱ
{
write_com(0x80+0x40+3);//�ڶ�����ʼ��3��λ��
write_date('-');
temp=temp-1;//�¶�Ϊʵ���¶Ȳ���-1����ȡ����ԭ��
temp=~temp;
tp=temp;
temp=tp*0.0625*10+0.5;//�������룬С�����ȡһλ��*10
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