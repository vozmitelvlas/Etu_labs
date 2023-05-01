#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

	siginfo_t SignalInfo;

        int pid, ppid, status;
	pid_t pid_son;
        pid = getpid();
        ppid = getppid();
        printf("\nFATHER PARAM: pid = %d, ppid = %d\n\n", pid, ppid);
        if (fork() == 0) execl("son", "son", NULL);
	if (fork() == 0) execl("son1", "son1", NULL);
	if (fork() == 0) execl("son2", "son2", NULL);
	if (fork() == 0) execl("son3", "son3", NULL);
	if (fork() == 0) execl("son4", "son4", NULL);
        system("ps xf");
        int wait_result;
        wait_result = waitid(P_ALL, 0, &SignalInfo, WEXITED);
        printf("Wait result: wait = %d, status = %d\n", wait_result, SignalInfo.si_pid);
        return 0;
}

