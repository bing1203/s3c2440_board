#include "sdram.h"
#include "nand.h"
#include "stdio.h"
#include "uart.h"


extern unsigned int __text_start;
extern unsigned int __bss_start;
extern unsigned int __bss_end;

void relocate()
{
	unsigned char *pMemAddr = (unsigned char *)&__text_start;
	int totalSize = (unsigned int)&__bss_start - (unsigned int)&__text_start;

	NAND_readData(0, pMemAddr, totalSize);

}

void clearBss()
{
	unsigned int *pStartAddr = (unsigned int *)&__bss_start;
	unsigned int *pStartEnd  = (unsigned int *)&__bss_end;

	while (pStartAddr < pStartEnd)
	{
		*pStartAddr = 0x00000000;
		pStartAddr++;
	}
}

void init(void)
{
	MEM_Init();
	NAND_Init();
	relocate();
	clearBss();
}

