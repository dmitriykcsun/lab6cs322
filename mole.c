#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char** argv){

	//printf("(test) my pid is %d\n",getpid());

	(void) argc;

	char* homedir = getenv("HOME");
	char* filename = "/lab6.log";
	char* filepath = malloc(strlen(homedir)+strlen(filename)+1);
	strncpy(filepath,homedir,strlen(homedir)+1);
	strncat(filepath,filename,strlen(filename)+1);

	FILE *logfile;
	logfile = fopen(filepath,"a");

	if(logfile==NULL){
		fprintf(stderr,"file error\n");
		exit(1);
	}

	fprintf(logfile,"Pop %s\n",argv[0]);
	fclose(logfile);

	free(filepath);
	pause();

	return 0;
}