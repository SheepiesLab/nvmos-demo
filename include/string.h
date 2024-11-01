#ifndef __string_h__
#define __string_h__

#include <stddef.h>

int memcmp(const void *, const void *, size_t);

void *memcpy(void *__restrict, const void *__restrict, size_t);

void *memmove(void *, const void *, size_t);

void *memset(void *, int, size_t);

size_t strlen(const char *);

int strcmp(const char *, const char *);

char *strcpy(char *, const char *);

#endif
