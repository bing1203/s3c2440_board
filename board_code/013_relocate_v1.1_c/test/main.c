#include "uart.h"
#include "sdram.h"
#include "nand.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
	UART_Init();

	printf("\033[00;31mhello, world!!!\r\n\033[0m");

	while (1);

	return 0;
}


