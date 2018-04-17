#ifndef __UNISTD_H__
#define __UNISTD_H__

#include <stdint.h>
#include <stddef.h>

int open(const char *pathname, int flags);
int close(int fd);
size_t read(int fd, void *buf, size_t count);
size_t write(int fd, const void *buf, size_t count);
size_t lseek(int fd, size_t offset, int whence);
int ftruncate(int fd, size_t length);

void *mmap(void *addr, size_t length, int prot, int flags,
		int fd, size_t offset);
int munmap(void *addr, size_t length);

int printf(const char *format, ...);

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

void exit();

#endif
