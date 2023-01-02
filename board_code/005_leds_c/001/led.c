

void delay(unsigned int t)
{
	while (t--);
}

int main(int argc, char *argv[])
{
	unsigned int *pGPFCON = (unsigned int *)0x56000050;
	unsigned int *pGPFDAT = (unsigned int *)0x56000054;
	int val = 0;
	int tmp = 0;

	/* 设置GPF4、GPF5、GPF6为输出引脚 */
	*pGPFCON &= ~((3<<8) | (3<<10) | (3<<12));
	*pGPFCON |= ((1<<8) | (1<<10) | (1<<12));

	/* 循环点亮LED */
	while (1)
	{
		tmp = ~val;
		tmp &= 7;
		*pGPFDAT &= ~(7<<4);
		*pGPFDAT |= (tmp << 4);
		delay(100000);
		val++;
		if (8 == val)
		{
			val = 0;
		}
	}

	return 0;
}