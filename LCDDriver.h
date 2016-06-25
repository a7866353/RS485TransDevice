/*
 * LCDDriver.h
 *
 *  Created on: 2016��5��22��
 *      Author: linwei
 */

#ifndef LCDDRIVER_H_
#define LCDDRIVER_H_

#include "Common.h"

#define    SETMODE       0x30   //����8λ���ݽӿ�,����ָ��
#define 	DISOPEN      0x0C   //��ʾ��,����ʾ���,��겻��˸
#define 	DISMODE      0x06   //��д�ַ����ַ��1,���Բ��ƶ�
#define    SETADDR1   0x80   //�������ݵ�ַָ���һ��
#define    SETADDR2   0x90   //�������ݵ�ַָ��ڶ���
#define    SETADDR3   0x88   //�������ݵ�ַָ�������
#define    SETADDR4   0x98   //�������ݵ�ַָ�������
#define 	CLEAR     0x01   //����,����ָ������
#define 	RET          0x02   //�س�,����ָ������


extern void Write12864_Com(uint8 com);
extern void Write12864_Dat(uint8 dat);

extern void CheckBusy(void);       //���æ

extern void LCDInit();
extern void LCDSetLine(uint8 line);
extern void LCDSendChar(uint8 data);
extern void LCDSendString(const char* str);

#endif /* LCDDRIVER_H_ */
