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
	int i=0;
	while(i==0){
		print_prompt();
		read_command_line(buf);

		if(strcmp(buf,"exit")==0){
			i++;
		}

		else
		{
			if(is_internal_command(buf))//internal command
			{
				execute_internal_command(buf);//executed internal command
			}
			else
			{
				printf("\nExecution of external commands not implemented yet");
			}
		
		}

	return(0);


	}
}
