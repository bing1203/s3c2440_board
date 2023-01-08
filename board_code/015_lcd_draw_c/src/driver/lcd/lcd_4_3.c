#include "lcd.h"

#define LCD_FB_BASE 0x30000000

struct lcd_param lcd_4_3 = {
	.name = "lcd_4_3",
	.pin_polarity = {
		.vclk  = PINS_Polarity_Normal,
		.vsync = PINS_Polarity_Invert,
		.hsync = PINS_Polarity_Invert,
		.rgb   = PINS_Polarity_Normal,
		.de    = PINS_Polarity_Normal,
		.pwren = PINS_Polarity_Normal,
	},
	.time_seq = {
		.tvb = 2,
		.tvf = 2,
		.tvp = 10,
		.thp = 41,
		.thb = 2,
		.thf = 2,
		.vclk = 10,
	},
	.xres = 480,
	.yres = 272,
	.bpp  = 24,
	.frame_buffer_base_addr = LCD_FB_BASE,
};

void lcd_4_3_add(void)
{
	register_lcd(&lcd_4_3);
}
