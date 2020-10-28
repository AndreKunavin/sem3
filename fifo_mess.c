#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define N 256

int main(int arc, char* argv[]) {
	
	
	char* client = argv[1];
	int client_num;
	client_num = client[0] - '0';
	if (client_num < 1 || client_num > 2) {
		exit(-1);
	}

	int fd, fp, pid;
	char* names[3] = {};
	names[1] = "aaa.fifo";
	names[2] = "bbb.fifo";
	/*			включаем этот модуль при первом запуске для создания fifo
	(void)umask(0);
	if(mknod(names[1], S_IFIFO | 0666, 0) < 0){
		printf("Can\'t create FIFO\n");
		exit(-1);
	}
	
	if(mknod(names[2], S_IFIFO | 0666, 0) < 0) {
		printf("Can\'t create FIFO\n");
		exit(-1);
	}
	*/
	if((pid = fork()) < 0) {
		printf("Can\'t fork child\n");
		exit(-1);
	
	} else if (pid > 0) {

		if((fd = open(names[client_num], O_WRONLY)) < 0) { 
			printf("Can\'t open FIFO for writting\n");
			exit(-1);
		}
		while(1) {
			size_t size, len;
			char* mess = (char*)malloc(N);
			mess = fgets(mess, N, stdin);
			len = strlen(mess);
			mess[len - 1] = '\0';
			size = write(fd, mess, len);
		
			if(size != len) {
				printf("Can\'t write all string to FIFO\n");
				exit(-1);
			}
			free(mess);
		}

	} else {
		if((fp = open(names[3 - client_num], O_RDONLY)) < 0) {
			printf("Can\'t open FIFO for reading\n");
			exit(-1);
		}
		while(1) {
			char* resstring = (char*)malloc(N);
			size_t size = read(fp, resstring, N);
			if(size < 0){
				printf("Can\'t read string\n");
				exit(-1);
			}
			resstring[size] = '\0';
			printf("%s\n",resstring);
			free(resstring);
		}

	}
	return 0;
} 
