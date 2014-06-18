#ifndef GDT_H_
#define GDT_H_

struct gdt_e{
	long long entry;
	/*I know it is bad, but here is just for simplicity*/
}__attribute__((packed));

struct gdt_p{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

void gdt_st(struct gdt_e * ge, struct gdt_p *gp);

#endif
