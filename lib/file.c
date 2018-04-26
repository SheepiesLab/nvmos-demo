#include <unistd.h>
#include <syscall.h>

struct openedFile
{
	void *mapAddr;
	unsigned int mapLen;
	unsigned int rwhead;
};

// Indexed by fd
static struct openedFile openedFiles[64];

int open(const char *pathname, int flags)
{
	int fd = sys_open(pathname, flags);
	if (fd >= 0)
	{
		openedFiles[fd].mapAddr = (void *)0; 
		openedFiles[fd].mapLen = 0; 
		openedFiles[fd].rwhead = 0; 
	}
	return fd;
}

int close(int fd){}
size_t read(int fd, void *buf, size_t count)
{
	if (openedFiles[fd].mapLen == 0)
	{
		void *addr = sys_mmap(0, 0x80000000, 0, 0, fd, 0);
		if (addr == (void *)0)
			return -1;
		openedFiles[fd].mapAddr = addr; 
		openedFiles[fd].mapLen = 0x80000000; 
	}
	memcpy(buf, openedFiles[fd].mapAddr + openedFiles[fd].rwhead, count);
	openedFiles[fd].rwhead += count;
	return count;
}
size_t write(int fd, const void *buf, size_t count)
{
	if (openedFiles[fd].mapLen == 0)
	{
		void *addr = sys_mmap(0, 0x80000000, 0, 0, fd, 0);
		if (addr == (void *)0)
			return -1;
		openedFiles[fd].mapAddr = addr; 
		openedFiles[fd].mapLen = 0x80000000; 
	}
	memcpy(openedFiles[fd].mapAddr + openedFiles[fd].rwhead, buf, count);
	openedFiles[fd].rwhead += count;
	return count;	
}
size_t lseek(int fd, size_t offset, int whence)
{
	openedFiles[fd].rwhead = offset;
	return offset;
}
void *mmap(void *addr, size_t length, int prot, int flags,
		int fd, size_t offset)
{
	if (openedFiles[fd].mapLen != 0)
	{
		return openedFiles[fd].mapAddr;
	}
	void *maddr = sys_mmap(addr, length, prot, flags, fd, offset);
	if (maddr != (void *)0)
	{
		openedFiles[fd].mapAddr = maddr; 
		openedFiles[fd].mapLen = length; 
	}
	return maddr;
}
int munmap(void *addr, size_t length)
{
 	int fd;
	for (int fd = 0; fd < 64; ++fd)
	{
		if (addr == openedFiles[fd].mapAddr)
			break;
	}
	int res = sys_munmap(addr, length);
	if (res)
		return res;
	
	openedFiles[fd].mapAddr = (void *)0; 
	openedFiles[fd].mapLen = 0; 
	return res;
}
