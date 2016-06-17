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

#define D_DEVICE_ADDRESS (0x5501)

    typedef enum
    {
        E_FRAME_FUNC_NONE = 0,
        E_FRAME_FUNC_RESULT,
        E_FRAME_FUNC_REGIEST_WIRTE_SHORT,
        E_FRAME_FUNC_REGIEST_READ_SHORT,
        E_FRAME_FUNC_LCD_WRITE,
        E_FRAME_FUNC_LCD_READ,
        E_FRAME_FUNC_LOOPBACK,
        E_FRAME_FUNC_MAX
    } FrameProtoFuncCode;

    typedef enum
    {
        E_FRAME_RESULT_OK = 0,
        E_FRAME_RESULT_NG,
        E_FRAME_RESULT_MAX
    } FrameProtoResultCode;

    typedef struct
    {
    	uint8 *bufPtr;
    	uint8 len;
    	uint8 maxLen;
    } DataWriterCtrl;

    typedef struct
    {
    	uint8 *bufPtr;
    	uint8 pos;
    	uint8 len;
    } DataReaderCtrl;


    typedef struct
    {
    	uint8	regiestAddress;
    } RegiestReadReq;

    typedef struct
    {
    	uint16 value;
    } RegiestReadRes;


    typedef struct
    {
    	uint8 	regiestAddress;
    	uint16	value;
    } RegiestWriteReq;

    typedef struct
    {
    	uint8 result;
    } ResultRes;

    typedef struct
    {
    	uint8	displayLine;
    } LcdReadReq;

    typedef struct
    {
    	uint8 str[9]; // max 8 char
    } LcdReadRes;

    typedef struct
    {
    	uint8	displayLine;
    	uint8	str[9]; // max 8 char
    } LcdWriteReq;


    typedef struct
    {
    	uint8	functionCode;
    	union
    	{
    		ResultRes		result;
    		RegiestReadReq 	regReadReq;
    		RegiestReadRes	regReadRes;
    		RegiestWriteReq	regWriteReq;
    		LcdReadReq		lcdReadReq;
    		LcdReadRes		lcdReadRes;
    		LcdWriteReq		lcdWriteReq;
    	} data;
    }  TransFrameData;


#ifdef	__cplusplus
}
#endif

#endif	/* FRAMEPROTOCOL_H */

