#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

        int pid, ppid, status;
        pid_t pid_son;
        pid = getpid();
        ppid = getppid();
        printf("\nFATHER PARAM: pid = %d, ppid = %d\n\n", pid, ppid);
        int pid1;
	if ((pid1 = fork()) == 0) execl("son", "son", NULL);
        if (fork() == 0) execl("son1", "son1", NULL);
        if (fork() == 0) execl("son2", "son2", NULL);
        if (fork() == 0) execl("son3", "son3", NULL);
        if (fork() == 0) execl("son4", "son4", NULL);
        system("ps xf");
        int wait_result;
        wait_result = waitpid(pid1, 0, WNOHANG);
        printf("Wait result: wait = %d, status = %d\n", wait_result, 0);
        return 0;
}
