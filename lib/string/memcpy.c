#include <string.h>

void *memcpy(void *restrict dstptr, const void *restrict srcptr, size_t size) {
	int i;

	if (
			(unsigned)dstptr % sizeof(long) == 0 &&
			(unsigned)srcptr % sizeof(long) == 0 &&
			size % sizeof(long) == 0
			){
		long *d = dstptr;
		const long *s = srcptr;
		for (i = 0; i < size/sizeof(long); ++i){
			d[i] = s[i];
		}
		return dstptr;
	}

    unsigned char *dst = (unsigned char *) dstptr;
    const unsigned char *src = (const unsigned char *) srcptr;
    for (size_t i = 0; i < size; i++)
        dst[i] = src[i];
    return dstptr;
}
