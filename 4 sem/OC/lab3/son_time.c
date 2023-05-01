#include <stdio.h>
#include <unistd.h>
int main()
{
	printf("SON PARAMS: pid=%d ppid=%d\n", getpid(), getppid());
	return 0;
}

