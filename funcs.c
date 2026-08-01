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

int file_copy(char *src_file, char *dest_path){
	FILE *src = fopen(src_file, "rb");

	if(src == NULL){
		fprintf(stderr, "Source file couldn't opened. Now trying it wia 'sudo cp' command now.\n\n");
		return -1;
	}

	FILE *dest = fopen(dest_path, "wb");
	if(dest == NULL){
		fprintf(stderr, "Destination file couldn't created. Trying it wia 'sudo cp' command now.\n\n");
		fclose(src);
		return -1;
	}

	char buffer[4096];
	size_t bytes_read;

	while((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0){
		size_t bytes_written = fwrite(buffer, 1, sizeof(buffer), dest);

		if(bytes_written != bytes_read){
			fprintf(stderr, "There has been a mistake while writing to the destination file!");
			fclose(src);
			fclose(dest);
			return -1;
		}
	}

	fclose(src);
	fclose(dest);
	
	return 0;
}

char *path_to_name(char *file_path){
	int i = 0, count = 0;
	char *file_name = malloc(sizeof(char) * FILE_NAME_LIMIT);

	while(file_path[i] != '\0'){
		if(file_path[i] == '/'){
			count++;
		}
		i++;
	}

	i = 0;
	while(file_path[count] != '\0'){
		file_name[i] = file_path[count];
		i++;
		count++;
	}
	file_name[i + 1] = '\0';
	return file_name;
}
