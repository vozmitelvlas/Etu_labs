#include <stdio.h>
#include <unistd.h>

int main() {
	int pid, ppid;
	pid=getpid();
	ppid=getppid();
	printf("\n SON PARAM: pid=%d ppid=%d \n", pid, ppid);
	sleep(10);
	pid=getpid();
	ppid=getppid();
	printf("\n SON PARAM: pid=%d ppid=%d \n", pid, ppid);
}
