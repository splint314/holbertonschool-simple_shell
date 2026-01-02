#include "shell.h"

/**
 * shell_loop - main shell loop
 * @name: program name
 */
void shell_loop(char *name)
{
	char *line;
	int interactive;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		line = read_line();
		if (!line)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[0] != '\0')
			execute_command(line, name);

		free(line);
	}
}
