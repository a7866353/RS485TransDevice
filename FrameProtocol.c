#include "FrameProtocol.h"
#include "DataPipe.h"

#include "RegiestModule.h"
#include "LcdModule.h"

#if 0
//============================
// Data Reader
//============================

typedef union
{
	uint8 	byteData;
	uint16 	shortData;
	uint32	intData;
	uint32	value;
} DataAccess;

void DataReader_Init(DataReaderCtrl *ctrl, uint8 *data, uint8 len)
{
	ctrl->bufPtr = data;
	ctrl->pos = 0;
	ctrl->len = len;
}

void DataReader_ReadFuncCode(DataReaderCtrl *ctrl, uint8 *out)
{
	DataAccess *pData = (DataAccess*)&(ctrl->bufPtr[ctrl->pos]);
	*out = pData->byteData;
	ctrl->pos++;
}

void DataReader_ReadByte(DataReaderCtrl *ctrl, uint8 *out)
{
	DataAccess *pData = (DataAccess*)&(ctrl->bufPtr[ctrl->pos]);
	*out = pData->byteData;
	ctrl->pos++;
}

void DataReader_ReadShort(DataReaderCtrl *ctrl, uint16 *out)
{
	DataAccess *pData = (DataAccess*)&(ctrl->bufPtr[ctrl->pos]);
	*out = pData->shortData;
	ctrl->pos += 2;
}

void DataReader_Reads(DataReaderCtrl *ctrl, uint8 *out, uint8 len)
{
	memcpy(out, &(ctrl->bufPtr[ctrl->pos]), len);
	ctrl->pos += len;

//============================
// Data Writer
//============================

void DataWriter_Init(DataWriterCtrl *ctrl, uint8 *buffer, uint8 maxLen)
{
	ctrl->bufPtr = buffer;
	ctrl->len = 0;
	ctrl->maxLen = maxLen;
}

void DataWriter_WriteFuncCode(DataWriterCtrl *ctrl, FrameProtoFuncCode code)
{
	DataAccess *pData = (DataAccess*)&(ctrl->bufPtr[ctrl->len]);

}

#endif

//=================================================================
typedef void(*FrameDispatch)(TransFrameData *);

static TransFrameData gFrameBuffer;
static uint8* getBuffer(FrameProtoFuncCode funcCode)
{
	gFrameBuffer.functionCode = funcCode;
	return gFrameBuffer.data.arr;
}
static void sendBuffer(uint8 size)
{
	DataPipeSend((uint8 *)&gFrameBuffer, size+1);
}



//================
// Dispatch Functions
//================
static void frameError(TransFrameData *data)
{
	ResultRes *res = (ResultRes *)getBuffer(E_FRAME_FUNC_RESULT);
	res->result = E_FRAME_RESULT_NG;
	sendBuffer(sizeof(ResultRes));
}

static void frameRegRead(TransFrameData *data)
{
	RegiestReadRes *res = (RegiestReadRes *)getBuffer(E_FRAME_FUNC_REGIEST_READ_SHORT);
	Regiest_Get(data->data.regReadReq.regiestAddress, &res->value);
	sendBuffer(sizeof(RegiestReadRes));
}

static void frameRegWrite(TransFrameData *data)
{
	Regiest_Set(data->data.regWriteReq.regiestAddress, data->data.regWriteReq.value);
	ResultRes *res = (ResultRes *)getBuffer(E_FRAME_FUNC_RESULT);
	res->result = E_FRAME_RESULT_OK;
	sendBuffer(sizeof(ResultRes));
}

static void frameLcdRead(TransFrameData *data)
{
	uint8 strLen;

	LcdReadReq *pReq = &(data->data.lcdReadReq);
	LcdReadRes *res = (LcdReadRes *)getBuffer(E_FRAME_FUNC_LCD_READ);
	LCD_Get(pReq->displayLine, res->str, &strLen);
	sendBuffer(sizeof(LcdReadRes));
}

static void frameLcdWrite(TransFrameData *data)
{
	LcdWriteReq *pReq = &(data->data.lcdWriteReq);
	LCD_Set(pReq->displayLine, pReq->str, sizeof(pReq->str));

	ResultRes *res = (ResultRes *)getBuffer(E_FRAME_FUNC_RESULT);
	res->result = E_FRAME_RESULT_OK;
	sendBuffer(sizeof(ResultRes));
}

static void frameLoopback(TransFrameData *data)
{
	// TODO
	ResultRes *res = (ResultRes *)getBuffer(E_FRAME_FUNC_RESULT);
	res->result = E_FRAME_RESULT_NG;
	sendBuffer(sizeof(ResultRes));
}





static FrameDispatch gDispatches[E_FRAME_FUNC_MAX] =
{
		frameError,
		frameError,
		frameRegWrite,
		frameRegRead,
		frameLcdWrite,
		frameLcdRead,
		frameLoopback,
};


static void onFrameRcv(FrameData *frame)
{
	TransFrameData *rcv = (TransFrameData *)frame->frame.data;
	FrameDispatch func = 0;
	if(rcv->functionCode >= E_FRAME_FUNC_MAX)
		return;
	func = gDispatches[rcv->functionCode];
	if(func == 0)
		return;
	func(frame->frame.data);
}

void FrameProto_Init()
{
	// Init Module
	LCD_Init();
	Regiest_Init();


	memset(&gFrameBuffer, 0, sizeof(gFrameBuffer));
	DataPipeInit(D_DEVICE_ADDRESS, onFrameRcv);
}



















