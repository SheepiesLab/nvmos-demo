#include <syscall.h>

int sys_munmap(void *addr, size_t length)
{
	uint32_t paramCount = 2;
	uint32_t params[paramCount + 1];

	params[0] = SYSCALL_MUNMAP;
	params[1] = addr;
	params[2] = length;

	return syscall(params, paramCount);
}
