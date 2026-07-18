#include "settings.h"

void list_directory(){
	DIR *dir = opendir(".");
	if(dir == NULL){
		fprintf(stderr, "Folder couldn't opened!");
		exit(1);
	}

	struct dirent *dp;
	int count = 0, capacity = 64;
	
	char **file_names = malloc(sizeof(char*) * capacity);
	if(file_names == NULL){
		fprintf(stderr, "Malloc stopped working! It didn't save file_names variable in funcs.c file.");
	}

	while((dp = readdir(dir)) != NULL){
		if(!secretFiles && dp->d_name[0] == '.')
			continue;

		if(count >= capacity){
			capacity *= 2;

			char **temp = realloc(file_names, sizeof(char *) * capacity);
			if(temp == NULL){
				fprintf(stderr, "Realloc didn't work! Only the first %d file will be shown", count);
				break;
			}

			file_names = temp;
		}

		file_names[count] = strdup(dp->d_name);
		if(file_names[count] != NULL){
			printf("%s\n", file_names[count]);
			count++;
		}
	}
	closedir(dir);

	for(int i = 0; i < count; i++){
		free(file_names[i]);
	}
	free(file_names);
}
