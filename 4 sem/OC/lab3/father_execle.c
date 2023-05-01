#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
        int pid, ppid, status;
        pid = getpid();
        ppid = getppid();
        printf("\nFATHER PARAM: pid = %d, ppid = %d\n\n", pid, ppid);
	char *new_env[] = {"TELYING",NULL};
        if(fork() == 0)
		execle("son", "son", NULL, new_env);

        system("ps -xf");
        wait(&status);
        printf("\nChild proccess is finished with status %d\n\n", status);
        return 0;
}
