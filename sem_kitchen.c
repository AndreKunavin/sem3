#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int table_capacity;
int waiter_freq;
int current_number = 0;

struct sembuf P_empty = { 0, -1, 0 };
struct sembuf V_empty = { 0, 1, 0 };
struct sembuf P_mut_ex = { 1, -1, 0 };
struct sembuf V_mut_ex = { 1, 1, 0 };
struct sembuf P_full = { 2, -1, 0 };
struct sembuf V_full = { 2, 1, 0 };
 
void* waiter(void* id) {
	int* semid = (int*)id;
	while(1) {
		semop(*semid, &P_full, 1);
		semop(*semid, &P_mut_ex, 1);
		printf("Got a dish, on the table: %d\n", --current_number);
		semop(*semid, &V_mut_ex, 1);
		semop(*semid, &V_empty, 1);
		sleep(waiter_freq);
	}
}

int main(int argc, char* argv[]) {
	
	assert(argc == 4);
	int chief_freq = atoi(argv[1]);		//sec/dish
	waiter_freq = atoi(argv[2]);		//sec/dish
	table_capacity = atoi(argv[3]);		//dishes
	
	char pathname[] = "sem.c";		//make this file before starting
	
	key_t key;
	if ((key = ftok(pathname, 0)) < 0) {
		printf("Can\'t generate key\n");
	       	exit(-1);
	}

	int semid;
	if ((semid = semget(key, 3, 0666 | IPC_CREAT)) < 0) {
		printf("Can\'t get semid\n");
		exit(-1);
	}
	
	struct sembuf cap_empty = { 0, table_capacity, 0};
	if (semop(semid, &cap_empty, 1) != 0) {
		printf("Can\'t semop");
		exit(-1);
	}
        semop(semid, &V_mut_ex, 1);
	
	pthread_t thid;
	int result = pthread_create(&thid, (pthread_attr_t*)NULL, waiter, (void*)&semid);
	if (result != 0) {
		printf("Error on thread create, return value = %d\n", result);
		exit(-1);
	}

	while(1) {
		sleep(chief_freq);
		semop(semid, &P_empty, 1);
		semop(semid, &P_mut_ex, 1);
		printf("Put a dish, on the table: %d\n", ++current_number);
		semop(semid, &V_mut_ex, 1);
		semop(semid, &V_full, 1);
	}
	pthread_join(thid, (void**)NULL);

	return 0;
}
