#include "settings.h"

bool secretFiles = true;

int main(){
	char db_path[sizeof(DATABASE) + 64];
	snprintf(db_path, sizeof(db_path), DATABASE"%s", "checkpatch.pl"); //Selected file is "checkpatch.pl" by default. But I'll add a menu for choosing every file you want.

	list_directory();

	return 0;
}
