#include "string.h"

size_t strlen(const char * str) {
	const char * ptr = str;

	while(*str++);

	return(ptr-str-1);
}

void * memcopy(void * dst, const void * scr, size_t size) {

	char * to = (char*)dst;
	const char * from = (const char*)scr;

	while(size--)

		*to++ = *from++;

	return(dst);
}

void * memset(void * ptr, int t, size_t size) {
	char p = (char)t + 48;
	char * buf = (char*)ptr;

	while(size--)
		*buf++ = p;

	return(ptr);
}