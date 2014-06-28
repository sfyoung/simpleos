/*
 * Young
 * task.c: multitask scheduler
 */

#include <task.h>
#include <printk.h>

task_struct *cur;

void processA()
{
	while(1)
		printk("A\n");
}

void processB()
{
	while(1)
		printk("B\n");
}

void create(unsigned int esp, unsigned int ebp, unsigned int eip)
{
	asm volatile(
			"cli\n"
			"mov %0, %%esp\n"
			"mov %1, %%ebp\n"
			"sti\n"
			"call %2\n"
			::"r"(esp),"r"(ebp),"r"(eip));
}

void task()
{
	task_struct A, B;
	A.pid = 1;
	A.esp = (unsigned int) 0xc0110000;
	A.ebp = (unsigned int) 0xc0110FFF;
	A.eip = (unsigned int) &processA;
	A.next = &B;
	B.pid = 2;
	B.esp = (unsigned int) 0xc0111000;
	B.ebp = (unsigned int) 0xc0111FFF;
	B.eip = (unsigned int) &processB;
	B.next = &A;

	cur = &A;
	asm volatile("cli");
	create(A.esp, A.ebp, A.eip);
	asm volatile("sti");
}

void scheduler()
{
	cur = cur->next;
	asm volatile("cli");
	create(cur->esp, cur->ebp, cur->eip);
	asm volatile("sti");
}
