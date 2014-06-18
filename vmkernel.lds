OUTPUT_FORMAT("elf32-i386")
ENTRY(start)

SECTIONS
{
	. = 0x100000;

	.setup_gdt :
	{
		load_addr = .;
		*(.setup_gdt)
		. = ALIGN(0x1000);
	}

	. += 0xC0000000;

	.text : AT(ADDR(.text) - 0xC0000000)
	{
		*(.text)
	}

	.data ALIGN (4096) : AT(ADDR(.data) - 0xC0000000)
	{
		*(.data)
		*(.rodata)
		*(.rodata.*)
		*(.rodata1)
	}

	load_end_addr = .;

	.bss ALIGN (4096) : AT(ADDR(.bss) - 0xC0000000)
	{
		*(COMMON*)
		*(.bss*)
	}

	bss_end_addr = .;
}
