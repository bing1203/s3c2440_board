#include "uart.h"
#include "sdram.h"
#include "nand.h"
#include "adc.h"
#include "stdio.h"
#include "stdio_lcd.h"

#include "lcd.h"
#include "framebuffer.h"
#include "geometry.h"
#include "font.h"

#include "s3c2440.h"

static void delay(unsigned int t)
{
	while (t--);
}

void LCD_Test(void)
{
	S3C2440_LCD_CTL_t * const pLCD = S3C2440_GetLCDCtlBaseAddr();

	lcd_init();

	fb_get_lcd_params();

	fill_fb(0, 480, 0, 272, 0xBB);

	draw_char_8x16(0, 0, 'W', 0xAA, 0xFF);

    printf_lcd(0, 16, "test lcd...");

}

int main(int argc, char *argv[])
{
	UART_Init();

	printf("\033[00;31mhello, world!!!\r\n\033[0m");

	LCD_Test();

    ADC_Init();

	while (1)
    {
        unsigned short value = 0;
        value = ADC_readDataX();
        printf_lcd(0, 32, "x_value:%d", value);

        value = ADC_readDataY();
        printf_lcd(0, 64, "y_value:%d", value);
    }

	return 0;
}


