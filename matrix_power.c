#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Проведены тесты для матриц размером 3, 5, 20 и 40; во всех случаях программа, использующая thread проиграла программе с тремя циклами. Например, для n = 40 t_tread = 0,005s, t_cycle = 0,003s; кол-во ядер = 2, Linux основная ОС; возможная причина проигрыша - большое число нитей (по условию их кол-во = n) || недостаточный размер матриц; в случае матриц размером 4 результат одинаковый - 0,001s*/

struct arg {
	int** first;
	int** second;
	int** result;
	int line;
	int size;
};

int** give_mem(int n) {
	int** ptr;
	ptr = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		ptr[i] = (int*)malloc(n * sizeof(int));
	}
	return ptr;
}

void cl_mem(int** mem, int n) {
	for (int i = 0; i < n; i++)
		free((mem)[i]);
	free(mem);
}

void get_matrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) 
			scanf("%d", &matrix[i][j]);
	}
}

void write_matrix(int** matrix, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) 
			printf("%d ", matrix[i][j]);
		putchar('\n');
	}
}

void* small_power(void* arg) {
	struct arg MtxLine = *((struct arg*)arg);
	for (int j = 0; j < MtxLine.size; j++) {
		MtxLine.result[MtxLine.line][j] = 0;
		for (int i = 0; i < MtxLine.size; i++) {
			MtxLine.result[MtxLine.line][j] += MtxLine.first[MtxLine.line][i] * MtxLine.second[i][j];
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	
	int n = atoi(argv[1]);
	
	int** matrix_1 = give_mem(n);
	int** matrix_2 = give_mem(n);
	int** matrix_res = give_mem(n);


	get_matrix(matrix_1, n);
	get_matrix(matrix_2, n);
	
	
	struct arg* MtxLine = (struct arg*)malloc((n) * sizeof(struct arg));
	for (int i = 0; i < n; i++) {
		MtxLine[i].first = matrix_1;
                MtxLine[i].second = matrix_2;
                MtxLine[i].result = matrix_res;
                MtxLine[i].line = i;
                MtxLine[i].size = n;
	}

	pthread_t* thid = (pthread_t*)malloc(n * sizeof(pthread_t));
	
	for (int i = 0; i < n - 1; i++) {
		int thread;
		thread = pthread_create(&thid[i], (pthread_attr_t*)NULL, small_power, (void*) &MtxLine[i]);
		if(thread != 0) {
			printf ("Error on thread create, return value = %d\n", thread);
			exit(-1);
		}
	}
	
	for (int j = 0; j < n; j++) {
		matrix_res[n - 1][j] = 0;
		for (int i = 0; i < n; i++) {
			matrix_res[n - 1][j] += matrix_1[n - 1][i] * matrix_2[i][j];
		}
	}

	for (int i = 0; i < n - 1; i++) {
		pthread_join(thid[i], (void**)NULL);
	}
	putchar('\n');
	
	write_matrix(matrix_res, n);
	
	free(MtxLine);
	free(thid);
	cl_mem(matrix_1, n);
	cl_mem(matrix_2, n);
	cl_mem(matrix_res, n);
	return 0;
}
