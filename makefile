cprep : cprep.o
	gcc cprep.o -o cprep

cprep.o : cprep.c
	gcc cprep.c -c

install : cprep
	sudo cp cprep /usr/local/bin/cprep

uninstall : clear
	sudo rm /usr/local/bin/cprep

clear : cprep_distrib_vers/ cprep_source_code_vers/ cprep
	rm cprep.o cprep cprep_distrib_vers/* cprep_source_code_vers/* *.zip
	rmdir cprep_distrib_vers cprep_source_code_vers

cprep_distrib_vers/ : 
	mkdir cprep_distrib_vers
	touch cprep_distrib_vers/None
	
cprep_source_code_vers/ : 
	mkdir cprep_source_code_vers
	touch cprep_source_code_vers/None

update : cprep cprep.o cprep_distrib_vers/ cprep_source_code_vers/
	rm cprep_distrib_vers/*
	rm cprep_source_code_vers/*
	cp cprep.o cprep_distrib_vers/cprep.o
	cp cprep.c cprep_source_code_vers/cprep.c
	cp config.h cprep_source_code_vers/config.h
	cp readme.md cprep_distrib_vers/readme.md
	cp readme.md cprep_source_code_vers/readme.md
	cp makefile_distrib_vers cprep_distrib_vers/makefile
	cp makefile_source_code_vers cprep_source_code_vers/makefile
	tar -czf cprep_distrib_vers.zip cprep_distrib_vers/
	cp cprep_distrib_vers.zip cprep_source_code_vers/cprep_distrib_vers.zip
	tar -czf cprep_source_code_vers.zip cprep_source_code_vers/

gedit : 
	gedit makefile *.h *.c &

