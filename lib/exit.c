#include <unistd.h>
#include <syscall.h>

void exit()
{
	sys_halt();
}
