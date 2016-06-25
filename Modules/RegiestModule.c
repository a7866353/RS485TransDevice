#include "RegiestModule.h"


static uint16 gRegValueArr[E_REG_MAX] = {0};

void Regiest_Init()
{
	memset(&gRegValueArr, 0, sizeof(gRegValueArr));
}

void Regiest_Set(uint8 addr, uint16 value)
{
	if(addr >= E_REG_MAX)
		return;
	gRegValueArr[addr] = value;
}

void Regiest_Get(uint8 addr, uint16 *value)
{

	if(addr >= E_REG_MAX)
	{
		*value = 0;
		return;
	}
	*value = gRegValueArr[addr];
}
