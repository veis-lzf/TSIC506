#ifndef		__CONFIG_H
#define		__CONFIG_H

/*********************************************************/

//#define MAIN_Fosc		 5529600L	//������ʱ��	 110 ~ 4800
#define MAIN_Fosc		11059200L	//������ʱ��	 110 ~ 9600
//#define MAIN_Fosc		12000000L	//������ʱ��	 110 ~ 9600
//#define MAIN_Fosc		22118400L	//������ʱ��	 220 ~ 19200
//#define MAIN_Fosc		24000000L	//������ʱ��	 220 ~ 19200
//#define MAIN_Fosc		33177600L	//������ʱ��	 220 ~ 38400


/*********************************************************/
// �������Ͷ���
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
