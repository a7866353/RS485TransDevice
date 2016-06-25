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
#define D_LCD_BUS_DATA_DIR 	TRISD  // PORT_D

#define D_LCD_BUS_RS        LATEbits.LATE7  // PORT_E.7
#define D_LCD_BUS_RS_DIR    TRISEbits.TRISE7
#define D_LCD_BUS_RW        LATEbits.LATE6  // PORT_E.6
#define D_LCD_BUS_RW_DIR    TRISEbits.TRISE6
#define D_LCD_BUS_E         LATEbits.LATE5  // PORT_E.5
#define D_LCD_BUS_E_DIR     TRISEbits.TRISE5


#define D_LCD_BUS_LIGHT     LATEbits.LATE4
#define D_LCD_BUS_LIGHT_DIR TRISEbits.TRISE4

void LCDInit()
{
    D_LCD_BUS_DATA_DIR = 0;
    D_LCD_BUS_RS_DIR = 0;
    D_LCD_BUS_RW_DIR = 0;
    D_LCD_BUS_E_DIR = 0;
  
    D_LCD_BUS_LIGHT_DIR = 0;
    D_LCD_BUS_LIGHT = 1;
    
    CheckBusy();
    Write12864_Com(0x30);
    CheckBusy();
    Write12864_Com(0x0c);
    CheckBusy();
    Write12864_Com(0x01);
}

void Write12864_Com(uint8 com)
{
    D_LCD_BUS_DATA_DIR = 0;
	D_LCD_BUS_RS=0;
	D_LCD_BUS_RW=0;
    D_LCD_BUS_DATA = com;
    D_LCD_BUS_E=0;
    D_LCD_BUS_E=1;
    D_LCD_BUS_E=0;
}

void Write12864_Dat(uint8 dat)
{
    D_LCD_BUS_DATA_DIR = 0;
	D_LCD_BUS_RS=1;
	D_LCD_BUS_RW=0;
	D_LCD_BUS_DATA=dat;
    D_LCD_BUS_E=0;
    D_LCD_BUS_E=1;
    D_LCD_BUS_E=0;
}

void CheckBusy(void)            //检查忙
{
#if 1
    uint8 temp;
    D_LCD_BUS_RS=0;
    D_LCD_BUS_RW=1;
    D_LCD_BUS_E=0;
    D_LCD_BUS_DATA_DIR = 0xff;
    while(1)
    {
       D_LCD_BUS_DATA=0xFF;      //数据线为输入
       D_LCD_BUS_E=1;
       temp=D_LCD_BUS_DATA;
       D_LCD_BUS_E=0;
       if ((temp&0x80)==0)
           break;
    } 
#else
    Delay(10000);
    
#endif
}

void LCDSetLine(uint8 line)
{
    CheckBusy();
    switch(line)
    {
        case 0: 
            Write12864_Com(SETADDR1);  
            break;
        case 1: 
            Write12864_Com(SETADDR2);  
            break;
        case 2: 
            Write12864_Com(SETADDR3);  
            break;
        case 3: 
            Write12864_Com(SETADDR4);  
            break;
        default:
            Write12864_Com(SETADDR1);  
            break;
    }  
}

void LCDSendChar(uint8 data)
{
    CheckBusy();
    Write12864_Dat(data); 
}
void LCDSendString(const char* str)
{
    uint8 max,i;
    max=(uint8)strlen(str);
    for(i=0;i<max;i++)
    {
        CheckBusy();
        Write12864_Dat(str[i]);        
    }
}
