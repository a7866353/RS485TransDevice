/*
 * LCDDriver.h
 *
 *  Created on: 2016年5月22日
 *      Author: linwei
 */

#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_

#include "type.h"

#include "string.h"                      //for strlen()

#define    SETMODE       0x30   //并口8位数据接口,基本指令
#define 	DISOPEN      0x0C   //显示开,不显示光标,光标不闪烁
#define 	DISMODE      0x06   //读写字符后地址加1,屏显不移动
#define    SETADDR1   0x80   //设置数据地址指针第一行
#define    SETADDR2   0x90   //设置数据地址指针第二行
#define    SETADDR3   0x88   //设置数据地址指针第三行
#define    SETADDR4   0x98   //设置数据地址指针第四行
#define 	CLEAR     0x01   //清屏,数据指针清零
#define 	RET          0x02   //回车,数据指针清零

void Init12864();
void Write12864_Com(uint8 com);
void Write12864_Dat(uint8 dat);

void CheckBusy(void);       //检查忙

extern void LCDSetLine(uint8 line);
extern void LCDSendChar(uint8 data);
extern void LCDSendString(char* str);

#endif /* LCDDRIVER_H_ */
