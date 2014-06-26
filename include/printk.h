#ifndef PRINTK_H_
#define PRINTK_H_

#include <io.h>
#include <stdarg.h>

void cls(void);
int printk(const char *format,...);

#endif
