#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <stdint.h>
#include <stddef.h>

#define SYSCALL_PRINTS	0x10
#define SYSCALL_OPEN	0x11
#define SYSCALL_CLOSE	0x12
#define SYSCALL_FTRUNC	0x13
#define SYSCALL_MMAP	0x14
#define SYSCALL_MUNMAP	0x15

#define SYSCALL_HALT	0xdeadbeef

unsigned syscall(void *params, size_t paramsSize);

uint32_t sys_prints(void *buf, size_t len);
int sys_open(uint8_t *pathname, int32_t flags);
int sys_ftruncate(int fd, size_t length);
uint32_t sys_mmap(void *addr, size_t length, int prot, int flags, int fd, size_t offset);
void sys_halt();

#endif
