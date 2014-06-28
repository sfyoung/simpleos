/******************************************************************************
 * kmain.c
 * The first entry function after boot.
 * ***************************************************************************/
#include <io.h>
#include <time.h>
#include <time_start.h>
#include <printk.h>
#include <gdt.h>
#include <idt.h>
#include <task.h>

unsigned int kpdir[1024] __attribute__((aligned(4096)));
unsigned int kptab[1024] __attribute__((aligned(4096)));
struct gdt_e ge[3];
struct gdt_p gdt_;
idt_e idt_table[256];
idt_p idtr;


void paging()
{
	int i;
	void *kpdirpointer = (void *)kpdir + 0x40000000;
	void *kptabpointer = (void *)kptab + 0x40000000;

	for (i = 0; i < 1024; i++) {
		kptab[i] = (i * 4096) | 0x3;
		kpdir[i] = 0;
	}

	kpdir[0] = (unsigned int) kptabpointer |0x3;
	//It's very interesting,have kpdir[0], you can easily recover gdt base to 0x0;
	kpdir[768] = (unsigned int) kptabpointer |0x3;
	asm volatile(	"mov %0, %%eax\n"
					"mov %%eax, %%cr3\n"
					"mov %%cr0, %%eax\n"
					"orl $0x80000000, %%eax\n"
					"mov %%eax, %%cr0\n"::"m"(kpdirpointer));
	return;
}

int main()
{
	paging();
	gdt_st(ge, &gdt_);
	idt_st();
	char* video = (char *) 0xc00b8000;
	
	cls();
	char* string = "Booting Simple OS...";
	int v = 1;
	printk("%s:v %d\n", string, v);

	struct tm time;
	time = time_start();
	printk("Time is %d:%d\n", time.tm_hour, time.tm_min);

	asm volatile("sti");
	task();
	timer_interrupt();

	return 0;
}
