#I'm too lazy for writing a decent makefile so we're gonna use it like this for a while.

DB_DIR	=	/usr/local/share/error_finder_database
FILE_DB_DIR	=	/usr/local/share/error_finder_database/files
SRCS	=	main.c	funcs.c	src/settings_file.c	src/run_script.c	settings.h	-o	ef

install:
	@gcc	$(SRCS)
	@sudo	cp	ef	/usr/local/bin/
	@echo	"Application has been created!"
	@sudo	mkdir	-p	$(DB_DIR)
	@sudo	mkdir	-p	$(FILE_DB_DIR)
	@sudo	chmod	755	$(DB_DIR)
	@sudo	chmod	-R	755	$(FILE_DB_DIR)
	@sudo	touch	$(DB_DIR)/settings.txt
	@sudo	chmod	666	$(DB_DIR)/settings.txt
	@echo	-e	"File search style: name\nDefault file: /usr/local/share/error_finder_database/checkpatch.pl\nHidden Files: 0\n"	|	sudo	tee	$(DB_DIR)/settings.txt

clean:
	@sudo rm -f ef;
	@sudo rm -f /usr/local/bin/ef;
	@echo	"Application removed!"
	@sudo	rm	-rf	$(DB_DIR)
	@echo	"Database cleared!"
