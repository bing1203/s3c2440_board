#ifndef __LCD_CONTROLLER_H
#define __LCD_CONTROLLER_H

#include "lcd.h"

typedef struct lcd_controller
{
	char *name;
	void (*init)(pLcdParams pLcdParam);
	void (*enable)(void);
	void (*disable)(void);
} lcd_controller_t, *pLcdController;

int register_lcd_controller(pLcdController pLcdCon);
int select_lcd_controller(char *name);
void lcd_controller_init(pLcdParams pLcdParam);
void lcd_controller_enable(void);
void lcd_controller_disable(void);
void lcd_controller_add(void);


#endif

