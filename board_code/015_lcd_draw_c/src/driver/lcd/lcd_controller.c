#include "lcd.h"
#include "lcd_controller.h"
#include "lcd_controller_s3c2440.h"
#include "types.h"

#define LCD_CONTROLLER_NUM 10
static pLcdController p_array_lcd_controller[LCD_CONTROLLER_NUM];
static pLcdController gLcdControllerSelected;

int register_lcd_controller(pLcdController pLcdCon)
{
	int i = 0;

	for (i = 0; i < LCD_CONTROLLER_NUM; i++)
	{
		if (NULL == p_array_lcd_controller[i])
		{
			p_array_lcd_controller[i] = pLcdCon;
			return i;
		}
	}

	return -1;
}

int select_lcd_controller(char *name)
{
	int i = 0;

	for (i = 0; i < LCD_CONTROLLER_NUM; i++)
	{
		if (NULL != p_array_lcd_controller[i])
		{
			if (0 == strcmp(p_array_lcd_controller[i]->name, name))
			{
				gLcdControllerSelected = p_array_lcd_controller[i];
				return i;
			}
		}
	}

	return -1;
}

void lcd_controller_init(pLcdParams pLcdParam)
{
	if (NULL == gLcdControllerSelected)
	{
		return;
	}

	gLcdControllerSelected->init(pLcdParam);
}

void lcd_controller_enable(void)
{
	if (NULL == gLcdControllerSelected)
	{
		return;
	}

	gLcdControllerSelected->enable();
}

void lcd_controller_disable(void)
{
	if (NULL == gLcdControllerSelected)
	{
		return;
	}

	gLcdControllerSelected->disable();
}

void lcd_controller_add(void)
{
	s3c2440_lcd_controller_add();
}
