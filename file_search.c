#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define P_MAX 256
#define N_MAX 64

int res_num = 0; 

int find_file(int c_dep, char path[P_MAX], char name[N_MAX]) {
	if (c_dep < 0) {
		return 0;
	}
	DIR* d_stm = opendir(path);
	struct dirent* dir;
	while ((dir = readdir(d_stm)) != NULL) {
		if (((strcmp(dir->d_name, name)) == 0) && (dir->d_type == 8)) {	
			res_num++;
			printf("%s/%s\n", path, dir->d_name);
		} else if ((dir->d_type == 4) && (strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
			char new_path[P_MAX];
			strcpy(new_path, path);
			strcat(new_path, "/");
			strcat(new_path, dir->d_name);
			find_file(c_dep - 1, new_path, name);
		}	
	}
	closedir(d_stm);
	return 0;
}


int main(int argc, char* argv[]) {	/* 1 - dir; 2 - name; 3 - depth*/
	assert(argc == 4);
	int depth = atoi(argv[3]);
	find_file(depth, argv[1], argv[2]);
	if (res_num == 0) {
		printf ("Not found :(\n");
	} else {
		printf ("Total: %d file(s)\n", res_num);
	}
	return 0;
}

