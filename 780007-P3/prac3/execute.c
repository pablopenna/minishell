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

	if ((args=parser_command(command,&backgr))==NULL)
	{
		return;
	}
	else
	{
		pid=fork();
		switch(pid)
		{
			case 0: printf("\nsoy hijo\n");
					args=parser_command(command,&backgr);
					execvp(args[0],args);
					perror("\nerror execvp\n");
					break;

			case -1: printf("fallo creando hijo");
					break;
		}
		//parser_command(command,&backgr);

	}


	parser_free_args(args);
}
