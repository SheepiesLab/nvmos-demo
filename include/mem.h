#ifndef _MEM_H_
#define _MEM_H_

int mem_init();
void *mem_nextbuddy(void *addr);
void *mem_buddypop(int order);
int mem_buddypush(void *addr, int order);
int mem_buddyinsert(void *addr, int order);
int mem_breakbuddy(int order);
void *mem_alloc(int order);

#endif
