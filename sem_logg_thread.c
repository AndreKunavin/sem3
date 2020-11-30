#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>

#define N 10000

struct sembuf plus;
struct sembuf minus;
struct sembuf zero;

void* new_thread(void* id) {
	int* semid = (int*)id;

	for (int i = 0; i < N; i++) {
		semop(*semid, &minus, 1);
		fputs_unlocked("TheBeatles ", stdout);
		semop(*semid, &plus, 1);
	}
	return NULL;
}


int main() {
	int semid;
	char pathname[] = "sem.c"; //create this file before starting
	
	key_t key;
	if ((key = ftok(pathname, 0)) < 0) {
		printf("Can\'t generate key\n");
	       	exit(-1);
	}

	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get semid\n");
		exit(-1);
	}

	plus.sem_flg = 0;
	plus.sem_num = 0;
	plus.sem_op = 1;
	
	minus.sem_flg = 0;
	minus.sem_num = 0;
	minus.sem_op = -1;
	
	zero.sem_flg = 0;
	zero.sem_num = 0;
	zero.sem_op = 0;
	
	semop(semid, &zero, 1);
	semop(semid, &plus, 1);

	pthread_t thid;
	int result = pthread_create (&thid, (pthread_attr_t*)NULL, new_thread, (void*)&semid);
	if(result != 0) {
		printf ("Error on thread create, return value = %d\n", result);
		exit(-1);
	}

	for (int i = 0; i < N; i++) {
		semop(semid, &minus, 1);
		fputs_unlocked("PinkFloyd ", stdout);
		semop(semid, &plus, 1);
	}
	
	semop(semid, &minus, 1);
	pthread_join(thid, (void**)NULL);
	return 0;
}
	

