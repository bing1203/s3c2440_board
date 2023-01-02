#include "s3c2440.h"
#include "s3c2440_uart.h"
int LED_Init()
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();

	pGPIO->GPFCON &= ~((3<<8) | (3<<10) | (3<<12));
	pGPIO->GPFCON |= ((1<<8) | (1<<10) | (1<<12));

	pGPIO->GPFDAT = 0xFFFFFFFF;
}

int LED_On()
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();

	pGPIO->GPFDAT = 0;

	return 0;
}

int LED_Off()
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();

	pGPIO->GPFDAT = 0xFFFFFFFF;

	return 0;
}

