#include "LcdModule.h"
#include "LCDDriver.h"


#define D_LCD_CHAR_MAX (8)

static char gLcdStrArr[4][D_LCD_CHAR_MAX+1] = {0};

void LCD_Init()
{
	LCDInit();
}

void LCD_Set(uint8 line, char *str, uint8 strLen)
{
	char *pStr = gLcdStrArr[line];
	memset(pStr, 0, D_LCD_CHAR_MAX+1);
	memcpy(pStr, str, strLen);

	LCDSetLine(line);
	LCDSendString(pStr);
}

void LCD_Get(uint8 line, char *str, uint8 *strLen)
{
	char *pStr = gLcdStrArr[line];
	memcpy(str, pStr, D_LCD_CHAR_MAX+1);
	*strLen = D_LCD_CHAR_MAX;
}
