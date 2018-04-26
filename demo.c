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
	void *mapaddr;
	printf(
		"FD of new file hello.txt: %d\n", 
		hellofd = open("hello.txt", 0));
	printf(
		"Result of ftruncate: %d\n", 
		ftruncate(hellofd, 0x1000));
	printf(
		"Result of mmap: 0x%p\n", 
		(uint64_t)(mapaddr = mmap(0, 0x1000, 0, 0, hellofd, 0)));

	memcpy(mapaddr + 1384, "Hello! I'm Ben! Demoing demoing",  35);
	lseek(hellofd, 1384, 0);
	char buf[35];
	read(hellofd, buf, 35);
	printf("Test serial reading mmap write: %s\n", buf);
	lseek(hellofd, 500, 0);
	write(hellofd, "TEST WRITE TEST WRITE!", 25);
	printf("Test mmap reading serial write: %s\n", (char *)(mapaddr + 500));


	int hellofd2;
	void *mapaddr2;
	printf(
		"FD2 of file hello.txt: %d\n", 
		hellofd2 = open("hello.txt", 0));
	lseek(hellofd2, 500, 0);
	read(hellofd2, buf, 35);
	printf("Test opened file: %s\n", buf);
	lseek(hellofd2, 1384, 0);
	read(hellofd2, buf, 35);
	printf("Test opened file: %s\n", buf);
	exit();

}
