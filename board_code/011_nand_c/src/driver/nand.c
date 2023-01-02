#include "s3c2440.h"
#include "s3c2440_nand.h"
#include "types.h"

/* 读操作命令 */
typedef enum
{
	ReadDataFirstCycleCmd  = 0x00,
	ReadDataSecondCycleCmd = 0x30,
} NAND_ReadDataCmd_e;

/* 读ID命令 */
typedef enum
{
	ReadIDFirstCylceCmd = 0x90,
} NAND_ReadIDCmd_e;

/* 复位命令 */
typedef enum
{
	ResetCmd = 0xFF,
} NAND_ResetCmd_e;

/* 写页命令 */
typedef enum
{
	PageProgramFirstCycleCmd  = 0x80,
	PageProgramSecondCycleCmd = 0x10,
} NAND_PageProgramCmd_e;

/* 块擦除命令 */
typedef enum
{
	EraseBlockFirstCycleCmd  = 0x60,
	EraseBlockSecondCycleCmd = 0xD0,
} NAND_EraseBlockCmd_e;

/* 读状态命令 */
typedef enum
{
	ReadStatusFirstCycleCmd = 0x70,
} NAND_ReadStatusCmd_e;

/* 读状态2命令 */
typedef enum
{
	ReadStatus2FirstCycleCmd = 0xF1,
} NAND_ReadStatus2Cmd_e;


/*******************************************************************************
 * 函数名称: NAND_delay
 * 功能描述: 延迟一定时间，不准确
 * 输入参数: t 延时时间
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_delay(int t)
{
	int i = 0;

	for (i = 0; i < t; i++);
}

/*******************************************************************************
 * 函数名称: NAND_enableChip
 * 功能描述: 使能NAND片选
 * 输入参数: 无
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_enableChip(void)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();
	unsigned int status = 0;

	status = pNAND->NFCONT;
	pNAND->NFCONT = status & ~(1 << 1);
}

/*******************************************************************************
 * 函数名称: NAND_disableChip
 * 功能描述: 关闭NAND片选
 * 输入参数: 无
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_disableChip(void)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();
	unsigned int status = 0;

	status = pNAND->NFCONT;
	pNAND->NFCONT = status | (1 << 1);
}

/*******************************************************************************
 * 函数名称: NAND_writeCmd
 * 功能描述: 向NAND发送命令
 * 输入参数: cmd 命令
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_writeCmd(unsigned char cmd)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();

	pNAND->NFCMMD = cmd;
	NAND_delay(10);
}

/*******************************************************************************
 * 函数名称: NAND_writeAddr
 * 功能描述: 向NAND发送地址
 * 输入参数: addr 地址
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_writeAddr(unsigned char addr)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();

	pNAND->NFADDR = addr;
	NAND_delay(10);
}

/*******************************************************************************
 * 函数名称: NAND_writeByte
 * 功能描述: 向NAND写入数据
 * 输入参数: data 数据
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_writeByte(unsigned char data)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();

	pNAND->NFDATA = data;
	NAND_delay(10);
}

/*******************************************************************************
 * 函数名称: NAND_readByte
 * 功能描述: 从NAND读出1字节数据
 * 输入参数: 无
 * 输出参数: pBuf 读出的1字节数据
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
static void NAND_readByte(unsigned char *pBuf)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();

	if (NULL == pBuf)
	{
		return;
	}

	*pBuf = *((unsigned char *)(&pNAND->NFDATA));

	return ;
}

/*******************************************************************************
 * 函数名称: NAND_waitReady
 * 功能描述: 等待NAND准备好
 * 输入参数: 无
 * 输出参数: 无
 * 返回的值: 无
*******************************************************************************/
static void NAND_waitReady(void)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();

	while ((1 == isRnBBusy(pNAND->NFSTAT)));
}

/*******************************************************************************
 * 函数名称: NAND_readStatus1
 * 功能描述: 读取NAND的状态寄存器1的数据
 * 输入参数: pBuf 用户存储状态寄存器1信息的缓存
 * 输出参数: pBuf NAND的状态寄存器1信息
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
static int NAND_readStatus1(unsigned char *pBuf)
{

	if (NULL == pBuf)
	{
		return -1;
	}

	/* 开启片选 */
	NAND_enableChip();

	/* 发送读状态寄存器1的命令0x70 */
	NAND_writeCmd(ReadStatusFirstCycleCmd);

	/* 读取状态寄存器1的值 */
	NAND_readByte(pBuf);

	/* 关闭片选 */
	NAND_disableChip();

	return 0;
}

