testexe: minishell.o minishell_input.o free_args.o execute.o
	gcc -Wall minishell.o minishell_input.o free_args.o execute.o -L./lib/Linux/i686 -lshell -o testexe
minishell.o: minishell.c
	gcc -Wall -c minishell.c
minishell_input.o: minishell_input.c
	gcc -Wall -c minishell_input.c
free_args.o: free_args.c
	gcc -Wall -c free_args.c
execute.o: execute.c
	gcc -Wall -c execute.c
clean:
	rm *.o
	rm testexe
