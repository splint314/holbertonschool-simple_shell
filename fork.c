#include "shell.h"

/**
 * fork_ - Forks and executes a command
 * @args: Command arguments
 * @env: Environment variables
 */
void fork_(char *args[], char **env)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(args[0], args, env);
		perror("Error");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(&status);
	}
}
