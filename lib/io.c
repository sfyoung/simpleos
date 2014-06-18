/*
 * Young
 * io.c: outb, inb
 */

#include <io.h>

void outb(int value, int port)
{
	asm volatile("outb %%al, %%dx"::"a"(value), "d"(port));
}

char inb(int port)
{
	char c;
	asm volatile("inb %%dx, %%al":"=a"(c):"d"(port));
	return c;
}
