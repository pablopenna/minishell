#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "internals.h"
#include "execute.h"
#include "jobs.h"
#include "minishell_input.h"


int main (int argc, char *argv[])
{
	char buf[BUFSIZ];
	
	while(1)
	{
		print_prompt();
		read_command_line(buf);

		if(strcmp(buf,"exit")==0){
			jobs_free_mem();
			exit(0);
		}

		else
		{
			if(is_internal_command(buf))//internal command
			{
				execute_internal_command(buf);//executed internal command
			}
			else
			{
				execute_external_command(buf);
			}
		}
	}
	return 0;
}
