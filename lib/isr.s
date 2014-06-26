/*
 * Young
 * isr.s: ISR wrapper. The ISR need be called and returned manually.
 */

	.text
	.global irq0

irq0:
	pusha
	pushf
	call irq_handler
	popf
	popa
	iret
