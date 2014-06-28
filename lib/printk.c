/*
 * Young
 * printk.c: kernel printk function.
 */

#include <printk.h>
int cursor_x, cursor_y;	/* cursor position. 0<=cursor_x<80, 0<=cursor_y < 25. */

static void set_cursor()
{
	unsigned short l = cursor_y * 80 + cursor_x;

	outb(14, 0x3D4);
	outb((unsigned char)((l >> 8) & 0xFF), 0x3D5);
	outb(15, 0x3D4);
	outb((unsigned char)(l & 0xFF), 0x3D5);
}


void cls(void) {
	char *video = (char *) 0xc00b8000;
	int i;
	for (i = 0; i < 80*24; i++) {
		video[2*i] = '\0';
		video[2*i + 1] = 0x7;
	}
	cursor_x = 0;
	cursor_y = 0;
	set_cursor();
}

static int itoa(char *buf, int num)
{
	char *str = buf;
	char q[20];
	char *p = q;
	int n = num;
	int size = 0;
	if (n < 0) {
		*str++ = '-';
		n = -n;
		size++;
	}

	*p++ = 0;
	do {
		*p++ = (n % 10) + '0';
	} while(n /= 10);

	while(*(--p)) {
		*str++ = *p;
		size++;
	}

	*str = 0;

	return size;
}

static void scroll()
{
	char *v = (char *) 0xb8000;
	int i = 0;
	for (i = 0; i < 24 * 80 * 2; i++) {
		v[i] = v[i + 160];
	}
	cursor_x = 0;
	cursor_y = 24;
}


static void putchar(char c)
{
	if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else {
		char *v = (char *) 0xb8000 + 2*(80*cursor_y + cursor_x);
		*v++ = c;
		*v = 0x7;
		cursor_x++;
	}

	if (cursor_x > 79) {
		cursor_x = 0;
		cursor_y++;
	}

	if(cursor_y > 24) {
		scroll();
	}

	set_cursor();
}

static int puts(char *s)
{
	char c;
	int size = 0;
	while(c = *s++){
		putchar(c);
		size++;
	}
	return size;
}

int printk(const char *format,...)
{
	int count = 0;
	const char * arg = format;
	char c, *p;
	char buf[20];
	va_list vl;
	int val;

	/* output */
	va_start(vl, format);
	while(c = *arg++){
		if ( c != '%') {
			putchar(c);
			count++;
		}
		else{
			c = *arg++;
			switch(c) {
				case 'd':
					val = va_arg(vl, int);
					count += itoa(buf, val);
					puts(buf);
					break;
				case 's':
					p = va_arg(vl, char*);
					count += puts(p);
					break;
			}
		}
	}
	va_end(vl);
	return count;
}
