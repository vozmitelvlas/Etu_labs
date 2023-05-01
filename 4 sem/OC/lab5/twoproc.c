#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
void sig_accept(){
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("SIGUSR1 accepted; tmp time: %s", asctime(timeinfo));
}
int main(){
	int pid = getpid();
	printf("Getter pid = %i\n", pid);
	signal(SIGUSR1, sig_accept);
	sleep(30);
}
