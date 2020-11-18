#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

pid_t cpid;
pid_t ppid;

void rt(int snum) {
	printf("RT\n");
	sleep(1);
	kill(ppid, SIGUSR2);
}

void champ(int snum) {
	printf("Champion!\n");
	sleep(1);
	kill(cpid, SIGUSR1);
}


int main() {
	
	(void)signal(SIGUSR1, rt);
	(void)signal(SIGUSR2, champ);
	
	pid_t res = fork();
	
	if (res == 0) {
		(void)signal(SIGUSR2, SIG_IGN);
		while (1);	
	}
	else if (res > 0) {
		sleep(1);
		(void)signal(SIGUSR1, SIG_IGN);
		cpid = res;
		ppid = getpid();
		kill(cpid, SIGUSR1);
		while (1);
	}
	else 
		return(-1);
}
