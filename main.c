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
		arr->strs = realloc(arr->strs, 2 * arr->size * sizeof(char*));
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

darr* get_options(FILE* file_ptr) {
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
			chr = fgetc(file_ptr);
			if(chr == '\n' || chr == EOF) break;
			str[i] = chr;
		}
		darr_push(options, str);
	}
	while(chr != EOF);
	
	return options;
}

int main(int argc, char** argv) {
	FILE* file_ptr = fopen(PATH, "r");
	if(file_ptr == NULL) exit(1);
	darr* options = get_options(file_ptr);
	fclose(file_ptr);
	file_ptr = fopen(PATH, "w");
	if(file_ptr == NULL) exit(1);

	int chosen;
	if(argc == 1)
		chosen = mmenu(options->strs, options->used, " >");
	else
		chosen = mmenu(options->strs, options->used, argv[1]);

	if(chosen == -1)
		fputs("", file_ptr);
	else
		fputs(options->strs[chosen], file_ptr);

	darr_free(options);	
	fclose(file_ptr);
}