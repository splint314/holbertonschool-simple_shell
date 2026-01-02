#include "shell.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/**
 * split_line - Splits a command line into arguments
 * @line: The string to be split
 *
 * This function parses the string `line` and splits it into tokens
 * separated by spaces, tabs, carriage returns, or alerts
 * (as defined by TOK_DELIM). It dynamically allocates an array of
 * pointers to the tokens and returns it. The last element of the
 * array is always NULL to indicate the end.
 *
 * Return: An array of strings (tokens), or exits the program if
 * memory allocation fails.
 */
char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		exit(1);

	token = strtok(line, TOK_DELIM);
	while (token)
	{
		tokens[position++] = token;

		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				exit(1);
		}

		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

/**
 * execute_command - executes a single command
 * @command: command to execute (absolute path)
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char **args;

	args = split_line(line);
	if (!args[0])
	{
		free(args);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			exit(1);
	}
	else if (pid < 0)
	{
		exit(1);
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(args);
}
