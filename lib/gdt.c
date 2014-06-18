#include <gdt.h>

void gdt_st(struct gdt_e * ge, struct gdt_p *gp)
	//After mapping the page, setup the base of gdt to 0x0
{
	ge[0].entry = 0x0000000000000000;
	ge[1].entry = 0x00cf9a000000ffff;
	ge[2].entry = 0x00cf92000000ffff;

	gp->limit = sizeof(struct gdt_e) * 3 - 1;
	gp->base = (unsigned int)&ge[0];

	asm volatile ("lgdt %0\n\t"
					"mov $0x10, %%eax\n\t"
					"mov %%ax, %%ds\n\t"
					"mov %%ax, %%es\n\t"
					"mov %%ax, %%fs\n\t"
					"mov %%ax, %%gs\n\t"
					"mov %%ax, %%ss\n\t"
					"jmp $0x08, $ok_done"::"m"(*gp));
	//if not jmp, i think it's still ok, but can't show hello world message in VirtualBox. I have not found the reason.
}
