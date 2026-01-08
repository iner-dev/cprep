cprep : cprep.o
	gcc cprep.o -o cprep

install : cprep
	sudo cp cprep /usr/local/bin/cprep

uninstall : clear
	sudo rm /usr/local/bin/cprep

clear : 
	rm cprep
