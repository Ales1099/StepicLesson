#ifndef MOS_STRING
#define MOS_STRING
#include <stddef.h>

size_t strlen(const char *);

void * memcopy(void*,const void*,size_t);

void * memset(void*,int,size_t);

#endif