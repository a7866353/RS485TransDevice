/* 
 * File:   FrameProtocol.h
 * Author: linwei
 *
 * Created on May 29, 2016, 4:09 PM
 */

#ifndef FRAMEPROTOCOL_H
#define	FRAMEPROTOCOL_H

#include "Common.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum
    {
        E_FRAME_PROTO_NONE = 0,
        E_FRAME_PROTO_RESULT,
        E_FRAME_PROTO_REGIEST_WRITE_SHORT,        
        E_FRAME_PROTO_REGIEST_READ_SHORT,
        E_FRAME_PROTO_LCD_WRITE,
        E_FRAME_PROTO_LCD_READ,
        E_FRAME_PROTO_LOOPBACK,
    } FrameProtoFuncCode;
    
    typedef struct
    {
        uint8 *BufPtr;
        uint8 Pos;
            
    } DataWriterCtrl;
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* FRAMEPROTOCOL_H */

