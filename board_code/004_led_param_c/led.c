

void delay(unsigned int t)
{
	while (t--);
}

int led_on(int which)
{
	unsigned int *pGPFCON = (unsigned int *)0x56000050;
	unsigned int *pGPFDAT = (unsigned int *)0x56000054;

	if (4 == which)
	{
		/* 设置GPF4为输出引脚 */
		*pGPFCON = 0x100;
	}
	else if (5 == which)
	{
		/* 设置GPF5为输出引脚 */
		*pGPFCON = 0x400;
	}

	/* 设置GPF4/5为低电平 */
	*pGPFDAT = 0;

	return 0;
}