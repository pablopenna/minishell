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

		if(strchr(buf,';')==NULL)/*if there is no ';' in the command, the
		function strchr() returns NULL, so the command will be a simple one*/
		{	
			if(strcmp(buf,"exit")==0){
				jobs_free_mem();
				exit(0);
			}
		
			else
			{
				if(is_internal_command(buf))//internal command
				{
					execute_internal_command(buf);//execute internal command
				}
				else
				{
					execute_external_command(buf);
				}
			}
		}
			
		else/*if there is a ';' in the command line(variable buf)->complex
		command line*/
		{
			
			char * buf_split;
			buf_split=strtok(buf,";");/*split the command line with ';'*/
			while(buf_split!=NULL)
			{
				if(strcmp(buf_split,"exit")==0){
					jobs_free_mem();
					exit(0);
				}

				else
				{
					if(is_internal_command(buf_split))/*interal command*/
					{
						execute_internal_command(buf_split);/*execute internal
						command*/
					}
					else
					{
						execute_external_command(buf_split);/*execute external
						command*/
					}
				}
			buf_split=strtok(NULL,";");
			}
		}
	}
	return 0;
}
