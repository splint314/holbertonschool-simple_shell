#include "shell.h"

/**
 * shell_loop - main shell loop
 *
 */
void shell_loop(void)
{
	char *line;

	while (1)
	{
		line = read_line();
		break;

		if (line[0] != '\0')
			execute_command(line);

		free(line);
	}
}
