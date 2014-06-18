/******************************************************************************
 * boot.S
 * boot from grub2. This file come from Multiboot Header.If you want to know
 * more about Grub2 Multiboot Header, Please go to
 * http://download-mirror.savannah.gnu.org/releases/grub/phcoder/multiboot.pdf
 * ****************************************************************************/

/*Code begin here*/

#include <boot.h>
	.code32
	.globl start, _mbh
.section .setup_gdt
	.balign 8
_mbh:
multiboot_header:/* grub2 multiboot header */
	.long MBH_MAGIC
	.long MBH_ARCHITECTURE_I386
	.long multiboot_header_end - multiboot_header
	.long -(MBH_MAGIC + MBH_ARCHITECTURE_I386 + multiboot_header_end - multiboot_header)

/*tags*/
	.balign 8
multiboot_header_adress_tag:
	.short 2
	.short 0
	.long multiboot_header_adress_tag_end - multiboot_header_adress_tag
	.long multiboot_header
	.long _mbh
	.long 0
	.long 0
	/*
	.long load_addr
	.long load_end_addr
	.long bss_end_addr*/
multiboot_header_adress_tag_end:

	.balign 8
multiboot_header_entry_address_tag:
	.short 3
	.short 0
	.long multiboot_header_entry_address_tag_end - multiboot_header_entry_address_tag
	.long start
multiboot_header_entry_address_tag_end:

	.balign 8
terminating_tag:
	.short 0
	.short 0
	.long 8
terminating_tag_end:

multiboot_header_end:

start:
	mov $gdtr, %eax
	lgdt (%eax)
	mov $0x10, %eax/*data selector is 0x10*/
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss


	jmp $0x08, $gdtReady


gdtr:
	.word gdt_end - gdt - 1/*gdt size*/
	.long gdt/*gdt address*/

gdt:
	.word 0, 0, 0, 0
	/*null gate*/
	.quad 0x40cf9a000000ffff
	/*code selector 0x08, base = 0x40000000=1GB*/
	//.quad 0x40cf92000000ffff
	.byte 0xff, 0xff, 0x0, 0x0, 0x0, 0x92, 0xcf, 0x40
	/*data selector 0x10*/
gdt_end:
/*
start:
	lgdt gdtr
	jmp $0x08, $_start*/


	.comm stack, STACK_SIZE
	.text
gdtReady:
//	lgdt gdtr
	mov $0x10, %eax/*data selector is 0x10*/
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss

	jmp $0x08, $call_main

call_main:/*ok, call main.*/
	movl $(stack + STACK_SIZE), %esp

	pushl $0
	popf

	pushl %ebx
	pushl %eax

	call main

loop: hlt
	jmp loop
