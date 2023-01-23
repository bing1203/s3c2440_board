#ifndef __S3C2440_H
#define __S3C2440_H

#include "s3c2440_soc.h"

typedef enum
{
	S3C2440_UART0,
	S3C2440_UART1,
	S3C2440_UART2,
} S3C2440_UARTn_e;

S3C2440_MEM_CTL_t * const S3C2440_GetMemCtlBaseAddr(void);
S3C2440_NAND_CTL_t * const S3C2440_GetNandCtlBaseAddr(void);
S3C2330_CLOCK_POWER_CTL_t * const S3C2440_GetClockPowerCtlBaseAddr(void);
S3C2440_LCD_CTL_t * const S3C2440_GetLCDCtlBaseAddr(void);
S3C2440_GPIO_CTL_t * const S3C2440_GetGPIOCtlBaseAddr(void);
S3C2440_UART_CTL_t * const S3C2440_GetUARTCtlBaseAddr(S3C2440_UARTn_e UARTn);
S3C2440_ADC_CTL_t * const S3C2440_GetADCCtlBaseAddr(void);

#endif
