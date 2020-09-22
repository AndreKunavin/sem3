#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid = 0;
	pid = fork();
	//printf("%d\n", pid);
	if (pid == 0)
		execlp("gcc", "gcc", "hw.c", NULL);
	else
	{
		int s = 0;
		wait(&s);
		execlp("./a.out", "./a.out", NULL);
	}
	printf("Error\n");
	return 0;
}
