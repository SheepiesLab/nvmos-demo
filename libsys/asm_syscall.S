.section .text

.global asm_syscall
.align 4
.type asm_syscall @function

asm_syscall:
	pop			%edx
	pop			%eax
	pop			%ebx
	mov			%esp,	%ecx
	sysenter
	ret
