#ifndef __STDIO_H
#define __STDIO_H

#define putc(ch) putchar(ch)

int printf(char *fmt, ...);
int puts(char *str);
int strcmp(char *pstr1, char *pstr2);
int strlen(char *pstr);

#endif

