#include "DataPipe.h"
#include "RS485Drvier.h"
#include <string.h>



  
typedef enum 
{
    E_FRAME_STATUS_Init = 0,
    E_FRAME_STATUS_RCV_HEADER,        
    E_FRAME_STATUS_RCV_DATA,
} FrameStatus;

typedef struct
{
    FrameStatus state;
    uint16 deviceAddress;
    RcvCallback callback;
    uint8 pos;
    uint8 len;
}FrameRevCtrl;

static FrameRevCtrl gFrameRcvCtrl;
static FrameHeader gSlveHeader;
static FrameData gRcvData;



static void DataPipeSendSync(uint8 *buf, uint8 len)
{
    uint8 i;
    for(i=0;i<len;i++)
    {
        RS485Send(buf[i]);
    }    
}

static void reset()
{
    gFrameRcvCtrl.state = E_FRAME_STATUS_Init;
    gRcvData.frame.header.deviceAddress = 0;
}

static void onDataRcv(uint8 rcv, uint8 flag)
{
    FrameHeader *head = &gRcvData.frame.header;
    if (flag != 0)
    {
        reset();
        return;
    }
    
    
    if(gFrameRcvCtrl.state == E_FRAME_STATUS_Init)
    {

        gRcvData.data[1] = rcv;
        if( head->deviceAddress == gFrameRcvCtrl.deviceAddress)
        {
            gFrameRcvCtrl.state = E_FRAME_STATUS_RCV_HEADER;
            gFrameRcvCtrl.len = sizeof(FrameHeader) - 2;
            gFrameRcvCtrl.pos = 2;
        }
        else
        {
            gRcvData.data[0] = gRcvData.data[1];
        }
        return;
    }
    
    
    gRcvData.data[gFrameRcvCtrl.pos] = rcv;
    gFrameRcvCtrl.pos++;
    gFrameRcvCtrl.len--;
    if(gFrameRcvCtrl.len > 0)
        return;
    // Receive finish
    if(E_FRAME_STATUS_RCV_HEADER == gFrameRcvCtrl.state)
    {
        gFrameRcvCtrl.state = E_FRAME_STATUS_RCV_DATA;
        gFrameRcvCtrl.len = head->length; 
    }
    else if(E_FRAME_STATUS_RCV_DATA == gFrameRcvCtrl.state)
    {
        if( gFrameRcvCtrl.callback != 0)
        {
            gFrameRcvCtrl.callback(&gRcvData);
        }
        reset();
    }
    else
    {
        // Error Status Value
    }
}

void DataPipeInit(uint16 deviceAddress,RcvCallback func)
{
    memset(&gFrameRcvCtrl, 0, sizeof(gFrameRcvCtrl));
    memset(&gSlveHeader, 0, sizeof(gSlveHeader));
    
    gFrameRcvCtrl.callback = func;
    gFrameRcvCtrl.deviceAddress = deviceAddress;
    gSlveHeader.deviceAddress = deviceAddress;

    RS485Init(onDataRcv);
}


void DataPipeSend(uint8 *buf, uint8 len)
{
    gSlveHeader.length = len;
    DataPipeSendSync((uint8 *)&gSlveHeader, (uint8)sizeof(gSlveHeader));
    DataPipeSendSync(buf, len);
}