/*******************************************************************************
 * 函数名称: NAND_readStatus2
 * 功能描述: 读取NAND的状态寄存器2的数据
 * 输入参数: pBuf 用户存储状态寄存器2信息的缓存
 * 输出参数: pBuf NAND的状态寄存器2信息
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
#if 0
static int NAND_readStatus2(unsigned char *pBuf)
{

	if (NULL == pBuf)
	{
		return -1;
	}

	/* 开启片选 */
	NAND_enableChip();

	/* 发送读状态寄存器2的命令0xF1 */
	NAND_writeCmd(ReadStatus2FirstCycleCmd);

	/* 读取状态寄存器1的值 */
	NAND_readByte(pBuf);

	/* 关闭片选 */
	NAND_disableChip();

	return 0;
}
#endif
/*******************************************************************************
 * 函数名称: NAND_readID
 * 功能描述: 读取NAND的ID信息
 * 输入参数: pBuf 用户存储ID信息的缓存
 *          size pBuf缓存大小，单位字节
 * 输出参数: pBuf NAND的ID信息
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
#if 0
int NAND_readID(unsigned char *pBuf, int size)
{
	int i = 0;

	if (NULL == pBuf || 5 > size)
	{
		return -1;
	}

	NAND_enableChip();

	/* 发送0x90 */
	NAND_writeCmd(ReadIDFirstCylceCmd);

	/* 发送地址0x00 */
	NAND_writeAddr(0x00);

	/* 读取5个字节数据 */
	for (i = 0; i < 5; i++)
	{
		NAND_readByte(&pBuf[i]);
	}

	NAND_disableChip();

	return 0;
}
#endif
/*******************************************************************************
 * 函数名称: NAND_readData
 * 功能描述: 读取NAND的main区域数据，不包括OOB区域数据
 * 输入参数: startAddr 起始地址
 *          pBuf 用户存储数据的缓存
 *          size pBuf的大小，单位字节
 * 输出参数: pBuf 读取的数据
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
int NAND_readData(unsigned int startAddr, unsigned char *pBuf, int size)
{
	unsigned int colAddr = 0;
	unsigned int rowAddr = 0;
	int len = 0;

	if (NULL == pBuf)
	{
		return -1;
	}

	NAND_enableChip();

	for (len = 0; len < size; len++)
	{
		/* 发送0x00 */
		NAND_writeCmd(ReadDataFirstCycleCmd);

		colAddr = (startAddr + len) % 2048;
		rowAddr = (startAddr + len) >> 11;

		/* 发送col1、col2、row1、row2、row3 */
		NAND_writeAddr(colAddr & 0xFF);
		NAND_writeAddr((colAddr >> 8) & 0xFF);
		NAND_writeAddr(rowAddr & 0xFF);
		NAND_writeAddr((rowAddr >> 8) & 0xFF);
		NAND_writeAddr((rowAddr >> 16) & 0xFF);

		/* 发送0x30 */
		NAND_writeCmd(ReadDataSecondCycleCmd);

		/* 等待数据准备好 */
		NAND_waitReady();

		NAND_readByte(&pBuf[len]);
	}

	NAND_disableChip();

	return len;
}

/*******************************************************************************
 * 函数名称: NAND_readDataWithOOB
 * 功能描述: 读取NAND的main区域+OOB区域的数据
 * 输入参数: startAddr 起始地址
 *          pBuf 用户存储数据的缓存
 *          size pBuf的大小，单位字节
 * 输出参数: pBuf 读取的数据
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
#if 0
int NAND_readDataWithOOB(unsigned int startAddr, unsigned char *pBuf, int size)
{
	unsigned int colAddr = 0;
	unsigned int rowAddr = 0;
	int len = 0;

	if (NULL == pBuf)
	{
		return -1;
	}

	NAND_enableChip();

	for (len = 0; len < size; len++)
	{
		/* 发送0x00 */
		NAND_writeCmd(ReadDataFirstCycleCmd);

		colAddr = (startAddr + len) % (2048 + 64);
		rowAddr = (startAddr + len) / (2048 + 64);

		/* 发送col1、col2、row1、row2、row3 */
		NAND_writeAddr(colAddr & 0xFF);
		NAND_writeAddr((colAddr >> 8) & 0xFF);
		NAND_writeAddr(rowAddr & 0xFF);
		NAND_writeAddr((rowAddr >> 8) & 0xFF);
		NAND_writeAddr((rowAddr >> 16) & 0xFF);

		/* 发送0x30 */
		NAND_writeCmd(ReadDataSecondCycleCmd);

		/* 等待数据准备好 */
		NAND_waitReady();

		NAND_readByte(&pBuf[len]);
	}

	NAND_disableChip();

	return len;
}
#endif

