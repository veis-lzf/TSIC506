#include <uart.h>

uchar data TBUF = 0, RBUF = 0;
uchar data TDAT = 0, RDAT = 0;
uchar data TCNT = 0, RCNT = 0;	// ���ͺͽ��ռ�� ������(3�����ʼ��)
uchar data TBIT = 0, RBIT = 0;	// ���ͺͽ��յ����ݼ�����
uchar data t = 0, r = 0;
uchar data Rev_buf[BUFF_SIZE] = "0";
uchar data S_BUF;   // ���ڽ��մ���һ���ֽڵķ���ֵ
bit flag = 0;       // ���ڱ�־�Ƿ������ݵ���

bit  TING, RING;	// ���ڷ��ͻ����һ���ֽ�
bit  TEND, REND;	// ���ջ�����ɵı�־λ


// UARTģ��ĳ�ʼ����	initial UART module variable
void uart_init()
{
	InternalRAM_enable();
	Timer0_1T();
	Timer0_AsTimer();
	Timer0_16bitAutoReload();       // ���ö�ʱ��0λ16λ�Զ���װģʽ
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

void uart_send(uchar dat)     // ���ڷ���һ���ֽں���
{
   if(TEND)
    {
        TEND = 0;
        TBUF = dat;
        TING = 1;
        while(!TEND);
    }
}

uchar uart_receive(void)     // ���պ���
{
	if (REND)				 // ���������,�ѽ��յ���ֵ�������S_BUF
	{
		REND = 0;
        if(r < BUFF_SIZE) Rev_buf[r++] = RBUF;
        else r = 0;
        S_BUF = RBUF;
        flag = 1;
	}
    return S_BUF;
}


// �ض���printf,��Ҫ��дputchar������������ stdio.h ͷ�ļ�ʱ������ֱ�Ӻͱ�׼Cһ��ʹ��printf���и�ʽ�������
char putchar(char c)
{
    uart_send(c);
    return c;
}



// ����һ���ַ���
void uart_printf(uchar * p_buf)
{
    while(*p_buf != '\0')
    {
        uart_send(*p_buf);
        p_buf++;
    }
}



// ��ʱ��0�жϳ���for UART �Բ�����3�����ٶȲ����ж� ��ʼλ		Timer interrupt routine for UART
void tm0(void) interrupt 1 using 1
{

	if (RING)
	{
		if (--RCNT == 0)				  // ���������Զ�ʱ����1/3������
		{
			RCNT = 3;                     // ���ý��ռ�����  ���������Զ�ʱ����1/3������	reset send baudrate counter
			if (--RBIT == 0)			  // ������һ֡����
			{
				RBUF = RDAT;              // �洢���ݵ�������	save the data to RBUF
				RING = 0;                 // ֹͣ����			stop receive
				REND = 1;                 // ������ɱ�־����	set receive completed flag
			}
			else
			{
				RDAT >>= 1;			      // �ѽ��յĵ�b���� �ݴ浽 RDAT(���ջ���)
				if (RXB) RDAT |= 0x80;    // shift RX data to RX buffer
			}
		}
	}

	else if (!RXB)		                  // �ж��ǲ��ǿ�ʼλ RXB=0;
	{
		RING = 1;                         // ����������ÿ�ʼ���ձ�־λ 	set start receive flag
		RCNT = 4;                         // ��ʼ�����ղ����ʼ�����       	initial receive baudrate counter
		RBIT = RxBitLenth;                // ��ʼ�����յ�����λ��(8������λ+1��ֹͣλ)    initial receive bit number (8 data bits + 1 stop bit)
	}

    if (--TCNT == 0)			          // ���������Զ�ʱ����1/3������
    {
        TCNT = 3;				          // ���÷��ͼ�����   reset send baudrate counter
        if(TING)
        {
            if (TBIT == 0)			      // ���ͼ�����Ϊ0 �������ֽڷ��ͻ�û��ʼ
            {
                TXB = 0;			      // ���Ϳ�ʼλ     					send start bit
                TDAT = TBUF;		      // �ѻ�������ݷŵ����͵�buff		load data from TBUF to TDAT
                TBIT = TxBitLenth;	      // ��������λ�� (8����λ+1ֹͣλ)	initial send bit number (8 data bits + 1 stop bit)
            }
            else					      // ���ͼ�����Ϊ��0 ���ڷ�������
            {
                TDAT >>= 1;		          // �����λ�͵� CY(�洦��־λ) shift data to CY
                if (--TBIT == 0)	      // ���ͼ�������Ϊ0 �������ֽڷ��ͽ���
                {
                    TXB = 1;		      // ��ֹͣλ����
                    TING = 0;		      // ����ֹͣλ    			stop send
                    TEND = 1;             // ��λ������ɱ�־��      set send completed flag
                }
                else
                {
                    TXB = CY;		      // ���͵�b����				write CY to TX port
                }
            }
        }
    }
}



