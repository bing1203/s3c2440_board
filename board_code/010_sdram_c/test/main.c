#include "uart.h"
#include "sdram.h"
#include "stdio.h"

static void UART_Test()
{
	UART_Init();

	printf("This is test\n\r");

	printf("[%s | %d] This is test\n\r", __func__, __LINE__);

	printf("oct test:%o %o %o %o\r\n", 033, 067, 999, 888);

	printf("hex test:0x%x 0x%x\r\n", 0xF2345678, 1111111);

	printf("dia test:%d %d\r\n", -100, 9087);

	printf("add test:0x%p\r\n", UART_Test);
}

static void SDRAM_Test()
{
	volatile unsigned int *p = (volatile unsigned int *)0x30000000;

	printf("%s|%d\r\n", __func__, __LINE__);

	*p = 0x12345678;

	printf("addr[0x30000000]:0x%x\r\n", *p);

	printf("%s|%d\r\n", __func__, __LINE__);
}

int main(int argc, char *argv[])
{
	UART_Test();
	SDRAM_Test();

	return 0;
}


