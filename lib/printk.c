#include <printk.h>
#include <stdarg.h>

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

static void putchar(char c, int x, int y)
{
	char *v = (char *) 0xb8000 + 2*(80*y + x);
	*v++ = c;
	*v = 0x7;
}

static int puts(char *s, int x, int y)
{
	char c;
	int size = x;
	while(c = *s++){
		putchar(c, x, y);
		x++;
	}
	return x - size;
}

int printk(const char *format,...)
{
	int count = 0;
	const char * arg = format;
	char c, *p;
	char buf[20];
	va_list vl;
	int val, x, y, i = 23;/* 0<=x<=80,0<=y<=24 */
	int size;

	char * v = (char *)0xb8000 + 80*i*2;
	/* Suppose that, text is left align. */
	for (; i >= 0; i--) {
		if (*v=='\0')
			v = (char *) 0xb8000 + 80*(i - 1)*2;
		else {
			//v = (char *) 0xb8000 + 80*[(i + 1)%25];
			break;
		}
	}
	y = (i + 1) % 24;/* Now, the right line has been found. */

	/* output */
	va_start(vl, format);
	while(c = *arg++){
		if ( c != '%')
			putchar(c, x++, y);
		else{
			c = *arg++;
			switch(c) {
				case 'd':
					val = va_arg(vl, int);
					size = itoa(buf, val);
					puts(buf, x, y);
					x += size;
					break;
				case 's':
					p = va_arg(vl, char*);
					size = puts(p, x, y);
					x += size;
					break;
			}
		}
	}
	va_end(vl);
	return count;
}
