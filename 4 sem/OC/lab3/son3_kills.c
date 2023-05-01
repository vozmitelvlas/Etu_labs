#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_accept() {
	printf("\nMy signal SIGUSR1 accepted!\n");
}

int main() {
	int pid, ppid;
	pid = getpid();
	ppid = getppid();
	printf("\nSON PARAM: pid=%d ppid=%d \n", pid, ppid);
	signal(SIGUSR1, sig_accept);
	sleep(15);
}
