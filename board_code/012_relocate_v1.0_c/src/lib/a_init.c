#include "sdram.h"
#include "nand.h"


extern unsigned int __text_start;
extern unsigned int __bss_start;
extern unsigned int __bss_end;

void relocate()
{
	unsigned char *pMemAddr = (unsigned char *)0x30000000;
	int totalSize = 8192;//__bss_start - __text_start;

	NAND_readData(0, pMemAddr, totalSize);

}

void init(void)
{
	MEM_Init();
	NAND_Init();
	relocate();
}

