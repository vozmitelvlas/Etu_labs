#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sched.h>
pthread_t t1, t2;
void* thread1() {
        int i = 0;
        while(1) {
                printf("thread1, %d\n", i++);
                sleep(1);
        }
}
void* thread2() {
        int i = 0;
        while(1) {
                printf("thread2, %d\n", i++);
                sleep(5);
        }
}
void main(){
	int policy;
	struct sched_param param;
	pthread_attr_t attr_1, attr_2;
	 pthread_attr_init(&attr_1);
	 pthread_attr_init(&attr_2);
	pthread_attr_setschedpolicy(&attr_1, SCHED_RR);
	pthread_attr_setschedpolicy(&attr_2, SCHED_RR);
 //значения приоритетов лучше задавать извне – из командной строкиили файла
	 param.sched_priority = 10;
	pthread_attr_setschedparam(&attr_1, &param);
	 param.sched_priority = 30;
	pthread_attr_setschedparam(&attr_2, &param);
	// Стратегия планирования и связанные с ней атрибуты должны быть взяты из описателя //атрибутов, на который указывает аргумент attr
	pthread_attr_setinheritsched (&attr_1, PTHREAD_EXPLICIT_SCHED); 
	pthread_attr_setinheritsched (&attr_2, PTHREAD_EXPLICIT_SCHED);
	// Стратегия планирования и связанные с ней атрибуты должны быть унаследованы
// Установка атрибута наследования от родителя
//pthread_attr_setinheritsched (&attr_1, PTHREAD_INHERIT_SCHED)
// Установка статуса освобождения ресурсов
//pthread_attr_setdetachstate (&attr,PTHREAD_CREATE_DETACHED);
	pthread_attr_getschedparam(&attr_1, &param);
	pthread_attr_getschedpolicy(&attr_1, &policy);
	printf("Thread_1's priority = %d\n", param.sched_priority);
	pthread_attr_getschedparam(&attr_2, &param);
	pthread_attr_getschedpolicy(&attr_2, &policy);
	printf("Thread_2's priority = %d\n", param.sched_priority);
	switch (policy) {
		case SCHED_FIFO:
			printf ("policy SCHED_FIFO\n");
			break;
		case SCHED_RR:
			printf ("policy SCHED_RR\n");
			break;
		case SCHED_OTHER:
			printf ("policy SCHED_OTHER\n");
			break;
		case -1:
			perror ("policy SCHED_GETSCHEDULER");
			break;
		default:
			printf ("policy Неизвестная политика планирования\n");
	}
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_attr_destroy(&attr_1);
	pthread_attr_destroy(&attr_2);
}

