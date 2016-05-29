#include "RS485Drvier.h"
#include <pic16F1947.h>
#include <string.h>


#define D_RS485_BUS_DIR         LATCbits.LATC0
#define D_RS485_BUS_DIR_OUT     (1)
#define D_RS485_BUS_DIR_IN      (0)
#define D_RS485_BUS_DIR_DIR     TRISCbits.TRISC0


typedef struct
{
    RS485RcvCallback rcvCb;
} RS485Crtl;


static RS485Crtl gRS485Ctrl;


void RS485Init()
{
    uint8 tmp;
    
    memset(&gRS485Ctrl, 0, sizeof(gRS485Ctrl));
    
    
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_IN;
    D_RS485_BUS_DIR_DIR = 0;
    
    TRISCbits.TRISC6 = 0;  // TX1
    TRISCbits.TRISC7 = 1;  // RX1        

    // SPBRG = 51;  // 9600bps=8M/[16*(51+1)]
    SPBRG = 207;  // 9600bps=8M * 4 / [16*(207.33+1)]
    SPBRGH=0;

    TX1STAbits.SYNC=0; // ??????
    TX1STAbits.BRGH=1; // ?????
    TX1STAbits.TX9=0;  // ????9?
    BAUD1CONbits.BRG16=0; // ??????   
    
    PIE1bits .TX1IE = 0; // ??????

    TX1STAbits.TXEN = 1; // Enable TX
    
    tmp = RC1REG;  // read RCREG to clear any pending IRQ
    RC1STAbits.CREN = 1; // Enable RX
    PIE1bits.RC1IE = 1;
    INTCONbits.PEIE = 1;
    
    RC1STAbits.SPEN = 1; // Enable USART
    

}

void RS485Interrupt()
{
    uint8 rcv;
    uint8 flag = 0;
    rcv = RC1REG;
    if( RC1STAbits.FERR == 1)
    {
        // Rcv Error
        flag |= 1;
    }

    if( RC1STAbits.OERR == 1)
    {
        flag |= 2;
        ResetRX();
    }   
    
    if(gRS485Ctrl.rcvCb != NULL)
        gRS485Ctrl.rcvCb(rcv, flag);
}
void RS485SetCallback(RS485RcvCallback func)
{
    gRS485Ctrl.rcvCb = func;
}

void RS485Send(uint8 data)
{
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_OUT;    
    TX1REG=data;
    while(TX1STAbits.TRMT == 0);
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_IN;
}
uint8 RS485GetChar()
{
    uint8 rcv;
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_IN;
    rcv = RC1REG;
    
    return rcv;
}
uint8 RS485GetCharWait()
{
    uint8 rcv;
    D_RS485_BUS_DIR = D_RS485_BUS_DIR_IN;
    while(PIR1bits.RCIF == 0);
    rcv = RC1REG;
    
    return rcv;
}

void ResetRX()
{
    RC1STAbits.CREN = 0; // Enable RX
    RC1STAbits.CREN = 1; // Enable RX
}





