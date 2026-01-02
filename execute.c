#include "shell.h"

/**
 * execute_builtin - Execute built-in commands
 * @args: Array of arguments
 *
 * Return: 1 if command was built-in, 0 otherwise, -1 for exit
 */
int execute_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
		return (-1);

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}

/**
 * execute_external - Execute external command
 * @args: Array of arguments
 * @argv0: Program name for error messages
 * @count: Command count for error messages
 *
 * Return: 1 on success
 */
int execute_external(char **args, char *argv0, int count)
{
	pid_t pid;
	int status;
	char *full_path = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (strchr(args[0], '/') != NULL)
			full_path = args[0];
		else
			full_path = find_path(args[0]);

		if (full_path == NULL || execve(full_path, args, environ) == -1)
		{
			print_error(argv0, count, args[0]);
			if (full_path != args[0])
				free(full_path);
			exit(127);
		}
	}
	else if (pid < 0)
		perror("fork");
	else
		waitpid(pid, &status, 0);

	return (1);
}

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @argv0: Program name for error messages
 * @count: Pointer to command count
 *
 * Return: 1 if shell should continue, 0 if it should terminate
 */
int execute_command(char **args, char *argv0, int *count)
{
	int builtin_result;

	(*count)++;

	builtin_result = execute_builtin(args);
	if (builtin_result == -1)
		return (0);
	if (builtin_result == 1)
		return (1);

	return (execute_external(args, argv0, *count));
}

/**
 * print_error - Print error message
 * @argv0: Program name
 * @count: Command count
 * @command: Command that failed
 */
void print_error(char *argv0, int count, char *command)
{
	fprintf(stderr, "%s: %d: %s: not found\n", argv0, count, command);
}

/**
 * print_env - Print environment variables
 */
void print_env(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
