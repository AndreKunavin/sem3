#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define N 256

int main() {
	
	char string[N] = {}; 
	size_t n = 0;

	ssize_t size = read(STDIN_FILENO, string, N);
	scanf("%ld", &n);
	
	char word[N] = {};	

	(void)umask(0);

	int fd = open("myfile", O_WRONLY | O_CREAT, 0666);
	write(fd, string, size);
	close(fd);
	
	int fp = open("myfile", O_RDONLY, 0666);
	size = read(fp, word, n);
	while (size > 0) {
		if (size == n) {
			write(STDOUT_FILENO, word, n);
			putchar('\n');
		} else {
			write(STDOUT_FILENO, word, size - 1);
			putchar('\n');
			close(fp);
			return 0;
		}
		size = read(fp, word, n);
	}
	close(fd);
	return 0;
}
