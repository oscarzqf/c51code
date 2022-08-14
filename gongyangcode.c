#include<reg52.h>
sbit wei1=P2^0;
void main()
{
wei1=1;
while(1)
{
P0=~0x3f;
}
}