#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define N 5

int main()
{
	int i;
	int s = 0;
	for (i = 0; i < N; i++) {
		pid_t pid = fork();
		if (pid > 0) {
			wait(&s);
			exit(0);
		}
		else if (pid == 0) {
			sleep(1);
			printf("PID %d PPID %d\n", getpid(), getppid());

		}
	}
	return 0;
}

