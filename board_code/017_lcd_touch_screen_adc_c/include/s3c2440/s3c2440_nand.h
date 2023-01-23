#ifndef __S3C2440_NAND_H
#define __S3C2440_NAND_H

typedef enum
{
	TACLS_0 = 0 << 12,
	TACLS_1 = 1 << 12,
	TACLS_2 = 2 << 12,
	TACLS_3 = 3 << 12,
} NAND_TACLS_e;

typedef enum
{
	TWRPH0_0 = 0 << 8,
	TWRPH0_1 = 1 << 8,
	TWRPH0_2 = 2 << 8,
	TWRPH0_3 = 3 << 8,
	TWRPH0_4 = 4 << 8,
	TWRPH0_5 = 5 << 8,
	TWRPH0_6 = 6 << 8,
	TWRPH0_7 = 7 << 8,
} NAND_TWRPH0_e;

typedef enum
{
	TWRPH1_0 = 0 << 4,
	TWRPH1_1 = 1 << 4,
	TWRPH1_2 = 2 << 4,
	TWRPH1_3 = 3 << 4,
	TWRPH1_4 = 4 << 4,
	TWRPH1_5 = 5 << 4,
	TWRPH1_6 = 6 << 4,
	TWRPH1_7 = 7 << 4,
} NAND_TWRPH1_e;

typedef enum
{
	BUS_WIDTH_8bit  = 0 << 0,
	BUS_WIDTH_16bit = 1 << 0,
} NAND_BusWidth_e;

#define SET_NFCONF(TACLS, TWRPH0, TWRPH1, BusWidth) (TACLS | TWRPH0 | TWRPH1 | BusWidth)

typedef enum
{
	LockTight_Disable = 0 << 13,
	LockTight_Enable  = 1 << 13,
} NAND_LockTight_e;

/* soft lock configuration */
typedef enum
{
	SoftLock_Disable = 0 << 12,
	SoftLock_Enable  = 1 << 12,
} NAND_SoftLock_e;

/* lllegal access interrupt control */
typedef enum
{
	Lllegal_Access_Int_Disable = 0 << 10,
	Lllegal_Access_Int_Enable  = 1 << 10,
} NAND_EnblllegalAccINT_e;

/* RnB status input signal transition interrupt control */
typedef enum
{
	EnbRnBINT_Disable = 0 << 9,
	EnbRnBINT_Enable  = 1 << 9,
} NAND_EnbRnBINT_e;

/* RnB transition detection configuration */
typedef enum
{
	TransMode_Detect_Rising_Edge  = 0 << 8,
	TransMode_Detect_Falling_Edge = 1 << 8,
} NAND_RnB_TransMode_e;

/* lock spare area ECC generation */
typedef enum
{
	Spare_ECC_Unlock = 0 << 6,
	Spare_ECC_Lock   = 1 << 6,
} NAND_SpareECCLock_e;

/* lock main data area ECC generation */
typedef enum
{
	Main_ECC_Unlock = 0 << 5,
	Main_ECC_Lock   = 1 << 5,
} NAND_MainECCLock_e;

/* initialize ECC decoder/emcoder */
typedef enum
{
	Init_ECC_Disable = 0 << 4,
	Init_ECC_Enable  = 1 << 4,
} NAND_InitECC_e;

/* nFCE signal control */
typedef enum
{
	nFCE_Chip_Enable  = 0 << 1,
	nFCE_Chip_Disable = 1 << 1,
} NAND_Reg_nCE_e;

/* NAND flash controller operating mode */
typedef enum
{
	NAND_Disable = 0 << 0,
	NAND_Enable  = 1 << 0,
} NAND_MODE_e;

#define SET_NFCONT(locktight, softlock, lllegalAccInt, EnbRnBINT, RnBTransMode, spareECCLock, MainECCLock, InitECC, RegnCE, mode) \
	(locktight | softlock | lllegalAccInt | EnbRnBINT | RnBTransMode | spareECCLock | MainECCLock | InitECC | RegnCE | mode)


/* NAND flash operation status register */
#define isDetectIllegalAccess(val) ((val & (1 << 3)) ? 1: 0)
#define isDetectRnBTransition(val) ((val & (1 << 2)) ? 1: 0)
#define isnCEStatus(val) ((val & (1 << 1)) ? 1: 0)
/* 1表示NAND忙，0表示NAND空闲 */
#define isRnBBusy(val) ((val & (1 << 0)) ? 0: 1)

#endif

