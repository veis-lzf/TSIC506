#ifndef __TSIC506_H
#include "config.h"

sbit DQ = P3^3;

BOOL tsic506_init(void);    // 模块初始化函数
BOOL Check_Parity(uint value);
uint read_byte(void);
BOOL getTSIC_Temp (uint *temp_value16);

#endif /* __TSIC506_H */
