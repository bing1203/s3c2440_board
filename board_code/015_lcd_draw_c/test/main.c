#include "uart.h"
#include "sdram.h"
#include "nand.h"
#include "stdio.h"

#include "lcd.h"
#include "framebuffer.h"
#include "geometry.h"
#include "font.h"
static void delay(unsigned int t)
{
	while (t--);
}

void LCD_Test(void)
{
	char *str = "Hello, world!!!";
	int i = 0;
	printf("test lcd...\r\n");

	lcd_init();

	fb_get_lcd_params();

	fill_fb(0, 480, 0, 272, 0xFFFFFF);

	draw_circle(240, 136, 50, 0xFF0000);

	draw_line(0, 0, 480, 272, 0x00FF00);
	draw_line(480, 0, 0, 272, 0x0000FF);


	while(*str)
	{
		draw_char_8x8(i * 8, 0, *str, 0x000000, 0xFFFFFF);
		draw_char_8x16(i * 8, 9, *str, 0x000000, 0xFFFFFF);
		draw_char_6x11(i * 6 , 26, *str, 0x000000, 0xFFFFFF);
		draw_char_7x14(i * 7, 38, *str, 0x000000, 0xFFFFFF);
		str++;
		i++;
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


