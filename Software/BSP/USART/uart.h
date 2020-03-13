#ifndef __UART_H

#include "config.h"
#include <stdio.h>                  // ����ڴ治�������Թر����ͷ�ļ��İ�����ʹ���Զ���� uart_printf ��������ַ���

#define BaudRate		9600		// ģ�⴮�ڲ�����
#define Timer0_Reload	(65536 - MAIN_Fosc / BaudRate / 3)
#define D_RxBitLenth	9		    // 9: 8 + 1 stop
#define D_TxBitLenth	9		    // 9: 1 stop bit
#define BUFF_SIZE 30                // ���ܻ�������С

sbit RXB = P3^0;                    // define UART TX/RX port
sbit TXB = P3^1;

extern uchar data TBUF, RBUF;
extern uchar data TDAT, RDAT;
extern uchar data TCNT, RCNT;	    // ���ͺͽ��ռ�� ������(3�����ʼ��)
extern uchar data TBIT, RBIT;	    // ���ͺͽ��յ����ݼ�����
extern uchar data t, r;
extern uchar data Rev_buf[BUFF_SIZE];
extern bit flag;

extern bit  TING, RING;	            // ���ڷ��ͻ����һ���ֽ�
extern bit  TEND, REND;	            // ���ͻ������ɵı�־λ

#define	RxBitLenth	9	            // 8������λ+1��ֹͣλ
#define	TxBitLenth	9	            // 8������λ+1��ֹͣλ

void uart_init(void);               // ���ڳ�ʼ������
void uart_send(uchar dat);          // ����һ���ֽں���
uchar uart_receive(void);           // ���պ���
void uart_printf(uchar * p_buf);    // �����ַ�����ӡ

#endif /* __UART_H */
