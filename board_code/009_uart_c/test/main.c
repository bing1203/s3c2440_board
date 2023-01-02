#include "uart.h"
#include "stdio.h"

static void UART_Test()
{
	UART_Init();

	printf("This is test\n\r");

	printf("[%s | %d] This is test\n\r", __func__, __LINE__);

	printf("oct test:%o %o %o %o\r\n", 033, 067, 999, 888);

	printf("hex test:0x%x 0x%x\r\n", 0x12345678, 1111111);

	printf("dia test:%d %d\r\n", -100, 9087);

	printf("add test:0x%p\r\n", UART_Test);
}

int main(int argc, char *argv[])
{
	UART_Test();

	return 0;
}