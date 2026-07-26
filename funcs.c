#include "settings.h"

char **parser(char *target){
	DIR *dir;
	if(target[0] == '.'){
		dir = opendir(".");
		if(dir == NULL){
			fprintf(stderr, "Folder couldn't opened!");
			exit(1);
		}
	}

	else{
		char *db = malloc(strlen(DATABASE) + strlen(target));
		snprintf(db, sizeof(db), "./");
		snprintf(db, sizeof(db), DATABASE);
		snprintf(db, sizeof(db), target);
	
		dir = opendir(db);
		if(dir == NULL){
			fprintf(stderr, "Folder couldn't opened!");
			free(db);
			exit(1);
		}
	}
	struct dirent *dp;
	int count = 0, capacity = 64;
	
	char **file_names = malloc(sizeof(char*) * capacity);
	if(file_names == NULL){
		fprintf(stderr, "Malloc stopped working! It didn't save file_names variable in funcs.c file.");
		exit(1);
	}

	while((dp = readdir(dir)) != NULL){

		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;

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
		
		if(file_names[count] != NULL) count++;
	}
	closedir(dir);

	file_names[count] = NULL;

	return file_names;
}
