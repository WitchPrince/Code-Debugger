#I'm too lazy for writing a decent makefile so we're gonna use it like this for a while.

install:
	@gcc	main.c	funcs.c	settings.h	-o	ef
	@sudo	cp	ef	/usr/local/bin/
	@echo	"Application has been created!"
	@sudo	mkdir	-p	/usr/local/share/error_finder_database	/usr/local/share/error_finder_database

clean:
	@sudo rm -f ef;
	@sudo rm -f /usr/local/bin/ef;
	@echo	"Application removed!"
	@sudo	rm	-rf	/usr/local/share/kernel_error_finder_database
	@echo	"Database cleared!"
