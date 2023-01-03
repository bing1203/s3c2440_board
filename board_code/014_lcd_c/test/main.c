#include "uart.h"
#include "sdram.h"
#include "nand.h"
#include "stdio.h"

#include "lcd.h"
#include "image1.h"
#include "image2.h"
#include "image3.h"
#include "image4.h"
#include "image5.h"
#include "image6.h"
#include "image7.h"

const char (*pImg[7])[272][480] = {
	image1_rgb,
	image2_rgb,
	image3_rgb,
	image4_rgb,
	image5_rgb,
	image6_rgb,
	image7_rgb,
};

static void delay(unsigned int t)
{
	while (t--);
}

void LCD_Test(void)
{
	unsigned int fb_base;
	int xres, yres, bpp;
	int x = 0;
	int y = 0;
	int i = 0;

	printf("test lcd...\r\n");

	lcd_init();

	get_lcd_params(&fb_base, &xres, &yres, &bpp);

	printf("fa_base:0x%x, xres:%d, yres:%d, bpp:%d\r\n", fb_base, xres, yres, bpp);

	while (1)
	{
		const char (*pImageR)[480] = pImg[i][0];
		const char (*pImageG)[480] = pImg[i][1];
		const char (*pImageB)[480] = pImg[i][2];

		i++;
		if (7 <= i)
		{
			i = 0;
		}
		
		if (16 == bpp)
		{
			unsigned short *p = (unsigned short *)fb_base;

			for (y = 0; y < yres; y++)
			{
				for (x = 0; x < xres; x++)
				{
					*p = (((((unsigned short)pImageR[y][x]) & 0x1F) * 32 / 256) << 11) | 
						 (((((unsigned short)pImageG[y][x]) & 0x3F) * 64 / 256) << 5)  | 
						 (((((unsigned short)pImageB[y][x]) & 0x1F) * 32 / 256) << 0);
					p++;
				}
			}
		}
		else if (24 == bpp)
		{
			unsigned int *p = (unsigned int *)fb_base;

			for (y = 0; y < yres; y++)
			{
				for (x = 0; x < xres; x++)
				{
					*p = (((unsigned int)pImageR[y][x] & 0xFF) << 16) | 
						 (((unsigned int)pImageG[y][x] & 0xFF) << 8)  | 
						 (((unsigned int)pImageB[y][x] & 0xFF) << 0);
					p++;
				}
			}
		}

		delay(1000000);
	}
}



int main(int argc, char *argv[])
{
	UART_Init();

	printf("\033[00;31mhello, world!!!\r\n\033[0m");

	LCD_Test();

	while (1);

	return 0;
}


