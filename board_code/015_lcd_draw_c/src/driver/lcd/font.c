#include "font.h"
#include "lcd.h"

void draw_char_8x8(int x, int y, char ch, int frontColor, int background)
{
	int i = 0;
	int ii = 0;
	int iii = 0;
	char *pCh = &fontdata_8x8[ch * 8];

	for (i = 0; i < 8; i++)
	{
		for (ii = 7; ii >= 0; ii--)
		{
			iii = (*pCh >> ii) & 0x1;
			if (0 == iii)
			{
				fb_put_pixel(x + 7 - ii, y + i, background);
			}
			else
			{
				fb_put_pixel(x + 7 - ii, y + i, frontColor);
			}
		}
		pCh++;
	}
}

void draw_char_8x16(int x, int y, char ch, int frontColor, int background)
{
	int i = 0;
	int ii = 0;
	int iii = 0;
	char *pCh = &fontdata_8x16[ch * 16];

	for (i = 0; i < 16; i++)
	{
		for (ii = 7; ii >= 0; ii--)
		{
			iii = (*pCh >> ii) & 0x1;
			if (0 == iii)
			{
				fb_put_pixel(x + 7 - ii, y + i, background);
			}
			else
			{
				fb_put_pixel(x + 7 - ii, y + i, frontColor);
			}
		}
		pCh++;
	}
}

void draw_char_6x11(int x, int y, char ch, int frontColor, int background)
{
	int i = 0;
	int ii = 0;
	int iii = 0;
	char *pCh = &fontdata_6x11[ch * 11];

	for (i = 0; i < 11; i++)
	{
		for (ii = 7; ii >= 0; ii--)
		{
			iii = (*pCh >> ii) & 0x1;
			if (0 == iii)
			{
				fb_put_pixel(x + 7 - ii, y + i, background);
			}
			else
			{
				fb_put_pixel(x + 7 - ii, y + i, frontColor);
			}
		}
		pCh++;
	}
}

void draw_char_7x14(int x, int y, char ch, int frontColor, int background)
{
	int i = 0;
	int ii = 0;
	int iii = 0;
	char *pCh = &fontdata_7x14[ch * 14];

	for (i = 0; i < 14; i++)
	{
		for (ii = 7; ii >= 0; ii--)
		{
			iii = (*pCh >> ii) & 0x1;
			if (0 == iii)
			{
				fb_put_pixel(x + 7 - ii, y + i, background);
			}
			else
			{
				fb_put_pixel(x + 7 - ii, y + i, frontColor);
			}
		}
		pCh++;
	}
}