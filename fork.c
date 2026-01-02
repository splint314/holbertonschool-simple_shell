#include "shell.h"

/**
 * fork_ - Function that forks the processus into a child and
 * executes the program linked to the comand given in the child processus.
 * @args: Array of strings containing the input words.
 * @env: Environment.
 */

void fork_(char *args[], char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_arr(args);
		exit(1);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("execve");
			free_arr(args);
			exit(1);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			perror("wait");
			free_arr(args);
			exit(1);
		}
	}
}
