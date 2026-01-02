#include "shell.h"

/**
 * execute_command - executes a single command without arguments
 * @command: the command to execute (full path required)
 *
 * Return: 0 on success, 1 if command cannot be executed
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(command, args, environ);
		fprintf(stderr, "%s: 1: %s: not found\n", "./hsh", command);
		exit(127);
	}
	else
		wait(&status);

	return (0);
}
