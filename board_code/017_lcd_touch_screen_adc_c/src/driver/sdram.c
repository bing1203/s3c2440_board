#include "s3c2440.h"
#include "s3c2440_mem.h"

int MEM_Init(void)
{
	S3C2440_MEM_CTL_t * const pMEM = S3C2440_GetMemCtlBaseAddr();

	pMEM->BWSCON      = SET_BWSCON(6, UBLB_DISABLE, WAIT_DISABLE, BUS_WIDTH_32bit) | 
						SET_BWSCON(7, UBLB_DISABLE, WAIT_DISABLE, BUS_WIDTH_32bit);
	pMEM->BANKCONn[6] = SET_BANKCON_SDRAM(MT_SDRAM, Trcd_2clock, SCAN_9bit);
	pMEM->BANKCONn[7] = SET_BANKCON_SDRAM(MT_SDRAM, Trcd_2clock, SCAN_9bit);
	pMEM->BANKSIZE    = SET_BANKSIZE(BURST_ENABLE, POWER_DOWN_ENABLE, SCLK_Access_Active, BK76MAP_64MB);
	pMEM->MRSRB6      = SET_MRSRB(CAS_Latency_2clock);
	pMEM->MRSRB7      = SET_MRSRB(CAS_Latency_2clock);
	pMEM->REFRESH     = SET_REFRESH(Refresh_Enable, Refresh_mode_CBR_Auto, Trp_2clock, Tsrc_5clock, 1269);

	return 0;
}

