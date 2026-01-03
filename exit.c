#include "shell.h"

/**
 * handle_not_found - handle command not found error
 * @av: argument vector
 * @args: command arguments
 * @line_nb: line number
 * @interactive: interactive mode flag
 * @line: input line
 */
void handle_not_found(char **av, char **args,
					  int line_nb, int interactive, char *line)
{
	fprintf(stderr, "%s: %d: %s: not found\n",
			av[0], line_nb, args[0]);
	free_arr(args);
	if (!interactive)
	{
		free(line);
		exit(127);
	}
}
