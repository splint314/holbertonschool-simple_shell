#include "shell.h"

/**
 * main - Simple shell with PATH handling
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Return: 0
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int line_nb = 1;

	(void)ac;

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
				fprintf(stderr, "%s: %d: %s: not found\n",
						av[0], line_nb, args[0]);
				free_arr(args);
				line_nb++;
				continue;
			}
		}

		fork_(args, env);
		free_arr(args);
		line_nb++;
	}
	free(line);
	return (0);
}
