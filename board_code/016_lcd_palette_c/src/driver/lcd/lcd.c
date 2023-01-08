#include "lcd.h"
#include "types.h"
#include "lcd_4_3.h"

#include "lcd_controller.h"

#define LCD_NUM 10
static pLcdParams pLcdArray[LCD_NUM];
static pLcdParams gLcdSelected;

int register_lcd(pLcdParams pLcdParam)
{
	int i = 0;

	for (i = 0; i < LCD_NUM; i++)
	{
		if (NULL == pLcdArray[i])
		{
			pLcdArray[i] = pLcdParam;
			return i;
		}
	}

	return -1;
}

int select_lcd(char *name)
{
	int i = 0;

	for (i = 0; i < LCD_NUM; i++)
	{
		if (NULL != pLcdArray[i])
		{
			if (0 == strcmp(pLcdArray[i]->name, name))
			{
				gLcdSelected = pLcdArray[i];
				return i;
			}
		}
	}

	return -1;
}

void lcd_add(void)
{
	lcd_4_3_add();
}

void get_lcd_params(unsigned int *fb_base, int *xres, int *yres, int *bpp)
{
	*xres    = gLcdSelected->xres;
	*yres    = gLcdSelected->yres;
	*bpp     = gLcdSelected->bpp;
	*fb_base = gLcdSelected->frame_buffer_base_addr;
}

void lcd_enable(void)
{
	lcd_controller_enable();
}

void lcd_disable(void)
{
	lcd_controller_disable();
}

int lcd_init(void)
{
	/* 注册LCD */
	lcd_add();

	/* 注册LCD控制器 */
	lcd_controller_add();

	/* 选择LCD */
	select_lcd("lcd_4_3");

	/* 选择LCD控制器 */
	select_lcd_controller("lcd_controller_s3c2440");

	/* 初始化LCD控制器 */
	lcd_controller_init(gLcdSelected);

	/* 使能LCD */
	lcd_enable();
}

