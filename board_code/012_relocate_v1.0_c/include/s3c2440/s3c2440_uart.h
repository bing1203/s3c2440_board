#ifndef __S3C2440_UART_H
#define __S3C2440_UART_H

#include "s3c2440_soc.h"

typedef enum
{
	IrMode_Normal   = 0 << 6, // 普通模式，不支持红外收发
	IrMode_Infrared = 1 << 6, // 红外收发模式
} UART_ULCONn_IrMode_e;

typedef enum
{
	ParityMode_None       = 0 << 3, // 无奇偶校验位
	ParityMode_Odd        = 4 << 3, // 奇校验
	ParityMode_Even       = 5 << 3, // 偶校验
	ParityMode_Force_One  = 6 << 3, // 该位强制为1
	ParityMode_Force_Zero = 7 << 3, // 该位强制为0
} UART_ULCONn_ParityMode_e;

typedef enum
{
	StopBit_One       = 0 << 2, // 1位停止位
	StopBit_Two       = 1 << 2, // 2位停止位
} UART_ULCONn_StopBit_e;

typedef enum
{
	WrodLength_5bits       = 0 << 0, // 5位数据位
	WrodLength_6bits       = 1 << 0, // 6位数据位
	WrodLength_7bits       = 2 << 0, // 7位数据位
	WrodLength_8bits       = 3 << 0, // 8位数据位
} UART_ULCONn_WrodLength_e;



#endif
