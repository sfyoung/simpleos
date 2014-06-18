/*****************************************************************************
 * boot.h
 * Some dada and structure for Multiboot2 header. You can get more information
 * about Multiboot header
 * http://download-mirror.savannah.gnu.org/releases/grub/phcoder/multiboot.pdf
 * or the multiboot2.h file of Grub(locate at include directory).
 * ****************************************************************************/

#ifndef BOOT_H_
#define BOOT_H_

#ifndef MBH_MAGIC
#define MBH_MAGIC 0xE85250D6
/*Multiboot header: magic number*/
#endif

#ifndef MBH_ARCHITECTURE_I386
#define MBH_ARCHITECTURE_I386 0
/*Multiboot header: architecture i386*/
#endif

#ifndef STACK_SIZE
#define STACK_SIZE 0x4000
#endif
#endif
