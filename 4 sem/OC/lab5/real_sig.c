#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/signal.h"

void printsig(int sig, int value){
	if(sig == SIGUSR1){
		printf("Get SIGUSR1\n");
	}
	else if(sig == SIGUSR2){
		printf("Get SIGUSR2\n");
	}
	else if(sig == SIGRTMIN){
		printf("Get SIGRTMIN | value :%d\n", value);
	}
	else if(sig == SIGRTMIN + 1){
		printf("Get SIGRTMIN + 1 | value :%d\n", value);
	}
	else if(sig == SIGRTMIN + 3){
		printf("Get SIGRTMIN + 3 | value :%d\n", value);
	}
}
void sighandler(int sig, siginfo_t *siginfo){
	siginfo_t localinfo = *siginfo;
	printsig(sig, localinfo.si_value.sival_int);
}
int main(int argc, char * argv[]){
	sigset_t mask;	// сигналы, которые следует блокировать
	int sa_flags; // необходимые флаги
	struct sigaction act = { 0 }; // обеспечивает детализированный контроль над сигналами
	union sigval info_to_send; // структура, оправляемая с сигналом

	memset(&act, 0, sizeof(act));
	sigemptyset(&mask); //инициализирует набор сигналов, указанный в set, и "очищает" его от всех сигналов.

	//полностью инициализируется набор set, в котором содержатся все сигналы.
	sigaddset(&mask, SIGRTMIN);
	sigaddset(&mask, SIGRTMIN + 1);
	sigaddset(&mask, SIGRTMIN + 3);
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);

	sa_flags = SA_SIGINFO;

	act.sa_sigaction = (void*)sighandler;// обработчик сигнала
	act.sa_mask = mask;// сигналы, которые следует блокировать
	act.sa_flags = sa_flags;

	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGRTMIN, &act, NULL);
	sigaction(SIGRTMIN + 1, &act, NULL);
	sigaction(SIGRTMIN + 3, &act, NULL);
	sigprocmask(SIG_BLOCK, &mask, NULL); // Блокируем сигналы

	// блок отправления сигнало
	raise(SIGUSR1);

	info_to_send.sival_int = 1;
	sigqueue(getpid(), SIGRTMIN + 3, info_to_send);

	info_to_send.sival_int = 2;
	sigqueue(getpid(), SIGRTMIN + 1, info_to_send);

	info_to_send.sival_int = 3;
	sigqueue(getpid(), SIGRTMIN, info_to_send);

	raise(SIGUSR2);

	info_to_send.sival_int = 4;
	sigqueue(getpid(), SIGRTMIN + 1, info_to_send);

	info_to_send.sival_int = 5;
	sigqueue(getpid(), SIGRTMIN, info_to_send);

	info_to_send.sival_int = 6;
	sigqueue(getpid(), SIGRTMIN + 3, info_to_send);
	raise(SIGUSR1);
	raise(SIGUSR1);

	// Разблокируем сигналы
	sleep(1);
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	return 0;
}
