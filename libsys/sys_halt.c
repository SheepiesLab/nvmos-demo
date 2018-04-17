#include <syscall.h>

void sys_halt()
{
	uint32_t syscall_no = SYSCALL_HALT;
	syscall(&syscall_no, 0);
}
