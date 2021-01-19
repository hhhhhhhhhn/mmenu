#include "mmenu.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_SIZE 128
#define D_SIZE 128
#define PATH "/tmp/mmenu"

typedef struct darr {
	char** strs;
	int size;
	int used;
} darr;

void darr_push(darr* arr, char* str) {
	if(arr->used == arr->size) {
		arr->size *= 2;
		arr->strs = realloc(arr->strs, arr->size * sizeof(char*));
		if(arr->strs == NULL) exit(1);
	}
	arr->strs[arr->used] = str;
	arr->used++;
}

void darr_free(darr* arr) {
	for(int i = 0; i < arr->used; i++) {
		free(arr->strs[i]);
	}
	free(arr->strs);
	free(arr);
}

darr* get_options() {
	darr* options = malloc(sizeof(darr));
	if(options == NULL) exit(1);
	options->strs = malloc(D_SIZE * sizeof(char*));
	if(options->strs == NULL) exit(1);
	options->size = D_SIZE;
	options->used = 0;

	char chr;
	char* str;
	int i;
	do {
		str = malloc(MAX_STR_SIZE * sizeof(char));
		if(str == NULL) exit(1);
		for(i = 0; i < MAX_STR_SIZE; i++) {
			chr = fgetc(stdin);
			if(chr == '\n' || chr == EOF) break;
			str[i] = chr;
		}
		darr_push(options, str);
	}
	while(chr != EOF);
	
	return options;
}

int main(int argc, char** argv) {
	darr* options = get_options();
	freopen("/dev/tty", "rw", stdin);
	FILE* file_ptr = fopen(PATH, "w");
	if(file_ptr == NULL) exit(1);

	int chosen;
	if(argc == 1)
		chosen = mmenu(options->strs, options->used, "> ");
	else
		chosen = mmenu(options->strs, options->used, argv[1]);

	if(chosen == -1)
		printf("\n");
	else if(argc > 2 && argv[2][0] == 't')
		printf("%i\n", chosen);
	else
		printf("%s\n", options->strs[chosen]);

	darr_free(options);	
}
