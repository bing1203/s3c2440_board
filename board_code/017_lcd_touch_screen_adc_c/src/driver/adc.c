#include "s3c2440.h"



void ADC_Init(void)
{
    S3C2440_ADC_CTL_t *pADC = S3C2440_GetADCCtlBaseAddr();

    pADC->ADCCON = (1 << 14) | /* A/D converter prescaler enable */
                   (49 << 6) | /* A/D converter prescaler value */
                   (7 << 3) |  /* Analog input channel select */
                   (0 << 2) |  /* standby mode select */
                   (0 << 1) |  /* A/D conversion start by read */
                   (0 << 0);   /* A/D conversion starts by enable */

    pADC->ADCDLY = 0xFF;
}

unsigned short ADC_readDataY(void)
{
    S3C2440_ADC_CTL_t *pADC = S3C2440_GetADCCtlBaseAddr();

    pADC->ADCCON = (1 << 14) | /* A/D converter prescaler enable */
                   (49 << 6) | /* A/D converter prescaler value */
                   (7 << 3) |  /* Analog input channel select */
                   (0 << 2) |  /* standby mode select */
                   (0 << 1) |  /* A/D conversion start by read */
                   (1 << 0);   /* A/D conversion starts by enable */

    pADC->ADCTSC = (0 << 6) | 
                   (0 << 4) | 
                   (0 << 3) | 
                   (1 << 0);

    while (0 == (pADC->ADCCON & (1 << 15)));

    return pADC->ADCDAT0 & 0x3FF;
}

unsigned short ADC_readDataX(void)
{
    S3C2440_ADC_CTL_t *pADC = S3C2440_GetADCCtlBaseAddr();

    pADC->ADCCON = (1 << 14) | /* A/D converter prescaler enable */
                   (49 << 6) | /* A/D converter prescaler value */
                   (5 << 3) |  /* Analog input channel select */
                   (0 << 2) |  /* standby mode select */
                   (0 << 1) |  /* A/D conversion start by read */
                   (1 << 0);   /* A/D conversion starts by enable */

    pADC->ADCTSC = (0 << 6) | 
                   (0 << 4) | 
                   (0 << 3) | 
                   (2 << 0);

    while (0 == (pADC->ADCCON & (1 << 15)));

    return pADC->ADCDAT1 & 0x3FF;
}