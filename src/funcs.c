#include "../settings.h"

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
		size_t buffer = strlen(DATABASE) + strlen(target);
		char *db = malloc(buffer);
		snprintf(db, buffer, "./");
		snprintf(db, buffer, DATABASE);
		snprintf(db, buffer, target);
	
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

//This func is for extracting names from file paths for adding them to database
char *path_to_name(char *file_path){
	int i = 0, count = 0, i_last;
	char *name = malloc(sizeof(char) * FILE_NAME_LIMIT);

	while(file_path[i] != '\0'){
		if(file_path[i] == '/'){
			count++;
			i_last = i;
		}
		i++;
	}

	i = 0;
	i_last;
	while(file_path[i_last] != '\0'){
		name[i] = file_path[i_last];
		i_last++;
		i++;
	}
	name[i] = '\0';
	return name;
}

//This func is for creating paths as strings.
char *name_to_path(char *name, char *main_dir){
	size_t buffer = sizeof(char) * FILE_NAME_LIMIT;
	char *path = malloc(buffer);
	snprintf(path, buffer, "%s/%s", main_dir, name);
	
	return path;
}

void init_paths(){
	char *home_dir = getenv("HOME");
	if(home_dir == NULL){
		fprintf(stderr, "Home directory couldn't found!\n\n");
		free(file_name);
		free(search_style);
		free(hidden_files);
	}

	snprintf(DATABASE, 1024, "%s/.local/share/error_finder_database", home_dir);
	snprintf(FILE_DB, 1024, "%s/.local/share/error_finder_database/files", home_dir);
	snprintf(SETTINGS_FILE, 1024, "%s/.local/share/error_finder_database/settings.txt", home_dir);
	snprintf(LOG_DB, 1024, "%s/.local/share/error_finder_database/logs", home_dir);
}

