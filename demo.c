#include <syscall.h>
#include <unistd.h>
#include <mem.h>

int i, a;

void _start()
{
	if (mem_init())
		printf("Cannot perform mem_init!\n");

	a = 0;
	for (i = 0; i < 1024; ++i)
	{
		++a;
	}

	printf("Hello from userspace!\n");

	char input[0x1000];
	const char *str = "asdfghjk";
	int hellofd;
	void *mapaddr;
	int file_pages = 0x80;
	printf(
		"FD of new file hello.txt: %d\n",
		hellofd = open("hello.txt", 0));
	printf(
		"Result of ftruncate: %d\n",
		ftruncate(hellofd, 0x1000 * file_pages));
	printf(
		"Result of mmap: 0x%p\n",
		(uint64_t)(mapaddr = mmap(0, 0x1000 * file_pages, 0, 0, hellofd, 0)));
	for (i = 0; i < 0x1000; ++i){
		input[i] = str[i%8];
	}
	lseek(hellofd, 0, 0);
	for (i = 0; i < file_pages; ++i)
		write(hellofd, input, 0x1000);

	printf("Starting the test in ");

	for (i = 5; i >= 0; --i){
		for (a = 0; a < 0x20000000; ++a);
		printf("%d ", i);
	}
	printf("\n");

	for (a = 0; a < 0x1000; ++a){
		lseek(hellofd, 0, 0);
		for (i = 0; i < file_pages; ++i)
			read(hellofd, input, 0x1000);
	}


	/*for (a = 0; a < 0x400000; ++a){
		mapaddr = mmap(0, 0x1000 * file_pages, 0, 0, hellofd, 0);
		munmap(mapaddr, 0x1000 * file_pages);
	}*/

	printf("Finished!\n");

	while(1);

	exit();
}
