/*
 * RegiestModule.h
 *
 *  Created on: 2016Äê6ÔÂ17ÈÕ
 *      Author: linwei3
 */

#ifndef REGIESTMODULE_H_
#define REGIESTMODULE_H_

#include "Common.h"

typedef enum
{
	E_REG_01,
	E_REG_02,
	E_REG_03,
	E_REG_04,
	E_REG_05,
	E_REG_MAX
}RegiestNames;

extern void Regiest_Init();
extern void Regiest_Set(uint8 addr, uint16 value);
extern void Regiest_Get(uint8 addr, uint16 *value);

#endif /* REGIESTMODULE_H_ */
