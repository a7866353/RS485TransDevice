#include "RS485Drvier.h"
#include <pic16F1947.h>

#define D_RS485_BUS_DIR         LATCbits.LATC0
#define D_RS485_BUS_DIR_OUT     (1)
#define D_RS485_BUS_DIR_IN      (0)
#define D_RS485_BUS_DIR_DIR     TRISCbits.TRISC0


void RS485Init()
{
    uint8 tmp;
    
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_OUT;
    D_RS485_BUS_DIR_DIR = 0;
    
    TRISCbits.TRISC6 = 0;  // TX1
    TRISCbits.TRISC7 = 1;  // RX1        

    SPBRG = 51;  // 9600bps=8M/[16*(51+1)]
    SPBRGH=0;

    TX1STAbits.SYNC=0; // ??????
    TX1STAbits.BRGH=1; // ?????
    TX1STAbits.TX9=0;  // ????9?
    BAUD1CONbits.BRG16=0; // ??????   
    
    PIE1bits .TX1IE = 0; // ??????

    TX1STAbits.TXEN = 1; // Enable TX
    RC1STAbits.CREN = 1; // Enable RX
    RC1STAbits.SPEN = 1; // Enable USART
    
    tmp = RC1REG;  // read RCREG to clear any pending IRQ
}

void RS485Send(uint8 data)
{
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_OUT;    
    TX1REG=data;
    while(TX1STAbits.TRMT == 0);
}
uint8 RS485GetChar()
{
    uint8 rcv;
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_IN;
    while(PIR1bits.RCIF == 0);
    rcv = RC1REG;
    
    return rcv;
}



