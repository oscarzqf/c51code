								  /******************************************************************
**                        头文件
******************************************************************/
#include<AT89X52.H>	  

/******************************************************************
**                       电机驱动定义
******************************************************************/
#define Left_moto_Stop    {P1_1=0,P1_2=0;}    //左电机停转 
#define Left_moto_go      {P1_1=1,P1_2=0;}    //左电机正转
#define Left_moto_back    {P1_1=0,P1_2=1;} 	  //左电机反转
#define Right_moto_Stop   {P1_4=0,P1_5=0;}	  //右电机停转                     
#define Right_moto_go     {P1_4=1,P1_5=0;}	  //右电机正转
#define Right_moto_back   {P1_4=0,P1_5=1;}	  //右电机反转
#define Daka_go         {P1_6=0,P1_7=1;}	  //向下打卡
#define Daka_back       {P1_6=1,P1_7=0;}	  //向上打卡
#define Daka_stop       {P1_6=0,P1_7=0;}	  //停止打卡
#define Left_moto_pwm	    P1_0	  //PWM信号端
#define Right_moto_pwm	  P1_3	  //PWM信号端

#define Left_1_led        P3_6	  //左传感器       
#define Right_1_led       P3_7	  //右传感器 

sbit BUZZ = P2^3;                 //蜂鸣器引脚

/******************************************************************
**                       PWM调速相关变量
******************************************************************/
unsigned char pwm_val_left  =0;              //变量定义
unsigned char push_val_left =0;              //左电机占空比N/20
unsigned char pwm_val_right =0;
unsigned char push_val_right=0;              //右电机占空比N/20
bit Right_moto_stop=1;
bit Left_moto_stop =1;
unsigned  int  time=0;

/******************************************************************
**                       延时函数
******************************************************************/	
void delay(unsigned int k)
{    
     unsigned int x,y;
	 for(x=0;x<k;x++) 
	   for(y=0;y<3000;y++);
}

/******************************************************************
**                       小车前进
******************************************************************/
void  front_run(void)
{
	 push_val_left=10;

	 push_val_right=12;
	 Left_moto_go;   
	 Right_moto_go;  
}

/******************************************************************
**                       小车后退
******************************************************************/
void  back_run(void)
{
	 push_val_left=10;
	 push_val_right=12;
	 Left_moto_back;   
	 Right_moto_back;  
}


/******************************************************************
**                       小车左转
******************************************************************/
void  left_run(void)
{
	 push_val_left=0;
	 push_val_right=15;
	 Right_moto_go;   
	 Left_moto_back;  
}

/******************************************************************
**                       小车右转
******************************************************************/
void  right_run(void)
{
	 push_val_left=12;
	 push_val_right=0;
	 Left_moto_go;   
	 Right_moto_back;  
}

/******************************************************************
**                       小车停走
******************************************************************/
void  stop(void)
{
	 Left_moto_Stop;
	 Right_moto_Stop;    
}

/******************************************************************
**                       左电机调速
******************************************************************/
void pwm_out_left_moto(void)
{  
	if(Left_moto_stop)
	{
	    if(pwm_val_left<=push_val_left)
			{
				Left_moto_pwm=1; 
	
			}
		else 
		    {
		        Left_moto_pwm=0;
	
			}
		if(pwm_val_left>=20)
		    pwm_val_left=0;
	}
	else    
	{
		Left_moto_pwm=0;
	}
}

/******************************************************************
**                       右电机调速
******************************************************************/
void pwm_out_right_moto(void)
{ 
	if(Right_moto_stop)
    { 
    	if(pwm_val_right<=push_val_right)
	    {
	    	Right_moto_pwm=1; 
		}
	else 
	    {
			Right_moto_pwm=0;
		}
	if(pwm_val_right>=20)
	       pwm_val_right=0;
   }
   else    
   {
       Right_moto_pwm=0;

   }
}

/******************************************************************
**                       定时器0初始化
******************************************************************/
void timer0_Init(void)
{
	TMOD=0X01;
	TH0= 0XFc;		  //1ms定时
	TL0= 0X18;
	TR0= 1;
	ET0= 1;
	EA = 1;			   //开总中断	
}
           
/******************************************************************
**                   定时器0中断服务子程序
******************************************************************/
void timer0()interrupt 1   using 2
{
   TH0=0XFc;	  
	 TL0=0X18;
	 time++;
	 pwm_val_left++;
	 pwm_val_right++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }	

/******************************************************************
**                       主函数
******************************************************************/
void main(void)
{
	unsigned char i;
	stop();	                //小车停转	    

  timer0_Init();     
	while(1)
	{
		if(Left_1_led==0&&Right_1_led==0)      //无黑线
		   front_run();                        //前进
		else
	    {			  
			if(Left_1_led==1&&Right_1_led==0)    //左边有黑线
			{
				left_run();		                     //左转
			}  
			if(Right_1_led==1&&Left_1_led==0)    //右边有黑线
		    {	  
				right_run();		                   //右转
		    }
			if(Right_1_led==1&&Left_1_led==1)    //前方有黑线
		    {	  
				stop();		                         //停车
                Daka_go;
                delay (10);
                Daka_back;
                delay (10);
                Daka_stop;
                front_run();
                delay (10);
		    }
		}	 
	}
}
/******************************************************************
**                        结束
******************************************************************/
