#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<time.h>

char* moleloc;
pid_t cpid;
int fd0,fd1,fd2;

void usrhandler(int signum){
	signal(signum,usrhandler);
	if(cpid!=0){
		kill(cpid,SIGKILL);
	}
	pid_t newpid;
	newpid=fork();
	srand(time(NULL));
	if(newpid==0){
		int rand_num = (rand()%(2-1+1))+1;
		if(rand_num==1){
			char* args[]={"mole1",NULL};
			execv(moleloc,args);
		}
		if(rand_num==2){
			char* args[]={"mole2",NULL};
			execv(moleloc,args);
		}
	}
}

void termhandler(int signum){
	if(cpid!=0){
		kill(cpid,SIGKILL);
	}
	kill(getpid(),SIGKILL);
}


int main(int argc, char** argv){

	(void)argc;
	char currdir[1014];
	pid_t pid,seshid;
	struct rlimit res_lim;

	moleloc = getcwd(currdir,1014);
	strncat(moleloc,"/mole",10);
	//printf("moleloc is %s\n",moleloc);

	char* homedir = getenv("HOME");
	char* filename = "/lab6.log";
	char* filepath = malloc(strlen(homedir)+strlen(filename)+1);
	strncpy(filepath,homedir,strlen(homedir)+1);
	strncat(filepath,filename,strlen(filename)+1);

	FILE *logfile;
	logfile = fopen(filepath,"w+");

	if(logfile==NULL){
		fprintf(stderr,"file error\n");
		exit(1);
	}

	fclose(logfile);
	free(filepath);

	pid=fork();
	if(pid!=0){
		exit(0);
	}

	signal(SIGUSR1,usrhandler);
	signal(SIGUSR2,usrhandler);
	signal(SIGTERM,termhandler);

	umask(0);

	seshid=setsid();
	cpid = 0;

	chdir("~/");

	getrlimit(RLIMIT_NOFILE,&res_lim);

	if(res_lim.rlim_max==RLIM_INFINITY){
		res_lim.rlim_max=1024;
	}
	for(int i=0;i<res_lim.rlim_max;i++){
		close(i);
	}

	fd0 = open("/dev/null",O_RDWR);
	fd1 = dup(0);
	fd2 = dup(0);

	while(1){
		//do nothing
	}

	exit(0);
	return 0;
}