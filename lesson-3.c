   #include<reg52.h>
   sbit di=P1^0;
   unsigned int a;
   void main()
   {
   
   while(1)
   
   {di=0;
   a=51000;
   while(a--);
   di=1;
   a=51000;
   while(a--);
   }
   
   
   
   }