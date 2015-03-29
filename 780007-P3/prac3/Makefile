minishell: minishell.o minishell_input.o free_args.o execute.o
	gcc -Wall minishell.o minishell_input.o free_args.o execute.o -L./lib/Linux/i686 -lshell -o minishell
minishell.o: minishell.c
	gcc -Wall -g -c minishell.c
minishell_input.o: minishell_input.c
	gcc -Wall -g -c minishell_input.c
free_args.o: free_args.c
	gcc -Wall -g -c free_args.c
execute.o: execute.c
	gcc -Wall -g -c execute.c
clean:
	rm *.o
	rm minishell
