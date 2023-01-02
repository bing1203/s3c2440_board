#include "s3c2440.h"
#include "s3c2440_uart.h"

int UART_Init()
{
	S3C2440_GPIO_CTL_t * const pGPIO = S3C2440_GetGPIOCtlBaseAddr();
	S3C2440_UART_CTL_t * const pUART = S3C2440_GetUARTCtlBaseAddr(S3C2440_UART0);

	/* TXD0——GPH2
	   GPHCON[5:4] = 0b10 TXD
	 */
	pGPIO->GPHCON &= ~(1 << 4);
	pGPIO->GPHCON |=  (1 << 5);

	/* RXD0——GPH3
	   GPHCON[7:6] = 0b10 RXD
	*/
	pGPIO->GPHCON &= ~(1 << 6);
	pGPIO->GPHCON |=  (1 << 7);

	/* 设置串口0的ULCON寄存器 */
	pUART->ULCON = IrMode_Normal   | /* 普通模式，非红外收发模式 */
				   ParityMode_None | /* 无奇偶校验 */
				   StopBit_One     | /* 1位停止位 */
				   WrodLength_8bits; /* 8位数据位 */

	/* 设置串口0的UBRDIV */
	/* 
		波特率：115200
		时钟频率：PCLK=50MHz
		计算出UBRDIV=(50000000 / (115200 * 16)) - 1 = 26
	 */
	pUART->UBRDIV = 26;

	/* 设置串口0的UCON */
	pUART->UCON = (1 << 0) | /* 开启接收功能 */
				  (1 << 2) | /* 开启发送功能 */
				  (0 << 4) | /* 不发送break信号 */
				  (0 << 5) | /* 关闭回环模式 */
				  (0 << 6) | /* 接收出现错误时不产生中断 */
				  (0 << 7) | /* 关闭接收超时中断 */
				  (1 << 8) | /* 接收中断类型 电平 */
				  (1 << 9) | /* 发送中断类型 电平 */
				  (0 << 10) | /* 时钟选择 PCLK */
				  (0 << 12);  /* 仅在选择FCLK/n时有效 */

	/* 设置串口0的UFCON */
	pUART->UFCON = (0 << 0) | /* 关闭FIFO功能 */
				   (0 << 1) | 
				   (0 << 2) | 
				   (0 << 4) | 
				   (0 << 6);
	return 0;
}

int putchar(int ch)
{
	S3C2440_UART_CTL_t * const pUART = S3C2440_GetUARTCtlBaseAddr(S3C2440_UART0);

	/* 等待发送buffer为空 */
	while (0 == (pUART->UTRSTAT0 & 0x2));

	pUART->UTXH = ch;

	return 0;
}

int getchar(void)
{
	S3C2440_UART_CTL_t * const pUART = S3C2440_GetUARTCtlBaseAddr(S3C2440_UART0);

	/* 等待接收buffer有数据 */
	while (0 == (pUART->UTRSTAT0 & 0x1));

	return pUART->URXH & 0xFF;
}



