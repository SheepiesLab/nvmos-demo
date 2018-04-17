#include <syscall.h>

int sys_ftruncate(int fd, size_t length)
{
	uint32_t paramCount = 2;
	uint32_t params[paramCount + 1];

	params[0] = SYSCALL_FTRUNC;
	params[1] = (uint32_t)fd;
	params[2] = (uint32_t)length;
	if (syscall(&params, paramCount) == 0)
		return 0;
	return -1;
}
