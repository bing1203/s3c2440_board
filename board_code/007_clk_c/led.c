#include "s3c2440.h"

void delay(unsigned int t)
{
	while (t--);
}

int main(int argc, char *argv[])
{
	int val = 0;
	int tmp = 0;

	/* 设置GPF4、GPF5、GPF6为输出引脚 */
	GPFCON &= ~((3<<8) | (3<<10) | (3<<12));
	GPFCON |= ((1<<8) | (1<<10) | (1<<12));

	/* 循环点亮LED */
	while (1)
	{
		tmp = ~val;
		tmp &= 7;
		GPFDAT &= ~(7<<4);
		GPFDAT |= (tmp << 4);
		delay(100000);
		val++;
		if (8 == val)
		{
			val = 0;
		}
	}

	return 0;
}