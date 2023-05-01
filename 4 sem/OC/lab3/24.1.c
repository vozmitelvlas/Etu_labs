#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
pthread_t t1, t2;
void *thread1(){
	pthread_t thread = pthread_self();
    	struct sched_param sp;
	sp.sched_priority = 50;
	int p;
	pthread_getschedparam(thread, &p, &sp);
	char *policy = NULL;
	switch (p) {
        	case SCHED_FIFO:
	            policy = "SCHED_FIFO";
	            break;
	        case SCHED_RR:
	            policy = "SCHED_RR";
	            break;
	        case SCHED_OTHER:
	            policy = "SCHED_OTHER";
	            break;
	        case -1:
        	    perror("SCHED_GETSCHEDULER");
	            break;
	}
        printf("Thread1: %s, prior = %d\n", policy, sp.sched_priority);

	int i = 0;
	while(1){
		printf("pthread1, %d\n", i++);
		sleep(1);
	}
}
void* thread2() {
	pthread_t thread = pthread_self();
        struct sched_param sp;
        int p;
        pthread_getschedparam(thread, &p, &sp);
        char *policy = NULL;
        switch (p) {
                case SCHED_FIFO:
                    policy = "SCHED_FIFO";
                    break;
                case SCHED_RR:
                    policy = "SCHED_RR";
                    break;
                case SCHED_OTHER:
                    policy = "SCHED_OTHER";
                    break;
                case -1:
                    perror("SCHED_GETSCHEDULER");
                    break;
        }
        printf("Thread2: %s, prior = %d\n", policy, sp.sched_priority);

	int i = 0;
        while(1) {
                printf("thread2, %d\n", i++);
                sleep(5);
        }
}

int main(int argc, char **argv) {
	pthread_t t1;
	pthread_t t2;
	struct sched_param sp;
	pthread_t thread = pthread_self();
        int p;
        pthread_getschedparam(thread, &p, &sp);
        char *policy = NULL;
        switch (p) {
                case SCHED_FIFO:
                    policy = "SCHED_FIFO";
                    break;
                case SCHED_RR:
                    policy = "SCHED_RR";
                    break;
                case SCHED_OTHER:
                    policy = "SCHED_OTHER";
                    break;
                case -1:
                    perror("SCHED_GETSCHEDULER");
                    break;
        }
        printf("main: %s, prior = %d\n", policy, sp.sched_priority);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
