/*
 * Young
 * io.h: outb, inb for device port
 */
#ifndef IO_H_
#define IO_H_

void outb(int value, int port);

char inb(int port);

#endif
