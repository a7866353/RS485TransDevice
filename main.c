/* 
 * File:   main.c
 * Author: linwei
 *
 * Created on May 21, 2016, 12:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Common.h"

#include "LCDDriver.h"
#include "RS485Drvier.h"
#include "DataPipe.h"

#include "pic.h"
#include <pic16F1947.h>





__CONFIG (CP_OFF & WDTE_OFF & BOREN_OFF & 
        PWRTE_OFF & FOSC_HS & PLLEN_OFF & WRT_OFF & LVP_OFF & CPD_OFF);




//============
// System Initialization
//==========

void systemInit()
{
    INTCONbits.GIE = 1; //??????
}
void interrupt ServiceRoutine(void) 
{
    if(RC1STAbits.CREN ==1 && (PIR1bits.RC1IF | RC1STAbits.FERR | RC1STAbits.OERR)==1)
    {
        RS485Interrupt();
    }
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
    
    LCDInit();
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
    RS485Init(null);
    
    while(1)
    {
        RS485Send(0x55);
        RS485Send(0xaa);
    }
    
}

void testRS485Rev()
{
    uint8 rcv;
    LCDInit();
    RS485Init(null); 
    
    LCDSetLine(0);
    LCDSendString("Get:");
    while(1)
    {
        rcv = RS485GetCharWait();
        LCDSetLine(1);
        LCDSendChar(rcv);
    }
}

//-------------
static void rs485RcvCB(uint8 rcv, uint8 flag)
{
    if( flag != 0 )
        return;
    LCDSetLine(1);
    LCDSendChar(rcv);
}
void testRS485RevRB()
{
	LCDInit();
    RS485Init(rs485RcvCB); 
    RS485SetCallback();
    LCDSetLine(0);
    LCDSendString("Get:");
    while(1)
    {
        
    }
}


//==============================
// DataPipe Test Sample
//==========================
#define D_SLAVE_ADDRESS ((uint16)0x0101)

static void DataPipeCB(FrameData *frame)
{
    LCDSetLine(1);
    LCDSendChar(frame->frame.data[0]);
    DataPipeSend(frame->frame.data, frame->frame.header.length);
}
static void DataPipeTest()
{
	LCDInit();
    LCDSetLine(0);
    LCDSendString("Get:");
    
    DataPipeInit(D_SLAVE_ADDRESS, DataPipeCB);
    
    while(1)
    {
            
    }
    
}

//==============================
// FramdData Test Sample
//==========================
static void DataFrameTest()
{
    FrameProto_Init();
}



/*
 * 
 */
int main(int argc, char** argv) {
    systemInit();
#if 0
     lcdTestSample();
#endif
     
#if 0
    testRS485();
#endif
    
#if 0
    testRS485Rev();
#endif
    
#if 0
    testRS485RevRB();
#endif
 
#if 0
    DataPipeTest();
#endif
    
#if 1
    DataFrameTest();
#endif
    
    while(1);
    return (EXIT_SUCCESS);
}





