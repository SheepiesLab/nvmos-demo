#include <unistd.h>
#include <syscall.h>

int ftruncate(int fd, size_t length)
{
	return sys_ftruncate(fd, length);
}

