#ifndef SETTINGS_H
#define SETTINGS_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses.h> 

//Macros
#define ERROR 0
#define SUCCESS 1

//Filepaths
#define DATABASE "/usr/local/share/error_finder_database/"
#define KERNEL	"/usr/local/share/error_finder_database/checkpatch.pl"

//Global Variables
extern bool secretFiles;

//Functions
void list_directory(); 

#endif
