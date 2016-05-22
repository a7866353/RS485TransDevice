/*
 * LCDDriver.c
 *
 *  Created on: 2016年5月22日
 *      Author: linwei
 */

#include "LCDDriver.h"
#include <pic16F1947.h>
// TODO
#define D_LCD_BUS_DATA 	PORTD  // PORT_D
#define D_LCD_BUS_RS	LATEbits.LATE7  // PORT_E.7
#define D_LCD_BUS_RW	LATEbits.LATE6  // PORT_E.6
#define D_LCD_BUS_E		LATEbits.LATE5  // PORT_E.5


void Delay(uint16 time);              //延时


void Delay(uint16 time)
{
    while(time--);
}

void Init12864()
{
    CheckBusy();
    Write12864_Com(0x30);
    CheckBusy();
    Write12864_Com(0x0c);
    CheckBusy();
    Write12864_Com(0x01);
}

void Write12864_Com(uint8 com)
{
	D_LCD_BUS_RS=0;
	D_LCD_BUS_RW=0;
    D_LCD_BUS_DATA = com;
    D_LCD_BUS_E=0;
    D_LCD_BUS_E=1;
    D_LCD_BUS_E=0;
}

void Write12864_Dat(uint8 dat)
{
	D_LCD_BUS_RS=1;
	D_LCD_BUS_RW=0;
	D_LCD_BUS_DATA=dat;
    D_LCD_BUS_E=0;
    D_LCD_BUS_E=1;
    D_LCD_BUS_E=0;
}

void CheckBusy(void)            //检查忙
{
    uint8 temp;
    D_LCD_BUS_RS=0;
    D_LCD_BUS_RW=1;
    D_LCD_BUS_E=0;
    while(1)
    {
       D_LCD_BUS_DATA=0xFF;      //数据线为输入
       D_LCD_BUS_E=1;
       temp=D_LCD_BUS_DATA;
       D_LCD_BUS_E=0;
       if ((temp&0x80)==0)
           break;
    }
}
