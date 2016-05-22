/* 
 * File:   RS485Samle.h
 * Author: linwei
 *
 * Created on May 22, 2016, 8:35 PM
 */

#ifndef RS485SAMLE_H
#define	RS485SAMLE_H

#include "type.h"

#ifdef	__cplusplus
extern "C" {
#endif


    extern void rs485Init();
    extern void rs485Send(uint8 data);
    extern uint8 rs485GetChar();

#ifdef	__cplusplus
}
#endif

#endif	/* RS485SAMLE_H */

