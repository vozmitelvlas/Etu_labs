#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv){
        int pid, ppid, status;
        pid = getpid();
        ppid = getppid();
        printf("\nFATHER PARAM: pid = %d, ppid = %d\n\n", pid, ppid);
        if (fork() == 0) execvp("son", argv);

        system("ps -xf");
        wait(&status);
        printf("\nChild proccess is finished with status %d\n\n", status);
        return 0;
}

