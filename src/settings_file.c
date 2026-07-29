#include "../settings.h"

int settings_menu(){
	FILE *settings_file = NULL;
	int decision, main_decision;
	while(1){
		printf("\n(1) File search format\n(2) Change default script file\n(3) Add a script file to database\n(4) Delete a script file from database\n(5) Exit\nDecision: ");
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
				fprintf(settings_file, "File search style: name\nDefault file: %s\n", file_name);

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
			printf("This page is still on development.");
			printf("\n==================================\n");
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
			printf("\n==================================\n");
			return SUCCESS;
		}
	}
}
