#include "stdio.h"
#include "types.h"

typedef char * va_list;

#define _INTSIZEOF(n) ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )

/* 根据固定参数fmt及其类型计算出第一个可变参数所在起始地址，ap为第一个可变参数的起始地址，v为固定参数fmt */
#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))

/* 取该地址处可变参数的值，ap为该参数的起始地址，t为该参数的类型 */
#define va_arg(ap, t) ( *(t *)(ap = ap + _INTSIZEOF(t), ap - _INTSIZEOF(t)))

/*  */
#define va_end(ap) (ap = (va_list)0)

const char hex2ch[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
};

static int processNum(int arg, char flags, int fldwidth, int base)
{
	unsigned long tmp = 0;
	int len = 0;
	char buf[21];
	char *p = buf + sizeof(buf);
	*p = '\0';

	if ((0 > arg) && (10 == base))
	{
		tmp = -arg;
	}
	else
	{
		tmp = arg;
	}
	tmp &= 0xFFFFFFFF;

	do
	{
		p--;
		*p = hex2ch[tmp % base];
		len++;
	} while (0 != (tmp /= base));
	

	if ((0 != fldwidth) &&
	    (len < fldwidth))
	{
		while (len < fldwidth)
		{
			p--;
			*p = flags;
			len++;
		}
	}

	if ((0 > arg) && (10 == base))
	{
		p--;
		*p = '-';
	}

	puts(p);

	return 0;
}

static int vprintf(const char *fmt, va_list ap)
{
	char flags = '\0';
	int fldwidth = 0;
	char convtype;

	while (*fmt)
	{
		switch (*fmt)
		{
			case '%':
			{
				fmt++;
				/* 
					%[flags][fldwidth][precision][lenmodifier]convtype
					  -       最小宽度 最少输出数字位数 参数长度    参数类型: d o u x f c s p
					  +
					  空格
					  #
					  0

				 */
				/* 获取flags */
				if (('0' == *fmt) ||
					('-' == *fmt) ||
					('+' == *fmt) ||
					('#' == *fmt) ||
					(' ' == *fmt))
				{
					flags = *fmt;
					fmt++;
				}

				/* 获取fldwidth */
				while (('0' <= *fmt) && 
					   ('9' >= *fmt))
				{
					fldwidth = fldwidth * 10 + *fmt - '0';
					fmt++;
				}

				/* 获取参数类型 */
				convtype = *fmt;
				switch (convtype)
				{
					case 'd':
						processNum(va_arg(ap, int), flags, fldwidth, 10);
						break;
					case 'o':
						processNum(va_arg(ap, unsigned int), flags, fldwidth, 8);
						break;
					case 'x':
						processNum(va_arg(ap, unsigned int), flags, fldwidth, 16);
						break;
					case 'c':
						putc(va_arg(ap, char));
						break;
					case 's':
						puts(va_arg(ap, char *));
						break;
					case 'p':
						processNum(va_arg(ap, unsigned int), '0', 8, 16);
						break;

					default:
					break;
				}

				break;
			}

			/* 不是占位符就直接输出 */
			default:
			{
				putc(*fmt);
				break;
			}
		}
		fmt++;
	}
}

int printf(char *fmt, ...)
{
	va_list ap = NULL;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	return 0;
}

int puts(char *str)
{
	int len = 0;
	while (*str)
	{
		putc(*str);
		str++;
		len++;
	}
	return len;
}

