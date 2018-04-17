#include <syscall.h>

uint32_t sys_mmap(void *addr, size_t length, int prot, int flags, int fd, size_t offset)
{
	uint32_t paramCount = 6;
	uint32_t params[paramCount + 1];

	params[0] = SYSCALL_MMAP;
	params[1] = addr;
	params[2] = length;
	params[3] = prot;
	params[4] = flags;
	params[5] = fd;
	params[6] = offset;

	return syscall(params, paramCount);
}
