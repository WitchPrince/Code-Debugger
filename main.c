#include "settings.h"

bool secretFiles = false;

int main(int argc, char *argv[]){
	char db_path[sizeof(DATABASE) + 64];
	snprintf(db_path, sizeof(db_path), DATABASE"%s", "checkpatch.pl"); //Selected file is "checkpatch.pl" by default. But I'll add a menu for choosing every file you want.

	if(argc > 1){
		if(strcmp(argv[1], "-a") == 0) secretFiles = true;
	}

	char **list = parser(".");

	
	int decision_1 = 1, decision_file;


	while(decision_1 != 3){
	
		printf("(1) List files\n(2) Use a script file\n(3) Exit\nDecision: ");
		if(scanf("%d", &decision_1) != 1){
			fprintf(stderr, "Only numbers please.");
			CLEAR_BEFORE_EXIT;
			exit(1);
		}
		printf("\n");

		if(decision_1 == 1){
			for(int i = 0; list[i] != NULL; i++){
				printf("(%d) %s\n", i + 1, list[i]);
			}
			printf("\n==================================\n");
		}

		else if(decision_1 == 2){
			for(int i = 0; list[i] != NULL; i++){
				printf("(%d) %s\n", i + 1, list[i]);
			}
			printf("\nWhich file you want to use from database?\nDecision: ");
	
			if(scanf("%d", &decision_file) != 1){
				fprintf(stderr, "Only numbers please.");
				CLEAR_BEFORE_EXIT;
				exit(1);
			}

			char *file_name = malloc(sizeof(char) * FILE_NAME_LIMIT);
			if(file_name == NULL){
				fprintf(stderr, "Memory couldn't allocated!");
				printf("\n==================================\n");
				CLEAR_BEFORE_EXIT;
				exit(1);
			}
			snprintf(file_name, FILE_NAME_LIMIT, "./%s", list[decision_file - 1]);
			system(file_name);
			free(file_name);
			printf("\n==================================\n");
		}

		else{
			if(decision_1 != 3) printf("Can't you see the numbers?\nThere's not any choice like that idiot.");
			printf("\n==================================\n");
		}
	}

	CLEAR_BEFORE_EXIT;
	return 0;
}
