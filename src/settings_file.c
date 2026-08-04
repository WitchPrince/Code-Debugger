#include "../settings.h"

int settings_menu(){
	FILE *settings_file = fopen(SETTINGS_FILE, "r");
	fscanf(settings_file, "File search style: %[^\n]\nDefault file: %[^\n]\nHidden Files: %[^\n]\n", search_style, file_name, hidden_files);
	int decision, main_decision;
	fclose(settings_file);

	while(1){
		printf("\n(1) File search format\n(2) Change default script file\n(3) Add a script file to database\n(4) Delete a script file from database\n(5) Show/Hide hidden files\n(6) Reset Settings File\n(7) Exit\nDecision: ");
		scanf("%d", &main_decision);
		printf("\n==================================\n");
		
		if(main_decision == 1){
			printf("How do you want to select files?\n(1) By Name\n(2) By Order Number\n(3) Exit\nDecision: ");
			scanf("%d", &decision);
			printf("\n==================================\n");
				
			if(decision == 1){
				settings_file = fopen(SETTINGS_FILE, "w");
				if(settings_file == NULL){
					fprintf(stderr, "Settings file couldn't opened.\n");
					return ERROR;
				}
				fprintf(settings_file, "File search style: name\nDefault file: %s\nHidden Files: %s\n", file_name, hidden_files);

				fclose(settings_file);
				printf("\nFrom now on files will be select from their exact name.\n");
				return SUCCESS;
			}

			else if(decision == 2){
				settings_file = fopen(SETTINGS_FILE, "w");
				if(settings_file == NULL){
					fprintf(stderr, "Settings file couldn't opened.\n");
					return ERROR;
				}
				fprintf(settings_file, "File search style: number\nDefault file: %s", file_name);

				fclose(settings_file);
				printf("\nFrom now on files will be select from their order number.\n");
				return SUCCESS;
			}

			else{
				if(decision != 3){
					fprintf(stderr, "Can't you see the numbers? There's not any choices like that idiot.");
					printf("\n==================================\n");
				}
			}
		}

		else if(main_decision == 2){
			FILE *temp;
			FILE *check;

			char *temp_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
			int limit = FILE_NAME_LIMIT;

			printf("File location: ");
			getchar();
			scanf("%1023s", temp_file);

			check = fopen(temp_file, "r");
			if(check == NULL){
				printf("File doesn't exist! If you sure that file exist, please check it's reading permissions.\n\n");
				free(temp_file);
				return -1;
			}
			fclose(check);

			settings_file = fopen(SETTINGS_FILE, "w");
			fprintf(settings_file, "File search style: %s\nDefault file: %s\nHidden Files: %s\n",search_style, temp_file, hidden_files);
			fclose(settings_file);

			printf("\nDo you want to add this file to '/usr/local/share/error_finder_database/files/' path for quick use for next time?\n(1/0): ");
			scanf("%d", &limit); //I know this isn't appropriate way but I didn't wanted to decline another integer just for this.
			
			if(limit == 0){
				free(temp_file);
				return SUCCESS;
			}

			else if(limit == 1){
				char *raw_file_name = path_to_name(temp_file);
				size_t buffer_nfp = sizeof(char) * FILE_NAME_LIMIT;
				char *new_file_path = malloc(buffer_nfp);
				snprintf(new_file_path, buffer_nfp, "%s/%s", FILE_DB, raw_file_name);
				free(raw_file_name);

				if(file_copy(temp_file, new_file_path) == -1){			
					free(new_file_path);

					size_t buffer_size = sizeof(char) * (FILE_NAME_LIMIT * 2 + 10);
					char *command = malloc(buffer_size);
					snprintf(command, buffer_size, "sudo cp %s %s", temp_file, FILE_DB);
					system(command);
					free(command);
					free(temp_file);
					printf("Success! File copied into database folder!\n\n");
					return SUCCESS;
				}
			}

			else{
				printf("Only numbers buddy. Only number. 1 for yes, 0 for no. Only numbers please.");
				free(temp_file);
				return ERROR;
			}
		}

		else if(main_decision == 3){
			char *path = malloc(sizeof(char) * FILE_NAME_LIMIT);
			printf("File path: ");
			scanf("%s", path);
			int error = file_copy(path, FILE_DB);
			if(error == -1){
				size_t buffer = sizeof(char) * FILE_NAME_LIMIT * 2 + 10;
				char *command = malloc(buffer);
				snprintf(command, buffer, "sudo cp %s %s", path, FILE_DB);
				system(command);
				free(command);
			}
			free(path);
			printf("Copy success!");
			printf("\n==================================\n");
		}

		else if(main_decision == 4){
			printf("Which file do you want to delete?\n\n");

			char **script_list = parser(FILE_DB);
			for(int i = 0; script_list[i] != NULL; i++){
				printf("(%d) %s\n", i + 1, script_list[i]);
			}
			
			if(strcmp(search_style, "name") == 0){
				char *wanted = malloc(sizeof(char) * FILE_NAME_LIMIT);
				printf("File name: ");
				scanf("%1023s", wanted);
				int check = 0;
				for(int i = 0; script_list[i] != NULL; i++){
					if(strcmp(wanted, script_list[i]) == 0){
						check = 1;
					}
					free(script_list[i]);
				}
				free(script_list);

				if(check){
					char *wanted_path = name_to_path(wanted, FILE_DB);
					remove(wanted_path);
					printf("%s file has been deleted!", wanted);
					free(wanted_path);
				}
				else{
					printf("There's not any file named %s\nPlease check for typos!\n\n", wanted);
				}
				free(wanted);
			}

			else if(strcmp(search_style, "number") == 0){
				int script_no;
				printf("File number: ");
				scanf("%d", &script_no);

				if(script_list[script_no - 1] != NULL){
					char *wanted = name_to_path(script_list[script_no - 1], FILE_DB);
					remove(wanted);
					printf("%s file has been deleted!\n\n", wanted);
					free(wanted);
				}
				else{
					printf("Count the numbers again...");
				}

				for(int i = 0; script_list[i] != NULL; i++)
					free(script_list[i]);
				free(script_list);
			}

			else{
				fprintf(stderr, "Settings files has been corrupted. Please fix it from 'settings->Reset Settings file' menu.");
				for(int i = 0; script_list[i] != NULL; i++) 
					free(script_list[i]);
				free(script_list);
			}
			printf("\n==================================\n");
		}

		else if(main_decision == 5){
			printf("Do you want to see secret files?\n(1/0): ");
			int decision;
			scanf("%d", &decision);

			char *choice = decision ? "yes" : "no";

			FILE *settings_file = fopen(SETTINGS_FILE, "w");
			if(settings_file == NULL){
				fprintf(stderr, "Settings file couldn't opened! Please run make command again.");
				return ERROR;
			}

			else{
				fprintf(settings_file, "File search style: %s\nDefault file: %s\nHidden Files: %s\n",search_style, file_name, choice);
			}
			fclose(settings_file);

			printf("Secret files settings has been updated!");
			printf("\n==================================\n");		
		}

		else if(main_decision == 6){
			remove(SETTINGS_FILE);
			FILE *fptr = fopen(SETTINGS_FILE, "w");
			if(fptr == NULL){
				fprintf(stderr, "Reset failed! File couldn't created again! Please check path permissions.");
				return ERROR;
			}

			char *home_dir = getenv("HOME");
			char *default_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
			snprintf(default_file, sizeof(char) * FILE_NAME_LIMIT, "%s/checkpatch.pl", home_dir);
			fprintf(fptr, "File search style: number\nDefault file: %s\nHidden Files: no\n", default_file);
			
			free(default_file);
			fclose(fptr);

			printf("Reset success!");
			
			printf("\n==================================\n");
		}

		else if(main_decision == 7){
			printf("\n==================================\n");
			return SUCCESS;
		}
	}
}
