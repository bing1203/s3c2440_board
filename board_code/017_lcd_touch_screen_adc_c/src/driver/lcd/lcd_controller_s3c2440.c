#include "lcd_controller.h"
#include "s3c2440.h"

#define PALETTE_BASE_ADDR (0x4D000400)
#define PALETTE_SIZE (0xFF)

static void s3c2440_lcd_gpio_init(void)
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();

	/* 背光引脚 */
	pGPIO->GPBCON &= ~0x03;
	pGPIO->GPBCON |= 0x01;

	/* LCD专用引脚 */
	pGPIO->GPCCON = 0xAAAAAAAA;
	pGPIO->GPDCON = 0xAAAAAAAA;
	pGPIO->GPGCON |= (3 << 8);

}

static void s3c2440_lcd_controller_init(pLcdParams pLcdParam)
{
	S3C2440_LCD_CTL_t * const pLCD = S3C2440_GetLCDCtlBaseAddr();
	volatile unsigned int *pPaletteAddr     = (volatile unsigned int *)PALETTE_BASE_ADDR;
	int i = 0;
	unsigned int clkval = 0;
	unsigned int bppmode = 0;
	unsigned int pixelplace = 0;

	s3c2440_lcd_gpio_init();

	/* palette */
	for (i = 0; i < PALETTE_SIZE; i++)
	{
		*pPaletteAddr = i;
		pPaletteAddr++;
	}

	clkval = (100 / pLcdParam->time_seq.vclk) / 2 - 1;

	bppmode = pLcdParam->bpp == 24 ? 0x0D : 
			  pLcdParam->bpp == 16 ? 0x0C : 
			                         0x0B; 

	pLCD->LCDCON1 = (clkval << 8) |  /* VCLK = HCLK / [(CLKVAL + 1) x 2] */
					(0 << 7) |       /* MMODE */
					(3 << 5) |       /* PNRMODE */
					(bppmode << 1) | /* BPPMODE */
					(0 << 0);        /* ENVID */

	pLCD->LCDCON2 = ((pLcdParam->time_seq.tvb - 1) << 24) | /* VBPD */
					((pLcdParam->yres - 1)         << 14) | /* LINEVAL， 与Y方向分辨率相同 */
					((pLcdParam->time_seq.tvf - 1) << 6)  | /* VFPD */
					((pLcdParam->time_seq.tvp - 1) << 0);   /* VSPW */

	pLCD->LCDCON3 = ((pLcdParam->time_seq.thb - 1) << 19) | /* HBPD */
					((pLcdParam->xres - 1)         << 8)  | /* HOZVAL，与X方向分辨率相同 */
					((pLcdParam->time_seq.thf - 1) << 0);   /* HFPD */

	pLCD->LCDCON4 = ((pLcdParam->time_seq.thp)     << 0);   /* HSPW */

	pixelplace = pLcdParam->bpp == 24 ? 0 :
				 pLcdParam->bpp == 16 ? 1 : (1 << 1);

	pLCD->LCDCON5 = (1 << 11) | /* FRM565 */
					(pLcdParam->pin_polarity.vclk  << 10) | /* INVVCLK */
					(pLcdParam->pin_polarity.hsync << 9)  | /* INVVLINE */
					(pLcdParam->pin_polarity.vsync << 8)  | /* INVVFRAME */
					(pLcdParam->pin_polarity.rgb   << 7)  | /* INVVD */
					(pLcdParam->pin_polarity.de    << 6)  | /* INVVDEN */
					(pLcdParam->pin_polarity.pwren << 5)  | /* INVPWREN */
					pixelplace;

	/* frame buffer start address */
	pLCD->LCDSADDR1 = (((pLcdParam->frame_buffer_base_addr >> 22) & 0x1FF) << 21) | 
	                  (((pLcdParam->frame_buffer_base_addr >> 1) & 0x1FFFFF) << 0);

	/* frame buffer end address */
	pLCD->LCDSADDR2 = pLcdParam->bpp == 24 ? ((pLcdParam->frame_buffer_base_addr + pLcdParam->xres * pLcdParam->yres * 4) >> 1) & 0x1FFFFF :
					  pLcdParam->bpp == 16 ? ((pLcdParam->frame_buffer_base_addr + pLcdParam->xres * pLcdParam->yres * 2) >> 1) & 0x1FFFFF :
					  						 ((pLcdParam->frame_buffer_base_addr + pLcdParam->xres * pLcdParam->yres * 1) >> 1) & 0x1FFFFF;

}

static void s3c2440_lcd_controller_enable(void)
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();
	S3C2440_LCD_CTL_t * const pLCD = S3C2440_GetLCDCtlBaseAddr();

	/* 背光引脚 */
	pGPIO->GPBDAT |= (1 << 0);

	/* power enable */
	pLCD->LCDCON5 |= (1 << 3);

	/* lcd controller enable */
	pLCD->LCDCON1 |= (1 << 0);

}
static void s3c2440_lcd_controller_disable(void)
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();
	S3C2440_LCD_CTL_t * const pLCD = S3C2440_GetLCDCtlBaseAddr();

	/* 背光引脚 */
	pGPIO->GPBDAT &= ~(1 << 0);

	/* power disable */
	pLCD->LCDCON5 &= ~(1 << 3);

	/* lcd controller disable */
	pLCD->LCDCON1 &= ~(1 << 0);

}


struct lcd_controller lcd_controller_s3c2440 = {
	.name = "lcd_controller_s3c2440",
	.init = s3c2440_lcd_controller_init,
	.enable = s3c2440_lcd_controller_enable,
	.disable = s3c2440_lcd_controller_disable,
};

void s3c2440_lcd_controller_add(void)
{
	register_lcd_controller(&lcd_controller_s3c2440);
}
