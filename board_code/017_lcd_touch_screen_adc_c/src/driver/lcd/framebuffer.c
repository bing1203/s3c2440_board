#include "lcd.h"

/* LCD参数 */
static unsigned int fb_base;
static int xres, yres, bpp;

static unsigned short convert32bppto16bpp(unsigned int rgb)
{
	unsigned int r = (rgb >> 16) & 0xFF;
	unsigned int g = (rgb >> 8) & 0xFF;
	unsigned int b = rgb & 0xFF;

	r = r >> 3;
	g = g >> 2;
	b = b >> 3;

	return (r << 11) | (g << 5) | b;
}

void fb_get_lcd_params(void)
{
	get_lcd_params(&fb_base, &xres, &yres, &bpp);
}

/* 画点 */
void fb_put_pixel(int x, int y, unsigned int color)
{
	unsigned char  *pc;
	unsigned short *pw;
	unsigned int   *pdw;

	unsigned int pixel_base;

	switch (bpp)
	{
		case 8:
		{
			pixel_base = fb_base + xres * y + x;
			pc = (unsigned char *)pixel_base;
			*pc = color;
			break;
		}

		case 16:
		{
			pixel_base = fb_base + xres * 2 * y + 2 * x;
			pw = (unsigned short *)pixel_base;
			*pw = convert32bppto16bpp(color);
			break;
		}

		case 24:
		{
			pixel_base = fb_base + xres * 4 * y + 4 * x;
			pdw = (unsigned int *)pixel_base;
			*pdw = color;
			break;
		}
	}
}