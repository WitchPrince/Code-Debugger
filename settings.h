#ifndef SETTINGS_H
#define SETTINGS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <ncurses.h> I decided TUI is not that necessary so I'll add it as a plugin or idk maybe as an another project..? Anyway it's all on cli from now on. 

//Macros
#define ERROR 0
#define SUCCESS 1
#define FILE_NAME_LIMIT 128
#define CLEAR_BEFORE_EXIT for(int i = 0; list[i] != NULL; i++) free(list[i]);\
	free(list);

//Filepaths
#define DATABASE "/usr/local/share/error_finder_database"
#define KERNEL	"/usr/local/share/error_finder_database/checkpatch.pl"

//Global Variables
extern bool secretFiles;

//Functions
char **parser(char *target); 
char *default_file(char *file_name);

#endif
