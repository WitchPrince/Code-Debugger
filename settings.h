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
  Hidden Files: %s

*/
//Macros
#define ERROR 1
#define SUCCESS 0
#define FILE_NAME_LIMIT 1024
#define CLEAR_BEFORE_EXIT for(int i = 0; list[i] != NULL; i++) free(list[i]);\
	free(list);

//Filepaths
#define DATABASE "/usr/local/share/error_finder_database"
#define FILE_DB "/usr/local/share/error_finder_database/files"
#define KERNEL	"/usr/local/share/error_finder_database/checkpatch.pl"
#define SETTINGS_FILE "/usr/local/share/error_finder_database/settings.txt"

//Global Variables
extern bool secretFiles;
extern char *file_name;
extern char *search_style;
extern char *hidden_files;

//Functions
char **parser(char *target); 
int settings_menu();
int file_copy(char *src_file, char *dest_path);
void run_script(char **list);
char *path_to_name(char *file_path);

#endif
