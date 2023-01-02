#ifndef _S3C2440_H
#define _S3C2440_H

#define __REG(x) (*(volatile unsigned int *)(x))

#define GPFCON __REG(0x56000050)
#define GPFDAT __REG(0x56000054)
#define GPFUP  __REG(0x56000058)

#endif