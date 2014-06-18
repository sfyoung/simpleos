/*
 * Young
 * mem.h: kmalloc, kfree
 */
#ifndef MEM_H_
#define MEM_H_

void * kmalloc(unsigned int size);
void kfree(void * ptr, int size);

#endif
