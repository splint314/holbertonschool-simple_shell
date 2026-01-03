#include "shell.h"

/**
 * main - simple shell
 * @ac: argument count (unused)
 * @av: argument vector
 * @env: environment
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
	int interactive;

	(void)ac;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		args = strtok_array(line);
		if (!args)
		{
			line_nb++;
			continue;
		}
		if (args[0][0] != '/' && args[0][0] != '.' && !path(args, env))
		{
			handle_not_found(av, args,
							 line_nb, interactive, line);
			line_nb++;
			continue;
		}
		fork_(args, env);
		free_arr(args);
		line_nb++;
	}
	free(line);
	return (0);
}
