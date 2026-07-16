#include "settings.h"

void list_directory(bool secretFiles){
	DIR *dir = opendir(".");
	struct dirent *dp;
	char **file_names = (char**)malloc(sizeof(char) * 64);
	int i = 0, max = 0;

	while(dp = readdir(dir)){
		if(secretFiles){
			file_names[i] = dp->d_name;
			printf("%s\n", file_names[i]);
			i++;
		}
		else{
			if(strncmp(file_names[i], ".", 0) != 0){
				file_names[i] = dp->d_name;
				printf("%s\n", file_names[i]);
				i++;
			}
		}
	}
	closedir(dir);
}
