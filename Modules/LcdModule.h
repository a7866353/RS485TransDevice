/*
 * LcdModule.h
 *
 *  Created on: 2016Äê6ÔÂ25ÈÕ
 *      Author: linwei
 */

#ifndef LCDMODULE_H_
#define LCDMODULE_H_

#include "Common.h"


extern void LCD_Init();
extern void LCD_Set(uint8 line, char *str, uint8 strLen);
extern void LCD_Get(uint8 line, char *str, uint8 *strLen);

#endif /* LCDMODULE_H_ */
