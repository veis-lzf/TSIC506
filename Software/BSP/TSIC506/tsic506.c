#include <tsic506.h>
#include <delay.h>


// 初始化函数
BOOL tsic506_init()
{
    DQ = 1;
    while(!DQ);
    return TRUE;
}

// 读取一次总线上的数据
uint read_byte(void)
{
    uchar i;
    uint temp_value = 0;

    // 等待开始信号
    while(DQ == 1);  // 等待总线被从机拉低
    while(DQ == 0);  // 等待就绪
    
    // 在下降沿读取8位数据+1位奇偶校验位
    for (i = 0; i < 9; i++)
    {
        while(DQ == 1);   // 等待下降沿产生，以读取总线
        delay_5us(12);
        if (DQ == 1)
        {
            temp_value |= 1 << (8-i); // 取一个位，从高位开始存
        }
        else
        {
            while(DQ == 0);  // 等待总线再次拉高，便于下次产生下降沿
        }
    }
    
    return temp_value;
}

// 检查校验位是否为1
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

// 获取温度
BOOL getTSIC_Temp (uint *temp_value16)
{
    uint temp_value1 = 0;
    uint temp_value2 = 0;
    uint Temperature;
    
    temp_value1 = read_byte();
    temp_value2 = read_byte();
    
    // 校验温度数据高字节
    while(!Check_Parity(temp_value1))
    {
        return FALSE;
    }
    // 校验温度数据低字节
    while(!Check_Parity(temp_value2))
    {
        return FALSE;
    }
 
    // 删除校验位
    temp_value1 >>= 1;
    temp_value2 >>= 1;
    
    Temperature = (temp_value1 << 8) | temp_value2;
    *temp_value16 = Temperature;
    
    return TRUE;
}