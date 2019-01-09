#include "string.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("%ld\n", strlen("hello"));
	const char * to = "no";
	char * t = (char*)malloc(2*sizeof(char));
	memcopy(t,to,2);
	printf("%s\n",t);
	memset(t,0,2);
	printf("%s\n",t);
	return 0;
}