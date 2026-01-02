#include "shell.h"

/**
 * shell_loop - main shell loop
 *
 */
void shell_loop(void)
{
	char *line;
	char *ptr;
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

		ptr = line;
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
			ptr++;

		if (*ptr != '\0')
			execute_command(ptr);

		free(line);
	}
}
