#ifndef __NAND_H
#define __NAND_H

int NAND_readID(unsigned char *pBuf, int size);
int NAND_readData(unsigned int startAddr, unsigned char *pBuf, int size);
int NAND_readDataWithOOB(unsigned int startAddr, unsigned char *pBuf, int size);
int NAND_writePage(unsigned int startAddr, unsigned char *pBuf, int size);
int NAND_eraseBlock(unsigned int startAddr);
int NAND_Init(void);

#endif
