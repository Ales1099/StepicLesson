#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	static int value = 42;
	const pid_t pid = fork();

	if(pid == -1)
	{
		printf("failed to fork\n");
		return(-1);
	}

	if(!pid) value = 43;
	else waitpid(pid,NULL,0);

	printf("value (%p) = %d\n", &value, value );

	return(0);
}
