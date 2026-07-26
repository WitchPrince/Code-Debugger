#include "../settings.h"

void run_script(char **list){
	int decision_file;
	FILE *settings_file = fopen(SETTINGS_FILE, "r");

	for(int i = 0; list[i] != NULL; i++){
		printf("(%d) %s\n", i + 1, list[i]);
	}
	printf("\nWhich file you want to use from database?\nDecision: ");
		
	if(strcmp(search_style, "number") == 0){
		if(scanf("%d", &decision_file) != 1){
			fprintf(stderr, "Only numbers please.\nYou can change this option to 'select with file-names'from settings.");
			return;
		}
	
		char *file_name = malloc(sizeof(char) * FILE_NAME_LIMIT);
		if(file_name == NULL){
			fprintf(stderr, "Memory couldn't allocated!");
			printf("\n==================================\n");
			return;
		}
	
		snprintf(file_name, FILE_NAME_LIMIT, "./%s", list[decision_file - 1]);
		system(file_name);	
		free(file_name);
		printf("\n==================================\n");
	}

	else if(strcmp(search_style, "name") == 0){
		char *choosed_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
		if(scanf("%s", choosed_file) != 1){
			bool isFileExist = false;
			int i = 0;
			while(list[i] != NULL){
				if(strcmp(choosed_file, list[i]) == 0){
					isFileExist = true;
					break;
				}
				else i++;
			}

			if(isFileExist){
				snprintf(file_name, FILE_NAME_LIMIT, "./%s", choosed_file);
				system(file_name);
			}
		}

		else{
			fprintf(stderr, "Please check up if there's any typo. Because there's not any file like that.");
			free(choosed_file);
			return;
		}
	}

	else{
		fprintf(stderr, "Check settings.txt file from '/usr/local/share/error_finder_database/settings.txt', because it seems it's corrupted. You can go to settings menu and re-configure it.\n");
		return;
	}
}
