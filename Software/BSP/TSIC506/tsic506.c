#include <tsic506.h>
#include <delay.h>


// ��ʼ������
BOOL tsic506_init()
{
    DQ = 1;
    while(!DQ);
    return TRUE;
}

// ��ȡһ�������ϵ�����
uint read_byte(void)
{
    uchar i;
    uint temp_value = 0;

    // �ȴ���ʼ�ź�
    while(DQ == 1);  // �ȴ����߱��ӻ�����
    while(DQ == 0);  // �ȴ�����
    
    // ���½��ض�ȡ8λ����+1λ��żУ��λ
    for (i = 0; i < 9; i++)
    {
        while(DQ == 1);   // �ȴ��½��ز������Զ�ȡ����
        delay_5us(12);
        if (DQ == 1)
        {
            temp_value |= 1 << (8-i); // ȡһ��λ���Ӹ�λ��ʼ��
        }
        else
        {
            while(DQ == 0);  // �ȴ������ٴ����ߣ������´β����½���
        }
    }
    
    return temp_value;
}

// ���У��λ�Ƿ�Ϊ1
BOOL Check_Parity(uint value)
{
    uchar i;
    uchar parity = 0;
    
    for (i = 0; i < 9; i++)
    {
        if (value & (1 << i))
        {
            parity++;
        }
    }
    if (parity % 2)
    {
        return FALSE;
    }
    
    return TRUE;  
}

// ��ȡ�¶�
BOOL getTSIC_Temp (uint *temp_value16)
{
    uint temp_value1 = 0;
    uint temp_value2 = 0;
    uint Temperature;
    
    temp_value1 = read_byte();
    temp_value2 = read_byte();
    
    // У���¶����ݸ��ֽ�
    while(!Check_Parity(temp_value1))
    {
        return FALSE;
    }
    // У���¶����ݵ��ֽ�
    while(!Check_Parity(temp_value2))
    {
        return FALSE;
    }
 
    // ɾ��У��λ
    temp_value1 >>= 1;
    temp_value2 >>= 1;
    
    Temperature = (temp_value1 << 8) | temp_value2;
    *temp_value16 = Temperature;
    
    return TRUE;
}