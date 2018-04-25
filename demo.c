#include <syscall.h>
#include <unistd.h>
#include <mem.h>

int i, a;

void _start(){
	if (mem_init())
		printf("Cannot perform mem_init!\n");

	a = 0;
	for (i = 0; i < 1024; ++i){
		++a;
	}

	printf("Hello from userspace!\n");

	int hellofd;
	printf(
		"FD of new file hello.txt: %d\n", 
		hellofd = open("hello.txt", 0));
	printf(
		"Result of ftruncate: %d\n", 
		ftruncate(hellofd, 0x1000));
	printf(
		"Result of mmap: 0x%p\n", 
		(uint64_t)mmap(0, 0x1000, 0, 0, hellofd, 0));
	exit();

}
