#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "execute.h"
#include "free_args.h"
#include "jobs.h"


void child_zombie_killer(int signal, siginfo_t *info, void *context)
{
	waitpid(-1,0,WNOHANG); //-1 para que espera por cualquier proceso hijo
	jobs_finished(info->si_pid);
}

void execute_external_command(const char *command)
{
	//struct siginfo_t *info;
//	struct ucontext_t *context;
	
	struct sigaction act;
	act.sa_sigaction=&child_zombie_killer;//,info,NULL;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGCHLD,&act,NULL);
	
	char **args;
	int backgr=0;
	pid_t pid;
	int status;

	if ((args=parser_command(command,&backgr))==NULL)
	{
		return;
	}
	else
	{
		pid=fork();
		
		if(pid==0){
			printf("\n------soy hijo-%d\n",backgr);
			args=parser_command(command,&backgr);
			if(execvp(args[0],args)==0)//because if u type a non-valid command
										//creates an additional shell
				execvp(args[0],args);
			else
				exit(1);
		}
		else{
			if(pid==-1){
				printf("fallo creando hijo");
				exit(-1);
			}
			else{
				printf("\n-----Soy padre-%d\n",backgr);
				if(backgr==1){//proceso primer plano
					jobs_new(pid,args[0]);//declaro el proceso en el procs padre
					waitpid(pid,&status,0);
					jobs_finished(pid);
				}
				else{//segundo plano
					jobs_new(pid,args[0]);//declaro el proceso en el padre
					waitpid(pid,&status,WNOHANG);
				}
			}

		}
	}
	parser_free_args(args);
}
