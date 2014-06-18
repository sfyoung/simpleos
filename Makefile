CC = gcc
LD = ld

CFLAGS = -m32 -g -O -I. -fno-builtin #-Wl,l,-n,-z,max-page-size=0x1000 -nostartfiles -nodefaultlibs

ISO := os.iso
OBJS = boot.o kmain.o 
KERNEL = kernel
.PHONY all : $(ISO)

$(ISO): $(KERNEL)
	cp $(KERNEL) iso/boot
	grub2-mkrescue -o $@ iso

$(KERNEL): $(OBJS) vmkernel.lds
#	$(LD) -melf_i386 -o $@ $(OBJS) -Ttext 0x100000 --entry=start
	$(LD) -melf_i386 -o $@ $(OBJS) -Tvmkernel.lds

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(KERNEL) iso/boot/$(KERNEL) $(ISO)
