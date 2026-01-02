#include "shell.h"

/**
 * main - simple shell with PATH
 * @ac: void
 * @av: void
 * @env: environment variable
 *
 * Return: 0
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;

	(void)ac;
	(void)av;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		args = strtok_array(line);
		if (!args)
			continue;

		if (args[0][0] != '/' && args[0][0] != '.')
		{
			if (!path(args, env))
			{
				fprintf(stderr, "%s: command not found\n", args[0]);
				free_arr(args);
				continue;
			}
		}

		fork_(args, env);
		free_arr(args);
	}

	free(line);
	return (0);
}
