#include <syscall.h>

extern uint32_t asm_syscall(uint32_t paramsPtr, uint32_t paramsSize);
unsigned syscall(void *params, size_t paramsSize)
{
	return asm_syscall((uint32_t)params, (uint32_t)paramsSize);
}
