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
#define CLEAR_BEFORE_EXIT(list) for(int i = 0; list[i] != NULL; i++) {free(list[i]);\
					free(db_file_list[i]);}\
				free(list); free(db_file_list);

//Filepaths
extern char DATABASE[1024];		//Path: ~/.local/share/error_finder_database/
extern char FILE_DB[1024];		//Path: ~/.local/share/error_finder_database/files/
extern char SETTINGS_FILE[1024];	//Path: ~/.local/share/error_finder_database/settings.txt
extern char **db_file_list;

//Global Variables
extern bool secretFiles;
extern char *file_name;
extern char *search_style;
extern char *hidden_files;

//Functions
char **parser(char *target); 
char *path_to_name(char *name);
char *name_to_path(char *name);

int settings_menu();
int file_copy(char *src_file, char *dest_path);

void init_paths();
void run_script(char **list);
void console_mode();

#endif
