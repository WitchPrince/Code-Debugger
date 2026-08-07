#include "settings.h"

bool secretFiles = false;
char *hidden_files = NULL;
char *file_name = NULL;
char *search_style = NULL;

char **db_file_list;
char DATABASE[1024];
char FILE_DB[1024];
char LOG_DB[1024];
char SETTINGS_FILE[1024];

int main(int argc, char *argv[]){
	file_name = malloc(sizeof(char) * FILE_NAME_LIMIT);
	search_style = malloc(sizeof(char) * 8);
	hidden_files = malloc(sizeof(char) * 4);

	init_paths();

	FILE *settings_file = fopen(SETTINGS_FILE, "r");
	fscanf(settings_file, "File search style: %[^\n]\nDefault file: %[^\n]\nHidden Files: %[^\n]\n", search_style, file_name, hidden_files);
	fclose(settings_file);

	db_file_list = parser(FILE_DB);

	if(argc > 1){
		int run = 0;
		int console = 0;
		for(int i = 1; i < argc; i++){
			if(strcmp(argv[i], "-a") == 0){ 
				secretFiles = true;
				run = 1;
			}
			if(!strcmp(argv[i], "-cm") || !strcmp(argv[1], "console-mode")){
				run = 1;
				console = 1;
			} 
		}

		if(run){
			if(console){
				console_mode();
				
				free(hidden_files);
				free(file_name);
				free(search_style);
				FREE_LIST(db_file_list);
				
				exit(1);
			}	
		}

		else{
			printf("There's probably a typo. Please check your command again.");
			
			free(hidden_files);
			free(file_name);
			free(search_style);
			FREE_LIST(db_file_list);
			
			exit(1);
		}
	}

	char **list = parser(".");
	int decision_1 = 1, decision_file;

	while(decision_1 != 5){
		printf("(1) List files\n(2) Use a script file\n(3) Settings\n(4) Console Mode\n(5) Exit\nDecision: ");
		if(scanf("%d", &decision_1) != 1){
			fprintf(stderr, "Only numbers please.\n");
			continue;
		}
		printf("\n==================================\n");

		if(decision_1 == 1){
			list = parser(".");
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
			
			settings_file = fopen(SETTINGS_FILE, "r");
			fscanf(settings_file, "File search style: %[^\n]\nDefault file: %[^\n]\nHidden Files: %[^\n]\n", search_style, file_name, hidden_files);
			fclose(settings_file);

			for(int i = 0; db_file_list[i]; i++) free(db_file_list[i]);
			free(db_file_list);
			db_file_list = parser(FILE_DB);
		}

		else if(decision_1 == 4){
			console_mode();

			settings_file = fopen(SETTINGS_FILE, "r");
			fscanf(settings_file, "File search style: %[^\n]\nDefault file: %[^\n]\nHidden Files: %[^\n]\n", search_style, file_name, hidden_files);
			fclose(settings_file);
			
			printf("\n==================================\n");
		}
		
		else{
			if(decision_1 != 5) {
				printf("Can't you see the numbers?\nThere's not any choice like that idiot.");
				printf("\n==================================\n");
			}
		}

	}

	free(hidden_files);
	free(file_name);
	free(search_style);
	FREE_LIST(list);
	FREE_LIST(db_file_list);
	return 0;
}
