#I'm too lazy for writing a decent makefile so we're gonna use it like this for a while.

DB_DIR	=	~/.local/share/error_finder_database
FILE_DB_DIR	=	~/.local/share/error_finder_database/files
LOG_DB_DIR	=	~/.local/share/error_finder_database/logs
SRCS	=	main.c	src/funcs.c	src/settings_file.c	src/run_script.c	settings.h	-o	ef

install:
	@mkdir	-p	$(DB_DIR)
	@mkdir	-p	$(FILE_DB_DIR)
	@mkdir	-p	$(LOG_DB_DIR)
	@gcc	$(SRCS)
	@cp	ef	~/.local/bin/
	@cp	src/console_commands.txt	~/.local/share/error_finder_database/
	@echo	"Application has been created!"
	@echo	-e	"File search style: number\nDefault file: ~/.local/share/error_finder_database/files/checkpatch.pl\nHidden Files: no\n" > $(DB_DIR)/settings.txt

clean:
	@rm -f ef;
	@rm -f ~/.local/bin/ef;
	@echo	"Application removed!"
	@rm	-rf	$(DB_DIR)
	@echo	"Database cleared!"
