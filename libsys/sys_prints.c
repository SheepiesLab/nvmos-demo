#include <stddef.h>
#include <syscall.h>

uint32_t sys_prints(void *buf, size_t len)
{
	size_t paramCount = 2;
	uint32_t paramsBuf[paramCount + 1];
	uint32_t *syscall_no = &(paramsBuf[0]);
	uint32_t *bufferPtr = &(paramsBuf[1]);
	uint32_t *bufferSize = &(paramsBuf[2]);
	
	*syscall_no = (uint32_t)SYSCALL_PRINTS;
	*bufferPtr = (uint32_t)buf;
	*bufferSize = (uint32_t)len;

	return syscall(paramsBuf, paramCount);
}
