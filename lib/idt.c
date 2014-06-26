#include <io.h>
#include <idt.h>

extern idt_e idt_table[256];
extern idt_p idtr;
extern void irq0();
unsigned int t= 0;

void irq_handler()
{
	outb(0x20, 0x20);
	t++;
	printk("irq0: %d\n", t);
}

static idt_st_entry(idt_e *entry, unsigned int addr, unsigned short se, unsigned char flag)
{
	entry->offset_l = addr & 0xFFFF;
	entry->se = se;
	entry->unused = '\0';
	entry->attype = flag;
	entry->offset_h = (addr >> 16) & 0xFFFF;
}

void timer_interrupt()
{
	idt_st_entry(&idt_table[32], (unsigned int)&irq0, 0x08, 0x8e);
	unsigned short v = 1193180 / 50;
	unsigned char l = (unsigned char) (v & 0xFF);
	unsigned char h = (unsigned char) ((v >> 8) & 0xFF);
	outb(0x36, 0x43);
	outb(l, 0x40);
	outb(h, 0x40);
}

void idt_st()
{
	int i = 0;
	idtr.base = (unsigned int) &idt_table;
	idtr.limit = (unsigned short)((sizeof(idt_table) * 256) - 1);
/*
	for (i = 0; i < 256; i++) {
		idt_st_entry(&idt_table[i],...);
	}*/

	outb(0x11, 0x20);	/* initialization 8259, and set irq offset. offset is set by ICW2. ICW3 set cascade. You can know more from osdev site:http://wiki.osdev.org/8259_PIC */
	outb(0x11, 0xA0);
	outb(0x20, 0x21);
	outb(0x28, 0xA1);
	outb(0x04, 0x21);
	outb(0x02, 0xA1);
	outb(0x01, 0x21);
	outb(0x01, 0xA1);
	outb(0x00, 0x21);
	outb(0x00, 0xA1);
	/* End of 8259. */

	idt_st_entry(&idt_table[32], (unsigned int)&irq0, 0x08, 0x8e);
	asm volatile("lidt (%0)\n\t"
				::"m"(idtr));
}
