#include "shell.h"

/**
 * shell_loop - main loop of the shell
 *
 * This shell reads a line from stdin, executes the command,
 * and repeats until EOF (Ctrl+D) is received.
 */
void shell_loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] != '\0')
			execute_command(line);
	}

	free(line);
}
