#include "shell.h"

/**
 * shell_loop - main shell loop
 *
 */
void shell_loop(void)
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

		while (*line == ' ')
			line++;
		if (*line != '\0')
			execute_command(line);

		free(line);
	}
}
