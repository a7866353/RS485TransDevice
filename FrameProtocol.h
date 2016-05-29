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
        E_FRAME_PROTO_ECHO = 0,
        E_FRAME_PROTO_WRITE,
        E_FRAME_PROTO_READ,
    } FrameProtoFuncCode;


#ifdef	__cplusplus
}
#endif

#endif	/* FRAMEPROTOCOL_H */

