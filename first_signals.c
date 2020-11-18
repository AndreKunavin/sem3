#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
	printf("%d\n", nsig);
}

int main(void) {
	
	(void)signal(SIGINT, SIG_IGN);	//Ctrl + C
	(void)signal(SIGQUIT, SIG_IGN);	//Ctrl + \
	
	while(1) {
		(void)signal(SIGTSTP, my_handler);	//Ctrl + Z
	}
	return 0;
}
