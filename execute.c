#include "shell.h"

/**
 * execute_command - executes a single command
 * @command: command to execute (absolute path)
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
