#ifndef __S3C2440_MEM_H
#define __S3C2440_MEM_H

typedef enum
{
	UBLB_DISABLE = 0,
	UBLB_ENABLE  = 1,
} MEM_UBLB_e;

typedef enum
{
	WAIT_DISABLE = 0,
	WAIT_ENABLE  = 1,
} MEM_WAIT_e;

typedef enum
{
	BUS_WIDTH_8bit  = 0,
	BUS_WIDTH_16bit = 1,
	BUS_WIDTH_32bit = 2,
	BUS_WIDTH_RES   = 3,
} MEM_BUS_WIDTH_e;

#define SET_BWSCON(n, ublb, wait, buswidth) (((ublb << 3) | (wait << 2) | (buswidth << 0)) << (4 * n))


/* Address set-up time before nGCSn */
typedef enum
{
	Tacs_0clock = 0 << 13,
	Tacs_1clock = 1 << 13,
	Tacs_2clock = 2 << 13,
	Tacs_4clock = 3 << 13,
} MEM_Tacs_e;

/* Chip selection set-up time before nOE */
typedef enum
{
	Tcos_0clock = 0 << 11,
	Tcos_1clock = 1 << 11,
	Tcos_2clock = 2 << 11,
	Tcos_4clock = 3 << 11,
} MEM_Tcos_e;

/* Access cycle */
typedef enum
{
	Tacc_1clock  = 0 << 8,
	Tacc_2clock  = 1 << 8,
	Tacc_3clock  = 2 << 8,
	Tacc_4clock  = 3 << 8,
	Tacc_6clock  = 4 << 8,
	Tacc_8clock  = 5 << 8,
	Tacc_10clock = 6 << 8,
	Tacc_14clock = 7 << 8,
} MEM_Tacc_e;

/* Chip selection hold time after nOE */
typedef enum
{
	Tcoh_0clock = 0 << 6,
	Tcoh_1clock = 1 << 6,
	Tcoh_2clock = 2 << 6,
	Tcoh_4clock = 3 << 6,
} MEM_Tcoh_e;

/* Address hold time after nGCSn */
typedef enum
{
	Tcah_0clock = 0 << 4,
	Tcah_1clock = 1 << 4,
	Tcah_2clock = 2 << 4,
	Tcah_4clock = 3 << 4,
} MEM_Tcah_e;

/* Page mode access cycle @Page mode */
typedef enum
{
	Tacp_2clock = 0 << 2,
	Tacp_3clock = 1 << 2,
	Tacp_4clock = 2 << 2,
	Tacp_6clock = 3 << 2,
} MEM_Tacp_e;

/* Page mode configuration */
typedef enum
{
	Page_Mode_1data  = 0,
	Page_Mode_4data  = 1,
	Page_Mode_8data  = 2,
	Page_Mode_16data = 3,
} MEM_PMC_e;

/* Determine the memory type for bank6 and bank7 */
typedef enum
{
	MT_ROM_SRAM = 0 << 15,
	MT_SDRAM    = 3 << 15,
	MT_NOT_USE  = 1 << 15,
} MEM_MT_e;

/* RAS to CAS delay */
typedef enum
{
	Trcd_2clock = 0 << 2,
	Trcd_3clock = 1 << 2,
	Trcd_4clock = 2 << 2,
} MEM_Trcd_e;

/* Column address number */
typedef enum
{
	SCAN_8bit  = 0 << 0,
	SCAN_9bit  = 1 << 0,
	SCAN_10bit = 2 << 0,
} MEM_SCAN_e;

#define SET_BANKCONn(MT, Tacs, Tcos, Tacc, Tcoh, Tcah, Tacp, PMC) (MT | Tacs | Tcos | Tacc | Tcoh | Tcah | Tacp | PMC)
#define SET_BANKCON_SDRAM(MT, Trcd, SCAN) (MT | Trcd | SCAN)

/* SDRAM Refresh Enable */
typedef enum
{
	Refresh_Disable = 0 << 23,
	Refresh_Enable  = 1 << 23,
} MEM_REFEN_e;

/* SDRAM Refresh Mode */
typedef enum
{
	Refresh_mode_CBR_Auto = 0 << 22,
	Refresh_mode_Self     = 1 << 22,
} MEM_TREFMD_e;

/* SDRAM RAS pre-change Time */
typedef enum
{
	Trp_2clock = 0 << 20,
	Trp_3clock = 1 << 20,
	Trp_4clock = 2 << 20,
} MEM_Trp_e;

/* SDRAM Semi Row cycle time */
typedef enum
{
	Tsrc_4clock = 0 << 18,
	Tsrc_5clock = 1 << 18,
	Tsrc_6clock = 2 << 18,
	Tsrc_7clock = 3 << 18,
} MEM_Tsrc_e;

#define SET_REFRESH(enable, mode, Trp, Tsrc, counter) (enable | mode | Trp | Tsrc | counter)

/* ARM core burst operation enable */
typedef enum
{
	BURST_DISABLE = 0 << 7,
	BURST_ENABLE  = 1 << 7,
} MEM_BURST_EN_e;

/* SDRAM power down mode enable control by SCKE */
typedef enum
{
	POWER_DOWN_DISABLE = 0 << 5,
	POWER_DOWN_ENABLE  = 1 << 5,
} MEM_SCKE_EN_e;

/* SCLK is enabled only during SDRAM access cycle for reducing power consumption */
typedef enum
{
	SCLK_Always_Active = 0 << 4,
	SCLK_Access_Active = 1 << 4,
} MEM_SCLK_EN_e;

/* BANK6/7 memory map */
typedef enum
{
	BK76MAP_128MB = 2 << 0,
	BK76MAP_64MB  = 1 << 0,
	BK76MAP_32MB  = 0 << 0,
	BK76MAP_16MB  = 7 << 0,
	BK76MAP_8MB   = 6 << 0,
	BK76MAP_4MB   = 5 << 0,
	BK76MAP_2MB   = 4 << 0,
} MEM_BK76MAP_e;

#define SET_BANKSIZE(burst, scke, sclk, bk76map) (burst | scke | sclk | bk76map)

/* CAS latency */
typedef enum
{
	CAS_Latency_1clock = 0 << 4,
	CAS_Latency_2clock = 2 << 4,
	CAS_Latency_3clock = 3 << 4,
} MEM_CL_e;

#define SET_MRSRB(cl) (cl)

#endif
