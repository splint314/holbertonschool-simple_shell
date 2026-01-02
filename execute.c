#include "shell.h"
/**
 * execute_command - executes a command
 * @command: command to execute
 * @name: program name
 */
void execute_command(char *command, char *name)
{
	pid_t pid;
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
			print_error(name, command);
			_exit(127);
		}
	}
	else
		wait(NULL);
}
