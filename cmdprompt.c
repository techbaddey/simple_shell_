#include "shell.h"
#include <sys/wait.h>

void cmdprompt(char **av, char **env)
{
	char *string = NULL;
	size_t n = 0;
	int i, status; 
	ssize_t num_input; /*Number of  characters input by user*/
	char *argv[] = {NULL, NULL};
	pid_t prop_pid; /*child of the processs ID(PID)*/


	while(1)
	{	
		/* isatty function checks if fd is an open file descriptor ref to terminal*/

		if (isatty(STDIN_FILENO))
			printf("shell is hell..!$ ");

		/*getline func*/

		num_input = getline(&string, &n, stdin);
		if (num_input == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}

		i = 0;
		while (string[i])
		{
			if(string[i] == '\n')
				string[i] = 0;
			i++;
		}
		
		argv[0] = string;
		prop_pid = fork();
		if (prop_pid == -1)
		{
			free(string);
			exit(EXIT_FAILURE);
		}
		if (prop_pid == 0)
		{
			if(execve(argv[0], argv, env))
				printf("%s: No such file or directory\n", av[0]);
		}
		else
			wait(&status);
	}
}
