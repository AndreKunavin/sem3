#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define L0_STR 64 /*first string length == max number of tokens*/
#define L0_PS 16

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
	
	return i;
}


char* read_str(char* str, int L)  
{
	int i = 0;
	char a;

	while ((a = getchar()) != '\n')
	{
		*(str + i) = a;
		i++;
		if (i == L)
			str = realloc(str, L *= 2);	
	}
	*(str + i) = '\0';
	return str;
}


int main()
{
	char** tokens;

	char* str = (char*) malloc(L0_STR);
	str = read_str(str, L0_STR);

	char* punct = (char*) malloc(L0_PS);	
	punct = read_str(punct, L0_PS);

	int t_num = split(str, punct, &tokens);
	
	free(str);
	free(punct);
	
	for (int i = 0; i < t_num; i++)
		 printf("%s\n", tokens[i]);
	
	for (int i = 0; i < L0_STR; i++)
		free(tokens[i]);
	free(tokens);

	return 0;
}
