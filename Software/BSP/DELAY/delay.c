#include <delay.h>

/*
 * @brief:����Ӧ������ʱ����,���۶�ʱ��Χ1~65535
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


/* 1T��Ƭ������Ƶ11.0592M����ʱ��������ʱ10us */
void delay_5us(uchar step)   // ��� -0.053530092593us
{
    unsigned char a;
    while(step-- > 0)
    {
        for(a=1;a>0;a--);
    }
}
