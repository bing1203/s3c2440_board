#include "uart.h"
#include "sdram.h"
#include "nand.h"
#include "stdio.h"

static void NAND_Test()
{
	unsigned char buf[5];
	int len = 0;
	NAND_Init();

	len = NAND_readData(0, buf, 5);
	printf("%x %x %x %x %x\r\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
}

int main(int argc, char *argv[])
{
	UART_Init();
	NAND_Test();

	return 0;
}


