#include "uart.h"
#include "sdram.h"
#include "nand.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
	UART_Init();

	while (1);

	return 0;
}


