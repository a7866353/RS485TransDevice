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
#include "pic.h"
#include <pic16F1947.h>

__CONFIG (CP_OFF&WDTE_OFF& BOREN_OFF&PWRTE_OFF &FOSC_HS&WRT_OFF&LVP_OFF&CPD_OFF);



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
    char i=0;
    SPBRG=25;
    SPBRGH=0;

    TX1STAbits.SYNC=0; // ??????
    TX1STAbits.BRGH=0; // ??????
    TX1STAbits.TX9=0;  // ????9?
    BAUD1CONbits.BRG16=0; // ??????   
   //BRGH=1; // ??????

    PIE1bits .TX1IE=1; // ????
    RC1STAbits.SPEN = 1; // USART??
   // ????????????????????????????
   // ?????????????????????
   //RCSTA=0b10000000;  
   //TXSTA=0b00100100;
   TXREG='A'; // ?????????TXREG??USART????????
   while(1)
   {
#if 0
     while(strSentData[i]!='\0') // ?????????
     {
       TXREG=strSentData[i];
       while(TRMT!=1) // ??????????????
       {         
       }
       i++;
     }
    i=0;
#endif
   } 
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    systemInit();


    return (EXIT_SUCCESS);
}





