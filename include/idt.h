/*
 * Young.
 * idt.h: Just like gdt.h.
 */

#ifndef IDT_H_
#define IDT_H_

typedef struct {
	unsigned short offset_l;	// 0..15 bits of 32bits offset
	unsigned short se;	// code segment selector in GDT
	unsigned char unused;	// unused, default zero
	unsigned char attype;	/* type and attributes,i386 Interrupt Gate:0xE; i386 Trap Gate:0xf; i386 Task Gate:0x5(all are 32bits.) */
	unsigned short offset_h; //16..31 bits of 32bits offset
}__attribute__((packed)) idt_e;

typedef struct {
	unsigned short limit;
	unsigned int base;
}__attribute__((packed)) idt_p;

void idt_st();

#endif
