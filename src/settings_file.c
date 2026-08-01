#include "../settings.h"

int settings_menu(){
	FILE *settings_file = fopen(SETTINGS_FILE, "r");
	fscanf(settings_file, "File search style: %[^\n]\nDefault file: %[^\n]\nHidden Files: %[^\n]\n", search_style, file_name, hidden_files);
	int decision, main_decision;
	fclose(settings_file);

	while(1){
		printf("\n(1) File search format\n(2) Change default script file\n(3) Add a script file to database\n(4) Delete a script file from database\n(5) Show/Hide hidden files\n(6) Exit\nDecision: ");
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

		if(main_decision == 2){
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

		if(main_decision == 3){
			printf("This page is still on development.");
			printf("\n==================================\n");
		}

		if(main_decision == 4){
			printf("This page is still on development.");
			printf("\n==================================\n");
		}

		if(main_decision == 5){
			printf("This page is still on development.");
			printf("\n==================================\n");		
		}

		if(main_decision == 6){
			printf("\n==================================\n");
			return SUCCESS;
		}
	}
}
