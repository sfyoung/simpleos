CC = gcc
LD = ld

CFLAGS = -m32 -g -O -I. -fno-builtin -fno-stack-protector -I../include #-Wl,l,-n,-z,max-page-size=0x1000 -nostartfiles -nodefaultlibs

LIB := lib.o
OBJS := io.o time_start.o printk.o gdt.o idt.o isr.o task.o

.PHONY all : $(LIB)

$(LIB): $(OBJS)
	$(LD) -melf_i386 -r -o $@ $(OBJS)

io.o: io.c ../include/io.h
	$(CC) $(CFLAGS) -c $< -o $@

gdt.o: gdt.c ../include/gdt.h
	$(CC) $(CFLAGS) -c $< -o $@

idt.o: idt.c ../include/idt.h
	$(CC) $(CFLAGS) -c $< -o $@

isr.o: isr.s
	$(CC) $(CFLAGS) -c $< -o $@

printk.o: printk.c ../include/printk.h
	$(CC) $(CFLAGS) -c $< -o $@

time_start.o: time_start.c io.o
	$(CC) $(CFLAGS) -c $< -o $@

task.o: task.c ../include/task.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJS) $(LIB)
