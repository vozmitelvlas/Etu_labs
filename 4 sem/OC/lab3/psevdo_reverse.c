#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/resource.h>
int main(int argc, char* argv[]){
        int m, n, pid, ppid;
        m=5000;
        n=1;
	if(fork() != 0 ){
                pid = getpid();
                ppid = getppid();
                printf("DAD PROC, m=%d, pid=%d, ppid=%d\n", m, pid, ppid);
                for(int j = 1; j <= 1000; j++){
                        m-=1;
                        if (m % 200 == 0) printf("dad\n");
                }
	}
        else{
                pid = getpid();
                ppid = getppid();
                printf("SON PROC, pid=%d, ppid=%d\n", pid, ppid);
                for(int i = 1; i <= 1000; i++){
                        n+=1;
                        if (n % 200 == 0) printf("son\n");
                }
                printf("SON PROC, n=%d\n", n);

        }
        printf("Finish!\n");
        return 0;
}

