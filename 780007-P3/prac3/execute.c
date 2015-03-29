#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "execute.h"
#include "free_args.h"
#include "jobs.h"


void child_zombie_killer(int signal, siginfo_t *info, void *context)
{
	waitpid(-1,0,WNOHANG); /*-1 so that it waits for any child*/
	jobs_finished(info->si_pid);/*gets the pid of the child and registers it as
	finished at jobs*/
}

void execute_external_command(const char *command)
{
	struct sigaction act;/*declare sigaction struct for sigaction()*/
	act.sa_sigaction=&child_zombie_killer;/*points function to execute when
	SIGCHLD is received*/ 
	act.sa_flags=SA_SIGINFO;/*so that we get info from the signal*/
	sigaction(SIGCHLD,&act,NULL);/*what signal to receive and what to do.*/
	
	char **args;
	int backgr=0;
	pid_t pid;
	int status;/*used by the system*/

	if ((args=parser_command(command,&backgr))==NULL)
	{
		return;
	}
	else
	{
		pid=fork();
		
		if(pid==0){
			/* CHILD PROCESS	printf("\n------soy hijo-%d\n",backgr);*/
			args=parser_command(command,&backgr);
			if(execvp(args[0],args)==0)/* if it is not a valid command it doesnt
			execute*/
			{
				execvp(args[0],args);
			}
			else
			{
				printf("\nInvalid Command\n");
				exit(1);
			}
				
		}
		else{
			if(pid==-1){
				printf("FAILURE creating a child");
				exit(-1);
			}
			else{
				/* PARENT PROCESS		printf("\n-----Soy padre-%d\n",backgr);*/
				if(backgr==1){/*foreground process*/
					jobs_new(pid,args[0]);/*Declared new process in parent*/
					waitpid(pid,&status,0);
					jobs_finished(pid);
				}
				else{/*background process*/
					jobs_new(pid,args[0]);/*new process declared in the parent*/
					waitpid(pid,&status,WNOHANG);
				}
			}

		}
	}
	parser_free_args(args);/*free memory*/
}
