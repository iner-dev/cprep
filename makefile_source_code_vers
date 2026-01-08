cprep : cprep.o
	gcc cprep.o -o cprep

cprep.o : cprep.c
	gcc cprep.c -c

install : cprep
	sudo cp cprep /usr/local/bin/cprep

uninstall : clear
	sudo rm /usr/local/bin/cprep

clear : 
	rm cprep.o cprep
