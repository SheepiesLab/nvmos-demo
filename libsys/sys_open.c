#include <syscall.h>

int sys_open(uint8_t *pathname, int32_t flags)
{
	uint32_t paramCount = 2;
	uint32_t params[paramCount + 1];
	params[0] = SYSCALL_OPEN;
	params[1] = (uint32_t)pathname;
	params[2] = (uint32_t)flags;
	return syscall(params, paramCount);
}

