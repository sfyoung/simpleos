CC = gcc
LD = ld

CFLAGS = -m32 -g -O -I. -fno-builtin -Iinclude #-Wl,l,-n,-z,max-page-size=0x1000 -nostartfiles -nodefaultlibs

ISO := os.iso
LIBS := lib/lib.o
OBJS = boot.o kmain.o $(LIBS)
KERNEL = kernel
.PHONY all : $(ISO)

$(ISO): $(KERNEL)
	cp $(KERNEL) iso/boot
	grub2-mkrescue -o $@ iso

$(KERNEL): $(OBJS) vmkernel.lds
#	$(LD) -melf_i386 -o $@ $(OBJS) -Ttext 0x100000 --entry=start
	$(LD) -melf_i386 -o $@ $(OBJS) -Tvmkernel.lds
#	$(CC) $(CFLAGS) -o $@ $(OBJS) -Tvmkernel.lds

$(LIBS):
	(cd lib;make)
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(KERNEL) iso/boot/$(KERNEL) $(ISO)
	(cd lib;make clean)
