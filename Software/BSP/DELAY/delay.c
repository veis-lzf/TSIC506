#include <delay.h>

/*
 * @brief:自适应毫秒延时函数,理论定时范围1~65535
 *
 *
 */
void delay_ms(unsigned int ms)
{
     unsigned int i;
	 do{
	      i = MS_STEP;
		  while(--i);   // 14T per loop
     }while(--ms);
}


/* 1T单片机，主频11.0592M，延时函数，延时10us */
void delay_5us(uchar step)   // 误差 -0.053530092593us
{
    unsigned char a;
    while(step-- > 0)
    {
        for(a=1;a>0;a--);
    }
}
