#include <stdio.h>
#include <sched.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
int main () {
	struct sched_param shdprm; // Значения параметров планирования
	struct timespec qp; // Величина кванта
	int i, pid, pid1, pid2, pid3, ppid, status;
	pid = getpid();
	ppid = getppid();
	printf("FATHER PARAMS: pid=%d ppid=%d\n", pid, ppid);

	printf ("Квант при циклическом планировании: %g мс\n",
	 qp.tv_sec + qp.tv_nsec / 1000000000.0);

	if(fork() == 0){
		printf ("SON: Квант процессорного времени: %g мс\n",
	        qp.tv_sec + qp.tv_nsec / 1000000000.0);
		execl("son", "son", NULL);
	}
	wait(&status);

	printf("Процесс с pid = %d завершен\n", status);
	return 0;
}

