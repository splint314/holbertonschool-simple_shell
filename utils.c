#include "shell.h"

/**
 * read_line - read input from stdin
 *
 * Return: pointer to string or NULL on EOF
 */
char *read_line(void)
{
	char *line;
	size_t len;
	ssize_t nread;

	line = NULL;
	len = 0;
	nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}
