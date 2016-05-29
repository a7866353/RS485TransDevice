/* 
 * File:   RS485Drvier.h
 * Author: linwei
 *
 * Created on May 22, 2016, 8:35 PM
 */

#ifndef RS485DRVIER_H
#define	RS485DRVIER_H

#include "type.h"

#ifdef	__cplusplus
extern "C" {
#endif


    extern void RS485Init();
    extern void RS485Send(uint8 data);
    extern uint8 RS485GetChar();

#ifdef	__cplusplus
}
#endif

#endif	/* RS485DRVIER_H */

