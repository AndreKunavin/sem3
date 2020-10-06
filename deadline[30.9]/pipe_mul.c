#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

	int fd[2], fp[2];
	size_t size;

	pipe(fd);
	pipe(fp);

	pid_t pid = fork();

	if (pid < 0) {
		printf("Can't fork\n");
		exit(-1);
	} else if (pid > 0) {
		close(fd[0]);
		close(fp[1]);
		
		int a, b;
		scanf("%d %d", &a, &b);

		size = write(fd[1], &a, sizeof(int));
		size = write(fd[1], &b, sizeof(int));
		close(fd[1]);
		
		size = read(fp[0], &a, sizeof(int));
		close(fp[0]);
		
		printf("%d\n", a);
		exit(0);
	} else {
		close(fd[1]);
		close(fp[0]);
		
		int a, b;
		size = read(fd[0], &a, sizeof(int));
		size = read(fd[0], &b, sizeof(int));
		close(fd[0]);
		
		int c = a * b;
		size = write(fp[1], &c, sizeof(int));
		close(fp[1]);
		
		exit(0);
	}
	return(-1);
}

		

