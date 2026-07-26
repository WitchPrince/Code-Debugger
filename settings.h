#ifndef SETTINGS_H
#define SETTINGS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <ncurses.h> I decided TUI is not that necessary so I'll add it as a plugin or idk maybe as an another project..? Anyway it's all on cli from now on. 

/*Some file syntax templates

  (1) SETTINGS_FILE:
  File search style: %s
  Default file: %s

*/
//Macros
#define ERROR 1
#define SUCCESS 0
#define FILE_NAME_LIMIT 128
#define CLEAR_BEFORE_EXIT for(int i = 0; list[i] != NULL; i++) free(list[i]);\
	free(list);

#define R_SETTINGS(search_style, file_name) fscanf(settings_file, "File search style: %" STR(FILE_NAME_LIMIT) "[\n]\nDefault file: %[^\n]\n", search_style, file_name);
#define W_SETTINGS(search_style, file_name) fprintf(settings_file, "File search style: %s\nDefault file: %s\n", file_name, search_style);

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

//Filepaths
#define DATABASE "/usr/local/share/error_finder_database"
#define KERNEL	"/usr/local/share/error_finder_database/checkpatch.pl"
#define SETTINGS_FILE "/usr/local/share/error_finder_database/settings.txt"

//Global Variables
extern bool secretFiles;
extern char *file_name;
extern char *search_style;

//Functions
char **parser(char *target); 
int settings_menu();
void run_script(char **list);

#endif
