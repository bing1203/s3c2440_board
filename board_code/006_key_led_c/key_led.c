#include "s3c2440.h"

void delay(unsigned int t)
{
	while (t--);
}

int main(int argc, char *argv[])
{
	int val1, val2;

	/* 设置GPF4、GPF5、GPF6为输出引脚 */
	GPFCON &= ~((3<<8) | (3<<10) | (3<<12));
	GPFCON |= ((1<<8) | (1<<10) | (1<<12));

	/* 配置3个按键引脚为输入引脚 */
	GPFCON &= ~((3<<0) | (3<<4));
	GPGCON &= ~((3<<6));

	/* 循环点亮LED */
	while (1)
	{
		val1 = GPFDAT;
		val2 = GPGDAT;
		
		if (val1 & (1<<0))
		{
			GPFDAT |= 1 << 6;
		}
		else
		{
			GPFDAT &= ~(1<<6);
		}

		if (val1 & (1<<2))
		{
			GPFDAT |= 1 << 5;
		}
		else
		{
			GPFDAT &= ~(1<<5);
		}

		if (val2 & (1<<3))
		{
			GPFDAT |= 1 << 4;
		}
		else
		{
			GPFDAT &= ~(1<<4);
		}
	}

	return 0;
}