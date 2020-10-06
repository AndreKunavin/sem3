#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define  N 64
#define L0_STR N


int split(char* string, char* punct, char*** tokens)
{
	char* str;
	char* token;
	int i;
	*tokens = (char**)malloc(L0_STR * sizeof(char*));

	for (i = 0, str = string; ; i++, str = NULL)
	{
		token = strtok(str, punct);

		if (token == NULL)
			break;

		*(*tokens + i) = (char*)malloc(strlen(token) * sizeof(char));
		strcpy(*(*tokens + i), token);
	}
	*(*tokens + i) = NULL;
	return i;
}


void free2(char*** arr, int n_words) {
	for (int i = 0; i < n_words; i++)
		free(*(*arr + i));
	free(*arr);
}

/*программа не требует количества аргументов в начале файла, время для iой строки >= i (начинаем считать с 1)*/
int main()	
{
	FILE* fd = fopen("task.txt", "r");
	if (fd == NULL) {
		printf("CAN'T OPEN\n");
		exit(-1);
	}
	char** commands = (char**)malloc(N * sizeof(char*));
	int j;
	for (j = 0; ; j++) {
		*(commands + j) = (char*)malloc(N * sizeof(char*));
		if ((*(commands + j) = fgets(*(commands + j), N, fd)) != NULL) {
		} else {
			break;
		}	
	}
	fclose(fd);
        
	char** tokens;	
	int n_words = 0;
	int sec = 0;

	for (int i = 0; i < 7; i++)
	{
		pid_t pid = fork();
		if (pid == 0) {
			if (i != j) {
				sleep(i + 1);
				n_words = split(*(commands + i), " \n", &tokens);
				sec = atoi(*(tokens + n_words - 1));
				tokens[n_words - 1] = NULL;
				sleep(sec - i - 1);
				execvp(tokens[0], tokens);
			} else {
				free2(&tokens, N);
                                free2(&commands, N);
			}
			exit(0);
		}
	}
	return 0;
}
