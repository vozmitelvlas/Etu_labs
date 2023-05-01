#include <stdio.h>
#include <unistd.h>

int main() {
        int pid, ppid;

        pid = getpid();
        ppid = getppid();

        printf("SON2 PARAMS: pid=%d ppid=%d\n",pid,ppid);
	sleep(5);
        return 0;
}
