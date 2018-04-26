
LD=i686-elf-ld
CC=i686-elf-gcc
AS=i686-elf-as

CFLAGS=-I./include -nostdlib -ffreestanding -g

LDFLAGS=-T linker.ld

OBJS=\
demo.o \
libsys/syscall.o \
libsys/asm_syscall.o \
libsys/sys_prints.o \
libsys/sys_open.o \
libsys/sys_ftruncate.o \
libsys/sys_mmap.o \
libsys/sys_munmap.o \
libsys/sys_halt.o \
lib/printf.o \
lib/file.o \
lib/ftruncate.o \
lib/exit.o \
lib/mem.o \
lib/string/memcpy.o \
lib/string/memcmp.o \
lib/string/memmove.o \
lib/string/memset.o \
lib/string/strcmp.o \
lib/string/strcpy.o \
lib/string/strlen.o

.PHONY: install all clean

all: demo

demo: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.S.o:
	$(AS) -o $@ $< 	

clean:
	rm ./demo
	rm $(OBJS)

install: all
	cp ./demo ../project/sysroot/boot/
	cp ./demo ../project/isodir/boot/

