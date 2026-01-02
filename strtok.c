#include "shell.h"

/**
 * strtok_array - Split line into an array
 * @str: Input string.
 * Return: An array of strings, if not NULL.
 */
char **strtok_array(char *str)
{
	char *token;
	char **args;
	size_t i = 0, bufsize = 64;

	args = malloc(bufsize * sizeof(char *));
	if (!args)
		exit(1);

	token = strtok(str, " \t\r\n");
	while (token)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			while (i > 0)
			{
				i--;
				free(args[i]);
			}
			free(args);
			exit(1);
		}
		i++;
		if (i >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, bufsize * sizeof(char *));
			if (!args)
				exit(1);
		}
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;

	if (i == 0)
	{
		free(args);
		return NULL;
	}

	return (args);
}
