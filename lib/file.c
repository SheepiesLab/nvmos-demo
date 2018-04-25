#include <unistd.h>
#include <syscall.h>

int open(const char *pathname, int flags)
{
	return sys_open(pathname, flags);
}

int close(int fd);
size_t read(int fd, void *buf, size_t count);
size_t write(int fd, const void *buf, size_t count);
size_t lseek(int fd, size_t offset, int whence);
void *mmap(void *addr, size_t length, int prot, int flags,
		int fd, size_t offset)
{
	return sys_mmap(addr, length, prot, flags, fd, offset);
}
int sys_munmap(void *addr, size_t length)
{
	return sys_munmap(addr, length);
}
int munmap(void *addr, size_t length);
