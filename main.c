#include "settings.h"

bool secretFiles = false;
char *file_name = NULL;
char *search_style = NULL;

int main(int argc, char *argv[]){
	file_name = malloc(sizeof(char) * FILE_NAME_LIMIT);
	search_style = malloc(sizeof(char) * 8);

	FILE *settings_file = fopen(SETTINGS_FILE, "r");
	R_SETTINGS(search_style, file_name);
	fclose(settings_file);

	char db_path[sizeof(DATABASE) + 64];
	snprintf(db_path, sizeof(db_path), DATABASE"%s", "checkpatch.pl"); //Selected file is "checkpatch.pl" by default. But I'll add a menu for choosing every file you want.

	if(argc > 1){
		if(strcmp(argv[1], "-a") == 0) secretFiles = true;
	}

	char **list = parser(".");
	int decision_1 = 1, decision_file;

	while(decision_1 != 4){
		printf("(1) List files\n(2) Use a script file\n(3) Settings\n(4) Exit\nDecision: ");
		if(scanf("%d", &decision_1) != 1){
			fprintf(stderr, "Only numbers please.");
			CLEAR_BEFORE_EXIT;
			exit(1);
		}
		printf("\n==================================\n");

		if(decision_1 == 1){
			for(int i = 0; list[i] != NULL; i++){
				printf("(%d) %s\n", i + 1, list[i]);
			}
			printf("\n==================================\n");
		}

		else if(decision_1 == 2){
			printf("\n==================================\n");
			run_script(list);
		}

		else if(decision_1 == 3){
			printf("\n==================================\n");
			settings_menu();
		}

		else{
			if(decision_1 != 4) {
				printf("Can't you see the numbers?\nThere's not any choice like that idiot.");
				printf("\n==================================\n");
			}
		}
	}

	free(file_name);
	free(search_style);
	CLEAR_BEFORE_EXIT;
	return 0;
}
