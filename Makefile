#I'm too lazy for writing a decent makefile so we're gonna use it like this for a while.

DB_DIR	=	~/.local/share/error_finder_database
FILE_DB_DIR	=	~/.local/share/error_finder_database/files
SRCS	=	main.c	funcs.c	src/settings_file.c	src/run_script.c	settings.h	-o	ef

install:
	@gcc	$(SRCS)
	@cp	ef	~/.local/bin/
	@echo	"Application has been created!"
	@mkdir	-p	$(DB_DIR)
	@mkdir	-p	$(FILE_DB_DIR)
	@touch	$(DB_DIR)/settings.txt
	@echo	-e	"File search style: number\nDefault file: ~/.local/share/error_finder_database/files/checkpatch.pl\nHidden Files: 0\n" >> $(DB_DIR)/settings.txt

clean:
	@rm -f ef;
	@rm -f ~/.local/bin/ef;
	@echo	"Application removed!"
	@rm	-rf	$(DB_DIR)
	@echo	"Database cleared!"