/*******************************************************************************
 * 函数名称: NAND_writePage
 * 功能描述: 向指定地址所在的页写入数据，会从该页的起始位置开始写数据，最多可写入2048个字节数据
 * 输入参数: startAddr 起始地址
 *          pBuf 用户写入页的数据缓存
 *          size 需要写入的数据的大小，单位字节，最多可写入2048个字节数据
 * 输出参数: 无
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
int NAND_writePage(unsigned int startAddr, unsigned char *pBuf, int size)
{
	unsigned char status  = 0;
	unsigned int  colAddr = 0;
	unsigned int  rowAddr = 0;
	int           i       = 0;

	colAddr = 0;
	rowAddr = startAddr / 2048;

	NAND_enableChip();

	/* 发送命令0x80 */
	NAND_writeCmd(PageProgramFirstCycleCmd);

	/* 写列地址 */
	NAND_writeAddr(colAddr & 0xFF);
	NAND_writeAddr((colAddr >> 8) & 0xFF);

	/* 写行地址 */
	NAND_writeAddr(rowAddr & 0xFF);
	NAND_writeAddr((rowAddr >> 8) & 0xFF);
	NAND_writeAddr((rowAddr >> 16) & 0xFF);

	/* 写数据 */
	for (i = 0; i < size && i < 2048; i++)
	{
		NAND_writeByte(pBuf[i]);
	}

	/* 发送命令0x10 */
	NAND_writeCmd(PageProgramSecondCycleCmd);

	/* 等待设备准备好 */
	NAND_waitReady();

	/* 读状态寄存器1 */
	NAND_readStatus1(&status);

	NAND_disableChip();

	if (-1 == (status & 0x01))
	{
		return -1;
	}

	return 0;
}

/*******************************************************************************
 * 函数名称: NAND_eraseBlock
 * 功能描述: 擦除指定地址所在的block
 * 输入参数: startAddr 起始地址
 * 输出参数: 无
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
int NAND_eraseBlock(unsigned int startAddr)
{
	unsigned char status = 0;

	unsigned int rowAddr = 0;

	rowAddr = startAddr / 2048;

	NAND_enableChip();

	NAND_writeCmd(EraseBlockFirstCycleCmd);

	NAND_writeAddr(rowAddr & 0xC0);
	NAND_writeAddr((rowAddr >> 8) & 0xFF);
	NAND_writeAddr((rowAddr >> 16) & 0xFF);

	NAND_writeCmd(EraseBlockSecondCycleCmd);

	NAND_waitReady();

	NAND_readStatus1(&status);

	NAND_disableChip();

	if (-1 == (status & 0x01))
	{
		return -1;
	}

	return 0;
}

/*******************************************************************************
 * 函数名称: NAND_Init
 * 功能描述: 初始化NAND相关寄存器
 * 输入参数: 无
 * 输出参数: 无
 * 返回的值: 0 成功； -1 失败
*******************************************************************************/
int NAND_Init(void)
{
	S3C2440_NAND_CTL_t * const pNAND = S3C2440_GetNandCtlBaseAddr();

	pNAND->NFCONF = SET_NFCONF(TACLS_0, TWRPH0_1, TWRPH1_0, BUS_WIDTH_8bit);

	pNAND->NFCONT = SET_NFCONT(LockTight_Disable, \
								SoftLock_Disable, \
								Lllegal_Access_Int_Disable,\
								EnbRnBINT_Disable,\
								TransMode_Detect_Rising_Edge,\
								Spare_ECC_Unlock,\
								Main_ECC_Unlock,\
								Init_ECC_Enable,\
								nFCE_Chip_Disable,\
								NAND_Enable);/* 开启NAND控制器 */

	return 0;
}

