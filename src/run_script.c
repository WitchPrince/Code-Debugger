#include "../settings.h"

void run_script(char **list){
	int decision_file;
	char *run_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
	
	if(run_file == NULL){
		fprintf(stderr, "Memory couldn't allocated!");
		printf("\n==================================\n");
		return;
	}

	for(int i = 0; list[i] != NULL; i++){
		printf("(%d) %s\n", i + 1, list[i]);
	}
	printf("\nWhich file you want to use from current directory?\n");
		
	if(strcmp(search_style, "number") == 0){
		printf("Please enter number: ");
		if(scanf("%d", &decision_file) != 1){
			fprintf(stderr, "Only numbers please.\nYou can change this option to 'select with file-names'from settings.\n");
			return;
		}
	
		snprintf(run_file, FILE_NAME_LIMIT, "./%s", list[decision_file - 1]);
		system(run_file);	
		free(run_file);
		printf("\n==================================\n");
	}

	else if(strcmp(search_style, "name") == 0){
		char *choosed_file = malloc(sizeof(char) * FILE_NAME_LIMIT);
		if(choosed_file == NULL){
			fprintf(stderr, "Memory couldn't allocated!");
			printf("\n==================================\n");
			free(run_file);
			return;
		}

		printf("Please enter file name: ");
		scanf("%s", choosed_file);
	
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
			snprintf(run_file, FILE_NAME_LIMIT, "./%s", choosed_file);
			system(run_file);
		}

		else{
			fprintf(stderr, "Please check up if there's any typo. Because there's not any file like that.\n");
		}
	free(choosed_file);
	free(run_file);
	}

	else{
		fprintf(stderr, "Check settings.txt file from '~/.local/share/error_finder_database/settings.txt', because it seems it's corrupted. You can go to settings menu and re-configure it.\n");
		free(run_file);
	}
}