void console_mode(){
	size_t buffer = sizeof(char) * FILE_NAME_LIMIT * 4;
	char *command = malloc(buffer);
	printf("Type 'exit' for closing the console mode.\n\n");

	size_t buffer2 = sizeof(char) * (FILE_NAME_LIMIT * 1);
	char *command_list_path = malloc(buffer2);
	snprintf(command_list_path, buffer2, "%s/console_commands.txt", DATABASE);
	FILE *command_list;
	FILE *settings_file;

	char *_dummy = malloc(sizeof(char) * 64);
	char *name;
	char *path;
	char **argv;
	bool exist;
	int number;

	struct args argi;

	while(1){
		exist = false;
		printf("\n> ");
		scanf(" %[^\n]", command);
		argi = console_parser(command);
		/*if(argi == NULL){//Idk how to do error control on structs but I'll figure it out on next update.
			fprintf(stderr, "Console parser is not working! Check it out.");
			break;
		}*/
		command_list = fopen(command_list_path, "r");
		for(int i = 0; fscanf(command_list, "%s\n", _dummy) != EOF; i++){
			if(!strcmp(_dummy, argi.argv[0])) exist = true;
			if(exist == true) break;
		}
		fclose(command_list);
		if(exist){
			if(!strcmp(argi.argv[0], "exit") || !strcmp(argi.argv[0], "quit")) break;

			else if(!strcmp(argi.argv[0], "df") || !strcmp(argi.argv[0], "default_file")){
				printf("Please choose the default file from database.\n\n");

				for(int i = 0; db_file_list[i]; i++){
					printf("(%d) %s\n", i + 1, db_file_list[i]);
				}

				if(strcmp(search_style, "name") == 0) {
					printf("File name: ");
					scanf("%s", name);
				}
				else if(strcmp(search_style, "number") == 0){
					printf("File number: ");
					scanf("%d", &number);
					name = db_file_list[number - 1];
				}

				path = name_to_path(name, FILE_DB);
				settings_file = fopen(path, "r");
				if(settings_file == NULL){
					printf("This file is not exist in database!");
					free(path);
					continue;
				}
				fclose(settings_file);
				settings_file = fopen(SETTINGS_FILE, "w");
				
				fprintf(settings_file, "File search style: %s\nDefault file: %s\nHidden Files: %s", search_style, path, hidden_files);
				fclose(settings_file);

				printf("Default file has been changed to '%s'", name);
			}

			else if(!strcmp(argi.argv[0], "ef") || !strcmp(argi.argv[0], "error_finder")){
				if(argi.argc > 1){
					int ch;
					printf("Default script file (%s) is going to work on these files. Are you okay with this?\n(y / n): ", file_name);
					getchar();
					ch = getchar();
				
					if(ch == 'y' || ch == 'Y'){
						char *worker = malloc(buffer);
						char *work;
						FILE *log;
						for(int i = 1; i < argi.argc; i++){
							char *name_helper = path_to_name(argi.argv[i]);
							work = name_to_path(name_helper, LOG_DB);
							free(name_helper);
							snprintf(worker, buffer, "%s %s >> %s-log.md 2>&1", file_name, argi.argv[i], work);
							char *log_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
							snprintf(log_file, buffer2, "%s-log.md", work);
							int status = system(worker);

							log = fopen(log_file, "r");
							if(log == NULL){
								printf("Error! Log file couldn't created! Please check '%s' directory permissions.", LOG_DB);
								free(work);
								free(log_file);
								break;
							}
							free(log_file);
							if(status == 0){
								printf("%s file has been checked and logged. File is all clean!", work);
							}
							else{
								fprintf(stderr, "%s file has been checked and logged. Some errors found on file. Please check the log file.", work);
							}
							free(work);
						}
						free(worker);
					}
					else{
							printf("\nProcess cancelled.\n");
							break;
					}
				}
				else{
					printf("Usage: ef <FILE_PATH>\n");
				}
			}
		}

		else if(!strcmp(argi.argv[0], "logs")){
			printf("\nLogs directory:\n\n");
			char **log_directory = parser(LOG_DB);
			for(int i = 0; log_directory[i] != NULL; i++){
				printf("(%d) %s\n", i + 1, log_directory[i]);
			}
			printf("\nTo inspect a log file please use 'logs -i' or 'logs --inspect'format!\n\n");

			if(argi.argc == 2){
				if(!strcmp(argi.argv[1], "-i") || !strcmp(argi.argv[1], "--inspect")){
					char *log_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
				
					if(!strcmp(search_style, "name")){
						printf("Name of the log file: ");
						scanf("%s", log_file);	
					}
					else if(!strcmp(search_style, "number")){
						int number;
						printf("Sequence number of the log file: ");
						scanf("%d", &number);
						strcpy(log_file, log_directory[number - 1]);
					}

					char *reader = malloc(buffer2);

					snprintf(reader, buffer2, "%s %s/%s", READER_APP, LOG_DB, log_file);
					system(reader);
			
					free(reader);
					free(log_file);
				}
			}
			FREE_LIST(log_directory);
		}

		else{
			system(command);
		}
	}
	
	FREE_LIST(argi.argv);
	free(command);
	free(_dummy);
	free(command_list_path);
}

struct args console_parser(char *command){
	struct args argi; //argi is like 'argument info'. It's much easier to remember this way. 
	argi.argc = 0;
	int count = 0;

	for(int i = 0; command[i] != '\0'; i++){
		if(command[i] == ' '){
			argi.argc++;
		}
	}
	argi.argc++;
	argi.argv = malloc(sizeof(char *) * (argi.argc + 1));

	for(int i = 0; i < argi.argc; i++){
		argi.argv[i] = malloc(sizeof(char) * FILE_NAME_LIMIT);
	}

	argi.argc = 0;

	for(int i = 0; command[i] != '\0'; i++){
		if(command[i] != ' '){
			argi.argv[argi.argc][count] = command[i] ;
			count++;
		}
		else{
			argi.argv[argi.argc][count] = '\0';
			argi.argc++;
			count = 0;
		}
	}

	argi.argv[argi.argc][count] = '\0';
	argi.argc++;

	argi.argv[argi.argc] = NULL;

	return argi;
}
