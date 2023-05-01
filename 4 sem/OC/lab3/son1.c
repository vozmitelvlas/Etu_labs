#include <stdio.h>
#include <unistd.h>

int main() {
        int pid, ppid;

        pid = getpid();
        ppid = getppid();

        printf("SON1 PARAMS: pid=%d ppid=%d\n",pid,ppid);
        sleep(9);

        return 0;
}
