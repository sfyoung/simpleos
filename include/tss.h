/******************************************************************************
 * Young.
 * This header give the struct of task state segment. The format of tss struct
 * is fixed. You can find the struct in Volum3 3 Chapter 7 of Intel 64 and IA-32
 * Architectures Software Developer's Manual, or search it in the website like
 * Wiki, OSdev, roll your own os tutorials of SIGOps or Linux kernel.
 *****************************************************************************/

#ifndef _TSS_H_
#define _TSS_H_

typedef volatile struct {
	unsigned long back_link;/* set high half to zero. */
	unsigned long esp0;
	unsigned long ss0;/* set high half to zero. */
	unsigned long esp1;
	unsigned long ss1;/* set high half to zero. */
	unsigned long esp2;
	unsigned long ss2;/* set high half to zero. */
	unsigned long cr3, eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
	unsigned long es, cs, ss,ds, fs, gs, ldt;/* set high half to zero. */
	unsigned short trace, iopbmbase;/* Seeing Intel 64 and IA-32 Architectures Software Developer's Manual Volume 1 chapter 16 section 5.2 for detail. */
} tss_struct;

typedef struct {
} task;

#endif
