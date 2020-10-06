#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int pid = 0;
	char** arr;
	arr[0] = "gcc";
	arr[1] = "hw.c";
	arr[2] = NULL;

	//printf("%s\n", arr[0]);
	pid = fork();
	//printf("%d\n", pid);
	if (pid == 0)
		execvp("gcc", arr);
	else
	{
		int s = 0;
		wait(&s);
		execlp("./a.out", "./a.out", NULL);
	}
	printf("Error\n");
	return 0;
}
