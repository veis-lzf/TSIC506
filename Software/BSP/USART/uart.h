#ifndef __UART_H

#include "config.h"
#include <stdio.h>                  // 如果内存不够，可以关闭这个头文件的包含，使用自定义的 uart_printf 函数输出字符串

#define BaudRate		9600		// 模拟串口波特率
#define Timer0_Reload	(65536 - MAIN_Fosc / BaudRate / 3)
#define D_RxBitLenth	9		    // 9: 8 + 1 stop
#define D_TxBitLenth	9		    // 9: 1 stop bit
#define BUFF_SIZE 30                // 接受缓冲区大小

sbit RXB = P3^0;                    // define UART TX/RX port
sbit TXB = P3^1;

extern uchar data TBUF, RBUF;
extern uchar data TDAT, RDAT;
extern uchar data TCNT, RCNT;	    // 发送和接收检测 计数器(3倍速率检测)
extern uchar data TBIT, RBIT;	    // 发送和接收的数据计数器
extern uchar data t, r;
extern uchar data Rev_buf[BUFF_SIZE];
extern bit flag;

extern bit  TING, RING;	            // 正在发送或接收一个字节
extern bit  TEND, REND;	            // 发送或接收完成的标志位

#define	RxBitLenth	9	            // 8个数据位+1个停止位
#define	TxBitLenth	9	            // 8个数据位+1个停止位

void uart_init(void);               // 串口初始化函数
void uart_send(uchar dat);          // 发送一个字节函数
uchar uart_receive(void);           // 接收函数
void uart_printf(uchar * p_buf);    // 串口字符串打印

#endif /* __UART_H */
