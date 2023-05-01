#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main() {
	int pid1, pid2, pid3;
	int pid, ppid, status;
	pid = getpid();
	ppid = getppid();
	printf("\n\nFATHER PARAM pid=%d ppid=%d\n",pid, ppid);
	if((pid1=fork()) == 0) execl("son1","son1", NULL);
	if((pid2=fork()) == 0) execl("son2","son2", NULL);
	if((pid3=fork()) == 0) execl("son3","son3", NULL);

	sleep(5);
	system("ps -s");
	kill(pid1,SIGUSR1);
	kill(pid2,SIGUSR1);
	kill(pid3,SIGUSR1);
	sleep(7);
	system("ps -s");
	wait(&status);
	return 0;
}
