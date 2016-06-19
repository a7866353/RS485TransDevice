/* 
 * File:   RS485Drvier.h
 * Author: linwei
 *
 * Created on May 22, 2016, 8:35 PM
 */

#ifndef RS485DRVIER_H
#define	RS485DRVIER_H

#include "Common.h"

#ifdef	__cplusplus
extern "C" {
#endif
    typedef void (*RS485RcvCallback)(uint8 data, uint8 flag);

    extern void RS485Init(RS485RcvCallback func);
    extern void RS485Interrupt();
    extern void RS485Send(uint8 data);
    extern uint8 RS485GetChar();
    extern uint8 RS485GetCharWait();
    extern void ResetRX();
#ifdef	__cplusplus
}
#endif

#endif	/* RS485DRVIER_H */

