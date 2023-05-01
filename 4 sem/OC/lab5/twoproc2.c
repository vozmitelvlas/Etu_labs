#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	printf("SIGUSR1 sent; tmp time: %s", asctime(timeinfo));
	kill(atoi(argv[1]), SIGUSR1);
}
