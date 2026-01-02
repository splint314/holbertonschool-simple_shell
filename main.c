#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char **args = NULL;
	int status = 0;
	int count = 0;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("($) ");

		line = read_line();
		if (line == NULL)
			break;

		args = parse_line(line);

		if (args && args[0])
			status = execute_command(args, argv[0], &count);

		free(line);
		free(args);
	}

	return (status);
}

/**
 * read_line - Read a line from stdin
 *
 * Return: Pointer to the line read, or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read;

	read = getline(&line, &bufsize, stdin);

	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * parse_line - Parse a line into tokens
 * @line: The line to parse
 *
 * Return: Array of tokens
 */
char **parse_line(char *line)
{
	int bufsize = BUFFER_SIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += BUFFER_SIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
