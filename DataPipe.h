/* 
 * File:   DataPipe.h
 * Author: linwei
 *
 * Created on May 29, 2016, 3:53 PM
 */

#ifndef DATAPIPE_H
#define	DATAPIPE_H

#include "Common.h"

#ifdef	__cplusplus
extern "C" {
#endif
    

#define D_DATA_FRAME_MAX_LENGTH (128)
    typedef struct
    {
        uint16 deviceAddress;
        uint8 length;
    } FrameHeader;

    typedef union
    {
        struct
        {
            FrameHeader header;
            uint8 data[];
         } frame;

        uint8 data[D_DATA_FRAME_MAX_LENGTH];
    } FrameData;
    
    typedef void (*RcvCallback)(FrameData *);
    
    extern void DataPipeInit(uint16 deviceAddress);
    extern void DataPipeFrameCB(RcvCallback func);
    extern void DataPipeSend(uint8 *buf, uint8 len);

#ifdef	__cplusplus
}
#endif

#endif	/* DATAPIPE_H */

