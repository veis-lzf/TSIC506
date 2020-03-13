#ifndef __DELAY_H
#define __DELAY_H
#include "config.h"

#define MS_STEP (Main_Fosc_KHZ / 14)

void delay_ms(unsigned int ms);
void delay_5us(uchar step); /* 11.0592M¾§Õñ£¬1Tµ¥Æ¬»ú */

#endif /* __DELAY_H */
