#ifndef __S3C2440_H
#define __S3C2440_H

#include "s3c2440_soc.h"

typedef enum
{
	S3C2440_UART0,
	S3C2440_UART1,
	S3C2440_UART2,
} S3C2440_UARTn_e;

typedef enum
{
	MEM_CTL_BASE_ADDR         = 0x48000000,

	USB_HOST_CTL_BASE_ADDR    = 0x49000000,

	DMA_CTL_BASE_ADDR         = 0x4B000000,

	CLOCK_POWER_CTL_BASE_ADDR = 0x4C000000,

	LCD_CTL_BASE_ADDR         = 0x4D000000,

	NAND_CTL_BASE_ADDR        = 0x4E000000,

	CAMERA_CTL_BASE_ADDR      = 0x4F000000,

	UART_CTL_BASE_ADDR        = 0x50000000,

	TIMER_CTL_BASE_ADDR       = 0x51000000,

	WTDOG_CTL_BASE_ADDR       = 0x53000000,

	IIC_CTL_BASE_ADDR         = 0x54000000,

	IIS_CTL_BASE_ADDR         = 0x55000000,

	GPIO_CTL_BASE_ADDR        = 0x56000000,

	

} S3C2440_BASE_ADDR_e;

static inline S3C2440_MEM_CTL_t * const S3C2440_GetMemCtlBaseAddr(void)
{
	return (S3C2440_MEM_CTL_t * const)MEM_CTL_BASE_ADDR;
}

static inline S3C2440_NAND_CTL_t * const S3C2440_GetNandCtlBaseAddr(void)
{
	return (S3C2440_NAND_CTL_t * const)NAND_CTL_BASE_ADDR;
}

static inline S3C2330_CLOCK_POWER_CTL_t * const S3C2440_GetClockPowerCtlBaseAddr(void)
{
	return (S3C2330_CLOCK_POWER_CTL_t * const)CLOCK_POWER_CTL_BASE_ADDR;
}

static inline S3C2440_GPIO_CTL_t * const S3C2440_GetGPIOCtlBaseAddr(void)
{
	return (S3C2440_GPIO_CTL_t * const)GPIO_CTL_BASE_ADDR;
}

static inline S3C2440_UART_CTL_t * const S3C2440_GetUARTCtlBaseAddr(S3C2440_UARTn_e UARTn)
{
	return (S3C2440_UART_CTL_t * const)UART_CTL_BASE_ADDR + 0x4000 * UARTn;
}

#endif
