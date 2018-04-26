#include <syscall.h>
#include <string.h>
#include <stdint.h>

#include <mem.h>
#include <unistd.h>

static int memf;
static void *mem_buddies[17];
static void *mem_start;

void *malloc(size_t size)
{
	size += 4;
	uint32_t order = 32 - __builtin_clz(size);
	order = MAX(order, 3);
	void *addr = mem_alloc(order);
	if (addr == (void *)0)
		return addr;
	*(uint32_t *)addr = order;
	return addr + 4;
}
void free(void *ptr)
{
	ptr -= 4;
	uint32_t order = *(uint32_t *)ptr;
	mem_buddypush(ptr, order);
}

int mem_init()
{
	memf = sys_open("memf", 0);
	if (memf < 0)
		return -1;
	if (sys_ftruncate(memf, 0x10000)) // 64 KB heap size, not expandable
	{
		return -1;
	}

	mem_buddies[17];
	mem_start = sys_mmap(0, 0x10000, 0, 0, memf, 0);
	if (mem_start == (void *)0)
		return -1;
	memset(mem_start, 0, 0x10000);

	printf("memf: %d\n", memf);
	printf("mem_start: 0x%p\n", (uint64_t)mem_start);

	int i;
	for (i = 0; i < 17; ++i)
		mem_buddies[i] = (void *)0;

	// 0, 1, 2 are not used as they are 1, 2, 4 bytes, min is 8 bytes,
	// 4 bytes overhead carrying order

	mem_buddies[16] = (void *)mem_start;

	return 0;
}

void *mem_nextbuddy(void *addr)
{
	return *(void **)addr;
}

void *mem_buddypop(int order)
{
	void *ret = mem_buddies[order];
	if (ret != (void *)0)
	{
		mem_buddies[order] = *(void **)ret;
	}
	return ret;
}

int mem_buddypush(void *addr, int order)
{
	void *target = (unsigned int)addr + (1 << order);
	void *buddy = addr;
	unsigned int offset = (unsigned int)addr - (unsigned int)mem_start;
	if (offset % (1 << (order + 1)))
	{
		target = (unsigned int)addr - (1 << order);
		buddy = (unsigned int)addr - (1 << order);
	}
	void *current = &(mem_buddies[order]);
	while (mem_nextbuddy(current) != (void *)0)
	{
		if (mem_nextbuddy(current) == target)
		{
			*(void **)current = *(void **)target;
			return mem_buddypush(buddy, order + 1);
		}
		current = mem_nextbuddy(current);
	}
	return 0;
}

int mem_buddyinsert(void *addr, int order)
{
	void *current = &(mem_buddies[order]);
	while (mem_nextbuddy(current) != (void *)0)
	{
		current = mem_nextbuddy(current);
	}
	*(void **)current = addr;
	*(void **)addr = (void *)0;
	return 0;
}

int mem_breakbuddy(int order)
{
	if (order > 16)
		return -1;
	if (mem_buddies[order] == (void *)0)
	{
		if (mem_breakbuddy(order + 1))
			return -1;
	}
	void *buddy = mem_buddies[order];
	mem_buddies[order] = *(void **)buddy;
	mem_buddyinsert(buddy, order - 1);
	mem_buddyinsert((unsigned int)buddy + (1 << (order - 1)), order - 1);
	return 0;
}

void *mem_alloc(int order)
{
	if (mem_buddies[order] == (void *)0)
	{
		if (mem_breakbuddy(order + 1))
			return (void *)0;
	}

	void *ret = mem_buddies[order];
	mem_buddies[order] = mem_nextbuddy(mem_buddies[order]);
	return ret;
}
