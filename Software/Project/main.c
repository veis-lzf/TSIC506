#include <uart.h>
#include <delay.h>
#include <tsic506.h>


void main()
{
    uint temp_value;
    float Temp_float;
    uart_init();				// UART模块的初始变量
    tsic506_init();
    while(1)
    {
		if(getTSIC_Temp(&temp_value))
		{
			Temp_float = ((float)temp_value / 2047 * 70) - 10;
			printf("%.2f\n\r\n",Temp_float);
		}
    }
}



