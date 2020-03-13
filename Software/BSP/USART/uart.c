#include <uart.h>

uchar data TBUF = 0, RBUF = 0;
uchar data TDAT = 0, RDAT = 0;
uchar data TCNT = 0, RCNT = 0;	// 发送和接收检测 计数器(3倍速率检测)
uchar data TBIT = 0, RBIT = 0;	// 发送和接收的数据计数器
uchar data t = 0, r = 0;
uchar data Rev_buf[BUFF_SIZE] = "0";
uchar data S_BUF;   // 用于接收串口一个字节的返回值
bit flag = 0;       // 用于标志是否有数据到来

bit  TING, RING;	// 正在发送或接收一个字节
bit  TEND, REND;	// 接收或发送完成的标志位


// UART模块的初始变量	initial UART module variable
void uart_init()
{
	InternalRAM_enable();
	Timer0_1T();
	Timer0_AsTimer();
	Timer0_16bitAutoReload();       // 设置定时器0位16位自动重装模式
	Timer0_Load(Timer0_Reload);
	Timer0_InterruptEnable();
	Timer0_Run();
	EA = 1;
	TING = 0;
	RING = 0;
	REND = 0;
    TEND = 1;
	TCNT = 0;
	RCNT = 0;
}

void uart_send(uchar dat)     // 串口发送一个字节函数
{
   if(TEND)
    {
        TEND = 0;
        TBUF = dat;
        TING = 1;
        while(!TEND);
    }
}

uchar uart_receive(void)     // 接收函数
{
	if (REND)				 // 如果接收完,把接收到的值存入接收S_BUF
	{
		REND = 0;
        if(r < BUFF_SIZE) Rev_buf[r++] = RBUF;
        else r = 0;
        S_BUF = RBUF;
        flag = 1;
	}
    return S_BUF;
}


// 重定向printf,需要重写putchar函数；当包含 stdio.h 头文件时，可以直接和标准C一样使用printf进行格式化输出。
char putchar(char c)
{
    uart_send(c);
    return c;
}



// 发送一串字符串
void uart_printf(uchar * p_buf)
{
    while(*p_buf != '\0')
    {
        uart_send(*p_buf);
        p_buf++;
    }
}



// 定时器0中断程序for UART 以波特率3倍的速度采样判断 开始位		Timer interrupt routine for UART
void tm0(void) interrupt 1 using 1
{

	if (RING)
	{
		if (--RCNT == 0)				  // 接收数据以定时器的1/3来接收
		{
			RCNT = 3;                     // 重置接收计数器  接收数据以定时器的1/3来接收	reset send baudrate counter
			if (--RBIT == 0)			  // 接收完一帧数据
			{
				RBUF = RDAT;              // 存储数据到缓冲区	save the data to RBUF
				RING = 0;                 // 停止接收			stop receive
				REND = 1;                 // 接收完成标志设置	set receive completed flag
			}
			else
			{
				RDAT >>= 1;			      // 把接收的单b数据 暂存到 RDAT(接收缓冲)
				if (RXB) RDAT |= 0x80;    // shift RX data to RX buffer
			}
		}
	}

	else if (!RXB)		                  // 判断是不是开始位 RXB=0;
	{
		RING = 1;                         // 如果是则设置开始接收标志位 	set start receive flag
		RCNT = 4;                         // 初始化接收波特率计数器       	initial receive baudrate counter
		RBIT = RxBitLenth;                // 初始化接收的数据位数(8个数据位+1个停止位)    initial receive bit number (8 data bits + 1 stop bit)
	}

    if (--TCNT == 0)			          // 发送数据以定时器的1/3来发送
    {
        TCNT = 3;				          // 重置发送计数器   reset send baudrate counter
        if(TING)
        {
            if (TBIT == 0)			      // 发送计数器为0 表明单字节发送还没开始
            {
                TXB = 0;			      // 发送开始位     					send start bit
                TDAT = TBUF;		      // 把缓冲的数据放到发送的buff		load data from TBUF to TDAT
                TBIT = TxBitLenth;	      // 发送数据位数 (8数据位+1停止位)	initial send bit number (8 data bits + 1 stop bit)
            }
            else					      // 发送计数器为非0 正在发送数据
            {
                TDAT >>= 1;		          // 把最低位送到 CY(益处标志位) shift data to CY
                if (--TBIT == 0)	      // 发送计数器减为0 表明单字节发送结束
                {
                    TXB = 1;		      // 送停止位数据
                    TING = 0;		      // 发送停止位    			stop send
                    TEND = 1;             // 置位发送完成标志符      set send completed flag
                }
                else
                {
                    TXB = CY;		      // 发送单b数据				write CY to TX port
                }
            }
        }
    }
}



