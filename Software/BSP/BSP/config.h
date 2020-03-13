#ifndef		__CONFIG_H
#define		__CONFIG_H

/*********************************************************/

//#define MAIN_Fosc		 5529600L	//定义主时钟	 110 ~ 4800
#define MAIN_Fosc		11059200L	//定义主时钟	 110 ~ 9600
//#define MAIN_Fosc		12000000L	//定义主时钟	 110 ~ 9600
//#define MAIN_Fosc		22118400L	//定义主时钟	 220 ~ 19200
//#define MAIN_Fosc		24000000L	//定义主时钟	 220 ~ 19200
//#define MAIN_Fosc		33177600L	//定义主时钟	 220 ~ 38400


/*********************************************************/
// 数据类型定义
typedef bit BOOL;
typedef unsigned char uchar;
typedef unsigned int uint;


#define TRUE  1
#define FALSE 0
/*********************************************************/


#include	"STC15Fxxxx.H"

/**************************************************************************/

#define Main_Fosc_KHZ	(MAIN_Fosc / 1000)

/***********************************************************/

#endif
