#include "shell.h"
/**
 * execute_command - executes a single command
 * @command: command to execute
 *
 * Description: forks a child process to execute the command
 * using execve. Does not print messages to stderr; just exits
 * child with status 127 if execve fails.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];
	char *path;

	path = resolve_path(command);

	argv[0] = path;
	argv[1] = NULL;

	pid = fork();
	if (pid == -1)
		return;

	if (pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			_exit(127);
		}
	}
	else
		waitpid(pid, &status, 0);
}
