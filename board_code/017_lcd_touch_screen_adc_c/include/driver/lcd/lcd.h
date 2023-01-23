#ifndef __LCD_H
#define __LCD_H

typedef enum
{
	PINS_Polarity_Normal,
	PINS_Polarity_Invert,
} PINS_Polarity_e;

typedef struct pins_polarity
{
	int vclk;
	int rgb;
	int hsync;
	int vsync;

	int de;
	int pwren;
} pins_polarity;

typedef struct time_sequence
{
	int tvp;
	int tvb;
	int tvf;

	int thp;
	int thb;
	int thf;

	int vclk;
} time_sequence;

typedef struct lcd_param
{
	char *name;
	pins_polarity pin_polarity;
	time_sequence time_seq;
	int xres;
	int yres;
	int bpp;

	unsigned int frame_buffer_base_addr;
} lcd_param_t, *pLcdParams;

int register_lcd(pLcdParams pLcdParam);
int select_lcd(char *name);
void get_lcd_params(unsigned int *fb_base, int *xres, int *yres, int *bpp);
int lcd_init(void);
void lcd_enable(void);
void lcd_disable(void);



#endif
