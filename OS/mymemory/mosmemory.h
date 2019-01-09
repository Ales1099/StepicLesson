#ifndef MOS_MEMORY
#define MOS_MEMORY

#include <stddef.h>

#define BUF_SIZE	1048576

struct memory
{
	void * mem[BUF_SIZE];
	size_t size = sizeof mem;
};


void setup(void *, size_t);

void * mos_alloc(size_t);

void mos_free(void*)

#endif