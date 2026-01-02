#include "shell.h"

/**
 * fork_ - Function that forks the processus into a child and
 * executes the program linked to the comand given in the child processus.
 * @args: Array of strings containing the input words.
 * @env: Environment.
 */

void fork_(char *args[], char **env)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		free_arr(args);
		perror("Error");
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			free_arr(args);
			perror("Error");
			exit(1);
		}
	}
	else
	{
		if (wait(&status) == -1)
		{
			free_arr(args);
			perror("Error");
			exit(1);
		}
	}
}
