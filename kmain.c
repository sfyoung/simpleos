/******************************************************************************
 * kmain.c
 * The first entry function after boot.
 * ***************************************************************************/
struct gdt_entry{
	long long entry;
	/*I know it is bad, but here is just for simplicity*/
}__attribute__((packed));

struct gdt_pointer{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

unsigned int kpdir[1024] __attribute__((aligned(4096)));
unsigned int kptab[1024] __attribute__((aligned(4096)));
struct gdt_entry gdt[3];
struct gdt_pointer gp;

void cls(void);
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

void gdt_st()
	//After mapping the page, setup the base of gdt to 0x0
{
	gdt[0].entry = 0x0000000000000000;
	gdt[1].entry = 0x00cf9a000000ffff;
	gdt[2].entry = 0x00cf92000000ffff;

	gp.limit = sizeof(struct gdt_entry) * 3 - 1;
	gp.base = (unsigned int)&gdt;

	asm volatile (
					"lgdt (%0)\n"
					"mov $0x10, %%eax\n"
					"mov %%ax, %%ds\n"
					"mov %%ax, %%es\n"
					"mov %%ax, %%fs\n"
					"mov %%ax, %%gs\n"
					"mov %%ax, %%ss\n"
					"jmp $0x08, $ok_done"::"m"(gp));
	//if not jmp, i think it's still ok, but can't show hello world message in VirtualBox. I have not found the reason.
}

int main()
{
	paging();
	gdt_st();
	char* video = (char *) 0xc00b8000;
	
	cls();
	/* "Hello, world!" */
	char* string = "Booting Simple OS...";
	int i = 0;
	for (i = 0; i < 20; i++) {
		video[2*i] = string[i];
		video[2*i + 1] = 0x7;
	}

	return 0;
}

void
cls(void) {
	char *video = (char *) 0xc00b8000;
	int i;
	for (i = 0; i < 80*24; i++) {
		video[2*i] = ' ';
		video[2*i + 1] = 0x7;
	}
}
