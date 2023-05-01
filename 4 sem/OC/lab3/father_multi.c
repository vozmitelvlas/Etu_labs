#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
        int pid, fpid[5], ppid, status, result;
        fpid[0] = getpid();
        ppid = getppid();
        printf("\nFATHER PARAM: pid = %d, ppid = %d\n\n", fpid[0], ppid);

        if ((fpid[0] = fork()) == 0) execl("son", "son", NULL);

	if ((fpid[1] = fork()) == 0) execl("son1", "son1", NULL);

	if ((fpid[2] = fork()) == 0) execl("son2", "son2", NULL);

	if ((fpid[3] = fork()) == 0) execl("son3", "son3", NULL);

	if ((fpid[4] = fork()) == 0) execl("son4", "son4", NULL);

        system("ps -xf");
	for(int i = 0; i < 5; i++){
		result = waitpid(fpid[i], &status, WUNTRACED);
		printf("%d) Child proccess with pid = %d is finished with status %d\n", i, result, status);
	}
	wait(&status);
	printf("\nChild proccess is finished with status %d\n\n", status);
        return 0;
}
