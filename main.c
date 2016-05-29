/* 
 * File:   main.c
 * Author: linwei
 *
 * Created on May 21, 2016, 12:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "type.h"


#include "LCDDriver.h"
#include "RS485Drvier.h"
#include "pic.h"
#include <pic16F1947.h>

__CONFIG (CP_OFF & WDTE_OFF & BOREN_OFF & 
        PWRTE_OFF & FOSC_HS & PLLEN_OFF & WRT_OFF & LVP_OFF & CPD_OFF);


void Delay(uint16 time);              //—” ±


void Delay(uint16 time)
{
    while(time--);
}


//============
// System Initialization
//==========

void systemInit()
{
    
}


//==============================
// LCD Test Sample
//==========================

uint8 const dis1[]="010101";
uint8 const dis2[]="020202";
uint8 const dis3[]="030303";
uint8 const dis4[]="040404";

void lcdTestSample()
{
    uint8 t;
    int16 max, len;
    
    Init12864();
    CheckBusy();
    Write12864_Com(SETADDR1);
    max=strlen(dis1);
    for(len=0; len<max; len++)
    {
       CheckBusy();
       Write12864_Dat(dis1[len]);
    }
    CheckBusy();
    Write12864_Com(SETADDR2);
    max=strlen(dis2);
    for(len=0;len<max; len++)
    {
       CheckBusy();
       Write12864_Dat(dis2[len]);
    }
    CheckBusy();
    Write12864_Com(SETADDR3);
    max=strlen(dis3);
    for(len=0;len<max; len++)
    {
       CheckBusy();
       Write12864_Dat(dis3[len]);
    }
    CheckBusy();
    Write12864_Com(SETADDR4);
    max=strlen(dis4);
    for(len=0;len<max; len++)
    {
       CheckBusy();
       Write12864_Dat(dis4[len]);
    }
    while(1);
}


//==============================
// RS485 Test Sample
//==========================


void testRS485()
{
    RS485Init();
    
    while(1)
    {
        RS485Send(0x55);
        RS485Send(0xaa);
    }
    
}

void testRS485Rev()
{
    uint8 rcv;
    Init12864();
    RS485Init(); 
    
    LCDSetLine(0);
    LCDSendString("Get:");
    while(1)
    {
        rcv = RS485GetChar();
        LCDSetLine(1);
        LCDSendChar(rcv);
    }

    
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    systemInit();
#if 0
     lcdTestSample();
#endif
     
#if 1
    testRS485();
#endif
    
#if 0
    testRS485Rev();
#endif
    
    return (EXIT_SUCCESS);
}





