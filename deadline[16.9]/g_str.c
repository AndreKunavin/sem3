#include <stdio.h>
#include <math.h>	/*to compile add "-lm" */
#include <string.h>


void gen_str(int n, char* str)
{
	int i;		
	int j = 0;	/*adress of a new letter*/
	str[0] = 'a';

	for (i = 1; i <= n; i++)
	{
		j = (int)pow(2, i) - 1;
		str[j] = 'a' + i;
		strncpy(str + j + 1, str, j);
	}
	str[(int)pow(2,n + 1)] = '\0'; 				
}

int main()
{
	int n = 0;
	char str[2048] = {};

	scanf("%d", &n);
	assert(n < 11);

	gen_str(n, str);
	printf("%s\n", str);

	return 0;
}
