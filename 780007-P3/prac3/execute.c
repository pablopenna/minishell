#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "parser.h"
#include "execute.h"
#include "free_args.h"
#include "jobs.h"

void execute_external_command(const char *command)
{
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
			execvp(args[0],args);
		}
		else{
			if(pid==-1){
				printf("fallo creando hijo");
				exit(-1);
			}
			else{
				printf("\n-----Soy padre-%d\n",backgr);
				if(backgr==1){//proceso primer plano
					waitpid(pid,&status,0);
				}
				else{//segundo plano
					waitpid(pid,&status,WNOHANG);
				}
			}

		}
	}
	parser_free_args(args);
}
