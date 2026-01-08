#include <stdio.h>
#include <string.h>
#include "config.h"

#ifndef MAX_FILE_NAME
#define MAX_FILE_NAME 64
#endif

#ifndef DEFAULT_MAIN_NAME
#define DEFAULT_MAIN_NAME "main.c"
#endif

#ifndef DEFAULT_EXEC_NAME
#define DEFAULT_EXEC_NAME "exec"
#endif

char* to_maj(char*,const char*);
void prep(const char*);
void make_main(const char* main_name,const char* exec_name,FILE* makefile);

int main(int argc,char** argv){
	int i,j,len;
	char main_file_name[MAX_FILE_NAME] = DEFAULT_MAIN_NAME;
	char exec_name[MAX_FILE_NAME] = DEFAULT_EXEC_NAME;
	int make_makefile = 0,make_mainfile = 0,verbose=0, other_rules = 0;
	char* arg;
	FILE* makefile = NULL;
	for(i=1;i<argc;i++){
		arg = argv[i]; 
		if(arg[0]=='-'){
			len = strlen(arg);
			for(j=1;j<len;j++){
				switch (arg[j]){
					case 'v':
						verbose = 1;
						break;
					case 'r':
						if(other_rules==0) other_rules = 1;
						break;
					case 'm':
						if(!make_makefile){
							makefile = fopen("makefile", "a+");
							make_makefile = 1;
							if(verbose) printf("makefile opened.\n");
						}
						break;
					case 'M':
						if(!make_makefile){
							makefile = fopen("Makefile", "a+");
							make_makefile = 1;
							if(verbose) printf("Makefile opened.\n");
						}
						break;
					case 'a':
						if(i+1<argc){
							strcpy(main_file_name,argv[i+1]);
							i++;
						}
					case 'A':
						if(make_mainfile==0) make_mainfile = 1;
						break;
					case 'e':
						if(i+1<argc){
							strcpy(exec_name,argv[i+1]);
							i++;
						}
						if(make_mainfile==0) make_mainfile = 1;
						break;
				}
			}
			if(other_rules==1 && make_makefile== 1) {
				#ifdef ALL_RULE
				fprintf(makefile, "all : %s\n\n",exec_name);
				#endif
				#ifdef CLEAR_RULE
				fprintf(makefile, "clear :\n	rm *.o %s\n\n",exec_name);
				#endif
				#ifdef GEDIT_RULE
				fprintf(makefile, "gedit : \n	gedit makefile *.h *.c &\n\n");
				#endif
				#ifdef RUN_RULE
				fprintf(makefile, "run : %s\n	.\\%s\n\n",exec_name,exec_name);
				#endif
				#ifdef ZIP_RULE
				fprintf(makefile, "zip : \n	tar -czvf prog.zip *\n\n");
				#endif
				if(verbose) printf("Other rules written.\n");
				other_rules++;
			}
			if(make_mainfile==1) {
				make_main(main_file_name,exec_name,makefile);
				make_mainfile++;
				if(verbose) printf("main file written.\n");
				if(verbose && make_makefile) printf("makefile updated for %s.\n",main_file_name);
			}
		}else{
			prep(arg);
			if(verbose) printf("%s files written.\n",arg);
			if (make_makefile && makefile != NULL) {
                		fprintf(makefile, "\n%s.o : %s.h %s.c\n\tgcc %s.c -c\n", 
                        arg, arg, arg, arg);
                        	if(verbose) printf("makefile updated for %s.\n",arg);
            		}
		}
	}
	if(make_makefile) fclose(makefile);
	if(verbose) printf("all files written.\n");
}

void make_main(const char* main_name,const char* exec_name,FILE* makefile){
	FILE* main_file = fopen(main_name,"w");
	fprintf(main_file,"\n\nint main(){\n	// code here\n}");
	fclose(main_file);
	if(makefile!=NULL){
		fprintf(makefile, "%s : %s\n	gcc %s -o %s\n",exec_name,main_name,main_name,exec_name);
	}
}

void prep(const char* file_name){
	char hfile_name[MAX_FILE_NAME] = "";
	char cfile_name[MAX_FILE_NAME] = "";
	char define_name[MAX_FILE_NAME] = "";
	FILE* gen_file;
	
	
	// generation du file.h
	strcpy(hfile_name,file_name);
	strcat(hfile_name,".h");
	to_maj(define_name,file_name);
	strcat(define_name,"_H");
	
	gen_file = fopen(hfile_name, "w");
	fprintf(gen_file, "#ifndef %s \n#define %s\n\n#endif", 
                        define_name,define_name);
	fclose(gen_file);
	
	// generation du file.c
	strcpy(cfile_name,file_name);
	strcat(cfile_name,".c");
	
	gen_file = fopen(cfile_name, "w");
	fprintf(gen_file, "#include \"%s\"", 
                        hfile_name);
	fclose(gen_file);
}


char* to_maj(char* ret,const char* txt){
	int i;
	int ln = strlen(txt);
	strcpy(ret,txt);
	for(i=0;i<ln;i++) if(ret[i]>='a' && ret[i]<='z') ret[i] += 'A'-'a';
	return ret;
}
